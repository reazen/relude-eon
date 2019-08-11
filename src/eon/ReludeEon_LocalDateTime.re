module LocalDate = ReludeEon_LocalDate;
module LocalTime = ReludeEon_LocalTime;
module Math = ReludeEon_DateMath;

type t =
  | LocalDateTime(LocalDate.t, LocalTime.t);

let makeWrapped = (y, mo, d, h, m, s, ms) => {
  let (days, hour, minute, second, millisecond) = Math.wrapTime(h, m, s, ms);
  let date = LocalDate.makeWrapped(y, mo, days + d);
  let time = LocalTime.makeClamped(hour, minute, second, millisecond);

  LocalDateTime(date, time);
};

let makeWrappedLabels =
    (~year, ~month, ~day, ~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  makeWrapped(year, month, day, hour, minute, second, millisecond);

let makeClamped = (y, mo, d, h, m, s, ms) =>
  LocalDateTime(
    LocalDate.makeClamped(y, mo, d),
    LocalTime.makeClamped(h, m, s, ms),
  );

let makeClampedLabels =
    (~year, ~month, ~day, ~hour, ~minute, ~second, ~millisecond=0, ()) =>
  makeClamped(year, month, day, hour, minute, second, millisecond);
