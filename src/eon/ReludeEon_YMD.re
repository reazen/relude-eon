module Year = ReludeEon_Year;
module Month = ReludeEon_Month;
module DayOfMonth = ReludeEon_DayOfMonth;

type t =
  | YMD(Year.t, Month.t, DayOfMonth.t);

let daysInMonth = (YMD(year, month, _)) =>
  Month.totalDays(Year.isLeapYear(year), month);

// -----------------------------------------------------------------------------
// # Private
//
// The following functions are private (hidden from the interface) because they
// can produce invalid days of the month, or they're only useful when working
// with potentially invalid days of the month (which is useful internally, but
// shouldn't be possible outside of this module).
// -----------------------------------------------------------------------------

let unsafeWithDay = (day, YMD(year, month, _)) =>
  YMD(year, month, DayOfMonth.fromInt(day));

let unsafePrevMonth = (YMD(year, month, day)) => {
  let year = Month.eq(month, Jan) ? Year.prev(year) : year;
  YMD(year, Month.prev(month), day);
};

let unsafeNextMonth = (YMD(year, month, day)) => {
  let year = Month.eq(month, Dec) ? Year.next(year) : year;
  YMD(year, Month.next(month), day);
};

let clampDay = (YMD(year, month, day) as ymd) => {
  let max = DayOfMonth.fromInt(daysInMonth(ymd));
  let clamped = DayOfMonth.clamp(~min=DayOfMonth.fromInt(1), ~max, day);
  YMD(year, month, clamped);
};

let rec wrap = (YMD(_, _, DayOfMonth(day)) as ymd) => {
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
  wrap(YMD(Year(year), month, DayOfMonth(day)));

let makeClamped = (year, month, day) =>
  clampDay(YMD(Year(year), month, DayOfMonth(day)));

let make = (year, month, day) => {
  let ymd = YMD(Year(year), month, DayOfMonth(day));
  day <= 0 || day > daysInMonth(ymd) ? None : Some(ymd);
};

// getters, since constructor is private
let toTuple = (YMD(Year(year), month, DayOfMonth(day))) => (year, month, day);
let getYear = (YMD(Year(year), _, _)) => year;
let getMonth = (YMD(_, month, _)) => month;
let getDayOfMonth = (YMD(_, _, DayOfMonth(day))) => day;

let prevMonth = ymd => clampDay(unsafePrevMonth(ymd));
let nextMonth = ymd => clampDay(unsafeNextMonth(ymd));

let addDays = (howMany, YMD(_, _, DayOfMonth(day)) as ymd) =>
  wrap(unsafeWithDay(day + howMany, ymd));

let nextDay = ymd => addDays(1, ymd);
let prevDay = ymd => addDays(-1, ymd);

let isLeapYear = (YMD(year, _, _)) => Year.isLeapYear(year);

let daysInYear = (YMD(year, _, _)) => Year.totalDays(year);

let eq = (YMD(yeara, montha, daya), YMD(yearb, monthb, dayb)) =>
  Year.eq(yeara, yearb)
  && Month.eq(montha, monthb)
  && DayOfMonth.eq(daya, dayb);

let compare = (YMD(yeara, montha, daya), YMD(yearb, monthb, dayb)) =>
  switch (Year.compare(yeara, yearb)) {
  | `equal_to =>
    switch (Month.compare(montha, monthb)) {
    | `equal_to => DayOfMonth.compare(daya, dayb)
    | v => v
    }
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

include Relude_Extensions_Ord.Make(Ord);
