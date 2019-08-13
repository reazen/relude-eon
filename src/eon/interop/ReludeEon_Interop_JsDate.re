open Relude.Globals;

module Month = ReludeEon_Month;
module OffsetMinute = ReludeEon_OffsetMinute;

module LocalDateTime = ReludeEon_LocalDateTime;
module Instant = ReludeEon_Instant;
module InstantUTC = ReludeEon_InstantUTC;

let fromInstantUTC = utc => {
  let instant = Instant.fromInstantUTC(utc);
  let (y, mo, d, h, m, s, _ms, _offset) = Instant.toTuple(instant);
  Js.Date.utcWithYMDHMS(
    ~year=Int.toFloat(y),
    ~month=Int.toFloat(Month.toInt0Based(mo)),
    ~date=Int.toFloat(d),
    ~hours=Int.toFloat(h),
    ~minutes=Int.toFloat(m),
    ~seconds=Int.toFloat(s),
    // TODO: constructor doesn't support milliseconds
    // we should probably just write our own binding...
    (),
  )
  |> Js.Date.fromFloat;
};

let fromInstant = instant => Instant.toInstantUTC(instant) |> fromInstantUTC;

let toInstantUTC = d =>
  LocalDateTime.makeClampedLabels(
    ~year=Int.fromFloat(Js.Date.getUTCFullYear(d)),
    ~month=
      Month.fromInt0BasedClamped(Int.fromFloat(Js.Date.getUTCMonth(d))),
    ~day=Int.fromFloat(Js.Date.getUTCDate(d)),
    ~hour=Int.fromFloat(Js.Date.getUTCHours(d)),
    ~minute=Int.fromFloat(Js.Date.getUTCMinutes(d)),
    ~second=Int.fromFloat(Js.Date.getUTCSeconds(d)),
    ~millisecond=Int.fromFloat(Js.Date.getUTCMilliseconds(d)),
    (),
  )
  |> InstantUTC.fromLocalDateTime;

let toInstant = (~offsetMinute=0, d) =>
  Instant.fromInstantUTC(~offsetMinute, toInstantUTC(d));

let toInstantForOffset = (offset, d) =>
  toInstant(~offsetMinute=OffsetMinute.getOffsetMinute(offset), d);

let toLocalDateTime = (~offsetMinute=0, d) =>
  toInstant(~offsetMinute, d) |> Instant.getDateTime;

let toLocalDate = (~offsetMinute=0, d) =>
  toInstant(~offsetMinute, d) |> Instant.getDate;

let toLocalTime = (~offsetMinute=0, d) =>
  toInstant(~offsetMinute, d) |> Instant.getTime;

let now = () => IO.suspend(() => Js.Date.make() |> toInstantUTC);

let getClientOffsetMinute = () => {
  let d = Js.Date.(getTimezoneOffset(make()));
  IO.suspend(() => OffsetMinute.makeClamped(Int.(negate(fromFloat(d)))));
};
