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
    (~year, ~month, ~day, ~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  makeClamped(year, month, day, hour, minute, second, millisecond);

let fromDateAndTime = (date, time) => LocalDateTime(date, time);

let fromDateClamped =
    (~hour=0, ~minute=0, ~second=0, ~millisecond=0, date) =>
  LocalDateTime(
    date,
    LocalTime.makeClamped(hour, minute, second, millisecond),
  );

// getters
let toTuple = (LocalDateTime(date, time)) => {
  let (year, month, day) = LocalDate.toTuple(date);
  let (hour, minute, second, ms) = LocalTime.toTuple(time);
  (year, month, day, hour, minute, second, ms);
};

let getDate = (LocalDateTime(date, _)) => date;
let getYear = (LocalDateTime(date, _)) => LocalDate.getYear(date);
let getMonth = (LocalDateTime(date, _)) => LocalDate.getMonth(date);
let getDayOfMonth = (LocalDateTime(date, _)) =>
  LocalDate.getDayOfMonth(date);

let getTime = (LocalDateTime(_, time)) => time;
let getHour = (LocalDateTime(_, time)) => LocalTime.getHour(time);
let getMinute = (LocalDateTime(_, time)) => LocalTime.getMinute(time);
let getSecond = (LocalDateTime(_, time)) => LocalTime.getSecond(time);
let getMillisecond = (LocalDateTime(_, time)) =>
  LocalTime.getMillisecond(time);

// math

// private, but used a lot to work with date and time math
let addDate = (fn, howMany, LocalDateTime(date, time)) =>
  LocalDateTime(fn(howMany, date), time);

let addTime = (fn, howMany, LocalDateTime(date, time)) => {
  let (hour, minute, second, millisecond) = LocalTime.toTuple(time);
  let (d, h, m, s, ms) = fn(howMany, hour, minute, second, millisecond);
  LocalDateTime(
    LocalDate.addDays(d, date),
    LocalTime.makeClamped(h, m, s, ms),
  );
};

let addYears = addDate(LocalDate.addYears);
let prevYear = dt => addYears(-1, dt);
let nextYear = dt => addYears(1, dt);

let addMonths = addDate(LocalDate.addMonths);
let prevMonth = dt => addMonths(-1, dt);
let nextMonth = dt => addMonths(1, dt);

let addDays = addDate(LocalDate.addDays);
let prevDay = dt => addDays(-1, dt);
let nextDay = dt => addDays(1, dt);

let addHours = addTime(Math.addHours);
let prevHour = dt => addHours(-1, dt);
let nextHour = dt => addHours(1, dt);

let addMinutes = addTime(Math.addMinutes);
let prevMinute = dt => addMinutes(-1, dt);
let nextMinute = dt => addMinutes(1, dt);

let addSeconds = addTime(Math.addSeconds);
let prevSecond = dt => addSeconds(-1, dt);
let nextSecond = dt => addSeconds(1, dt);

let addMilliseconds = addTime(Math.addMillis);
let prevMillisecond = dt => addMilliseconds(-1, dt);
let nextMillisecond = dt => addMilliseconds(1, dt);

// comparison
let eq = (LocalDateTime(datea, timea), LocalDateTime(dateb, timeb)) =>
  LocalDate.eq(datea, dateb) && LocalTime.eq(timea, timeb);

let compare = (LocalDateTime(datea, timea), LocalDateTime(dateb, timeb)) =>
  switch (LocalDate.compare(datea, dateb)) {
  | `equal_to => LocalTime.compare(timea, timeb)
  | v => v
  };

module Eq: BsBastet.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};

module Ord: BsBastet.Interface.ORD with type t = t = {
  include Eq;
  let compare = compare;
};

include Relude_Extensions_Ord.OrdExtensions(Ord);
