module Year = ReludeEon_Year;
module Month = ReludeEon_Month;
module DayOfMonth = ReludeEon_DayOfMonth;

type t =
  | YMD(Year.t, Month.t, DayOfMonth.t);

let isLeapYear = (YMD(year, _, _)) => Year.isLeapYear(year);

let daysInMonth = (YMD(year, month, _)) =>
  Month.totalDays(Year.isLeapYear(year), month);

// private, because this is only useful for forcing the day to be in the range
// 1...daysInMonth, which shouldn't be a concern for external YMDs
let clampDay = (YMD(year, month, day) as ymd) => {
  let max = DayOfMonth.fromInt(daysInMonth(ymd));
  let clamped = DayOfMonth.clamp(~min=DayOfMonth.fromInt(1), ~max, day);
  YMD(year, month, clamped);
};

let prevMonth = (YMD(year, month, day)) => {
  let year = Month.eq(month, Jan) ? Year.prev(year) : year;
  clampDay(YMD(year, Month.prev(month), day));
};

let nextMonth = (YMD(year, month, day)) => {
  let year = Month.eq(Dec, month) ? Year.next(year) : year;
  clampDay(YMD(year, Month.next(month), day));
};
