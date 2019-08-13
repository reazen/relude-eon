module LocalDateTime = ReludeEon_LocalDateTime;
module OffsetMinute = ReludeEon_OffsetMinute;

type t =
  | Instant(LocalDateTime.t, OffsetMinute.t);

let make = (dateTime, offset) => Instant(dateTime, offset);

// small gotcha: offsets will never be wrapped... always clamped
let makeWrapped = (y, mo, d, h, m, s, ms, o) => {
  let dt = LocalDateTime.makeWrapped(y, mo, d, h, m, s, ms);
  let offset = OffsetMinute.makeClamped(o);
  Instant(dt, offset);
};

let makeWrappedLabels =
    (
      ~year,
      ~month,
      ~day,
      ~hour=0,
      ~minute=0,
      ~second=0,
      ~millisecond=0,
      ~offset=0,
      (),
    ) =>
  makeWrapped(year, month, day, hour, minute, second, millisecond, offset);

let makeClamped = (y, mo, d, h, m, s, ms, o) => {
  let dt = LocalDateTime.makeClamped(y, mo, d, h, m, s, ms);
  let offset = OffsetMinute.makeClamped(o);
  Instant(dt, offset);
};

let makeClampedLabels =
    (
      ~year,
      ~month,
      ~day,
      ~hour=0,
      ~minute=0,
      ~second=0,
      ~millisecond=0,
      ~offsetMinute=0,
      (),
    ) =>
  makeClamped(
    year,
    month,
    day,
    hour,
    minute,
    second,
    millisecond,
    offsetMinute,
  );

let fromDateTime = (~offsetMinute=0, dt) =>
  Instant(dt, OffsetMinute.makeClamped(offsetMinute));

let fromDateAndTime = (~offsetMinute=0, date, time) =>
  Instant(
    LocalDateTime.fromDateAndTime(date, time),
    OffsetMinute.makeClamped(offsetMinute),
  );

let fromDateClamped =
    (~hour=?, ~minute=?, ~second=?, ~millisecond=?, ~offsetMinute=0, date) =>
  Instant(
    LocalDateTime.fromDateClamped(
      ~hour?,
      ~minute?,
      ~second?,
      ~millisecond?,
      date,
    ),
    OffsetMinute.makeClamped(offsetMinute),
  );

// TODO: fromInstantUTC

// destructure and set values
let toTuple = (Instant(dt, offset)) => {
  let (y, mo, d, h, m, s, ms) = LocalDateTime.toTuple(dt);
  (y, mo, d, h, m, s, ms, OffsetMinute.getOffsetMinute(offset));
};

let getDateTime = (Instant(dt, _)) => dt;
let getDate = (Instant(dt, _)) => LocalDateTime.getDate(dt);
let getTime = (Instant(dt, _)) => LocalDateTime.getTime(dt);
let getOffset = (Instant(_, offset)) => offset;
let getOffsetMinute = (Instant(_, offset)) =>
  OffsetMinute.getOffsetMinute(offset);

// make it very clear that this is not adjusting the date
let overwriteOffset = (offset, Instant(dt, _)) => Instant(dt, offset);

// math
let addYears = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addYears(howMany, dt), offset);
let prevYear = addYears(-1);
let nextYear = addYears(1);

let addMonths = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addMonths(howMany, dt), offset);
let prevMonth = addMonths(-1);
let nextMonth = addMonths(1);

let addDays = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addDays(howMany, dt), offset);
let prevDay = addDays(-1);
let nextDay = addDays(1);

let addHours = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addHours(howMany, dt), offset);
let prevHour = addHours(-1);
let nextHour = addHours(1);

let addMinutes = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addMinutes(howMany, dt), offset);
let prevMinute = addMinutes(-1);
let nextMinute = addMinutes(1);

let addSeconds = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addSeconds(howMany, dt), offset);
let prevSecond = addSeconds(-1);
let nextSecond = addSeconds(1);

let addMilliseconds = (howMany, Instant(dt, offset)) =>
  Instant(LocalDateTime.addMilliseconds(howMany, dt), offset);
let prevMillisecond = addMilliseconds(-1);
let nextMillisecond = addMilliseconds(1);

let adjustOffset = (newOffset, Instant(dt, offset)) => {
  let newOffsetMinutes = OffsetMinute.getOffsetMinute(newOffset);
  let existingOffsetMinutes = OffsetMinute.getOffsetMinute(offset);
  let dt =
    LocalDateTime.addMinutes(newOffsetMinutes - existingOffsetMinutes, dt);
  Instant(dt, newOffset);
};

let adjustOffsetClamped = (offset, instant) =>
  adjustOffset(OffsetMinute.makeClamped(offset), instant);

let adjustToUTC = adjustOffset(OffsetMinute.utc);

// TODO: toInstantUTC

// Instants can be compared for equality, but note that two moments in time may
// not be strictly equal if the timezone is not the same. For this reason, we
// also don't offer ordering. You should explicitly convert both values to an
// `InstantUTC` if you want a `compare` function.
let eq = (Instant(dta, offseta), Instant(dtb, offsetb)) =>
  LocalDateTime.eq(dta, dtb) && OffsetMinute.eq(offseta, offsetb);

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};
