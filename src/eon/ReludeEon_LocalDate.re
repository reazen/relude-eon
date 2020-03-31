module Year = ReludeEon_Year;
module Month = ReludeEon_Month;
module DayOfMonth = ReludeEon_DayOfMonth;
module Math = ReludeEon_DateMath;

type t =
  | LocalDate(Year.t, Month.t, DayOfMonth.t);

let daysInMonth = (LocalDate(year, month, _)) =>
  Month.totalDays(Year.isLeapYear(year), month);

// -----------------------------------------------------------------------------
// # Private
//
// The following functions are private (hidden from the interface) because they
// can produce invalid days of the month, or they're only useful when working
// with potentially invalid days of the month (which is useful internally, but
// shouldn't be possible outside of this module).
// -----------------------------------------------------------------------------

let unsafeWithDay = (day, LocalDate(year, month, _)) =>
  LocalDate(year, month, DayOfMonth.fromInt(day));

let unsafePrevMonth = (LocalDate(year, month, day)) => {
  let year = Month.eq(month, Jan) ? Year.prev(year) : year;
  LocalDate(year, Month.prev(month), day);
};

let unsafeNextMonth = (LocalDate(year, month, day)) => {
  let year = Month.eq(month, Dec) ? Year.next(year) : year;
  LocalDate(year, Month.next(month), day);
};

let clampDay = (LocalDate(year, month, day) as ymd) => {
  let max = DayOfMonth.fromInt(daysInMonth(ymd));
  let clamped = DayOfMonth.clamp(~min=DayOfMonth.fromInt(1), ~max, day);
  LocalDate(year, month, clamped);
};

let rec wrap = (LocalDate(_, _, DayOfMonth(day)) as ymd) => {
  // TODO: for efficiency, we could start by seeing if `day` is gte 365 (or 366
  // if the next Feb is in a leap year). As long as `day` is gte one full year,
  // we could make big steps instead of going one month at a time.
  let size = daysInMonth(ymd);
  let prev = unsafePrevMonth(ymd);

  day > size
    ? wrap(unsafeWithDay(day - size, ymd) |> unsafeNextMonth)
    : day <= 0 ? wrap(unsafeWithDay(day + daysInMonth(prev), prev)) : ymd;
};

// -----------------------------------------------------------------------------
// # Public
// -----------------------------------------------------------------------------

let makeWrapped = (year, month, day) =>
  wrap(LocalDate(Year.fromInt(year), month, DayOfMonth(day)));

let makeClamped = (year, month, day) =>
  clampDay(LocalDate(Year.fromInt(year), month, DayOfMonth(day)));

let make = (year, month, day) => {
  let ymd = LocalDate(Year.fromInt(year), month, DayOfMonth(day));
  day <= 0 || day > daysInMonth(ymd) ? None : Some(ymd);
};

// getters, since constructor is private
let toTuple = (LocalDate(year, month, DayOfMonth(day))) => (
  Year.getYear(year),
  month,
  day,
);
let getYear = (LocalDate(year, _, _)) => Year.getYear(year);
let getMonth = (LocalDate(_, month, _)) => month;
let getDayOfMonth = (LocalDate(_, _, DayOfMonth(day))) => day;

let addYears = (howMany, LocalDate(year, month, day)) =>
  clampDay(LocalDate(Year.addYears(howMany, year), month, day));

let prevYear = ymd => addYears(-1, ymd);
let nextYear = ymd => addYears(1, ymd);

let addMonths = (howMany, LocalDate(y, m, d)) => {
  let monthSum = Month.toInt0Based(m) + howMany;
  let (years, month) = Math.divWithRemainder(monthSum, 12);
  clampDay(
    LocalDate(
      Year.addYears(years, y),
      Month.fromInt0BasedWrapped(month),
      d,
    ),
  );
};

let prevMonth = ymd => addMonths(-1, ymd);
let nextMonth = ymd => addMonths(1, ymd);

let addDays = (howMany, LocalDate(_, _, DayOfMonth(day)) as ymd) =>
  wrap(unsafeWithDay(day + howMany, ymd));

let nextDay = ymd => addDays(1, ymd);
let prevDay = ymd => addDays(-1, ymd);

let isLeapYear = (LocalDate(year, _, _)) => Year.isLeapYear(year);

let daysInYear = (LocalDate(year, _, _)) => Year.totalDays(year);

let eq = (LocalDate(yeara, montha, daya), LocalDate(yearb, monthb, dayb)) =>
  Year.eq(yeara, yearb)
  && Month.eq(montha, monthb)
  && DayOfMonth.eq(daya, dayb);

let compare =
    (LocalDate(yeara, montha, daya), LocalDate(yearb, monthb, dayb)) =>
  switch (Year.compare(yeara, yearb)) {
  | `equal_to =>
    switch (Month.compare(montha, monthb)) {
    | `equal_to => DayOfMonth.compare(daya, dayb)
    | v => v
    }
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
