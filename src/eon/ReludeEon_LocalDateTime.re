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

// getters
let toTuple = (LocalDateTime(date, time)) => {
  let (year, month, day) = LocalDate.toTuple(date);
  let (hour, minute, second, ms) = LocalTime.toTuple(time);
  (year, month, day, hour, minute, second, ms);
};

let getYear = (LocalDateTime(date, _)) => LocalDate.getYear(date);
let getMonth = (LocalDateTime(date, _)) => LocalDate.getMonth(date);
let getDayOfMonth = (LocalDateTime(date, _)) =>
  LocalDate.getDayOfMonth(date);

let getHour = (LocalDateTime(_, time)) => LocalTime.getHour(time);
let getMinute = (LocalDateTime(_, time)) => LocalTime.getMinute(time);
let getSecond = (LocalDateTime(_, time)) => LocalTime.getSecond(time);
let getMillisecond = (LocalDateTime(_, time)) =>
  LocalTime.getMillisecond(time);

// math
// let addDay

// comparison
let eq = (LocalDateTime(datea, timea), LocalDateTime(dateb, timeb)) =>
  LocalDate.eq(datea, dateb) && LocalTime.eq(timea, timeb);

let compare = (LocalDateTime(datea, timea), LocalDateTime(dateb, timeb)) =>
  switch (LocalDate.compare(datea, dateb)) {
  | `equal_to => LocalTime.compare(timea, timeb)
  | v => v
  };

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = compare;
};
