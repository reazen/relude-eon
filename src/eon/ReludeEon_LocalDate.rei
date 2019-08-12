type t;

/**
 * For a given LocalDate, return the total number of days in the month.
 *
 * ```reason
 * daysInMonth(makeClamped(2019, Jan, 12)) == 31;
 * daysInMonth(makeClamped(2020, Feb, 1)) == 29;
 * ```
 */
let daysInMonth: t => int;

/**
 * Construct a LocalDate from a year int, a Month, and a 1-based day-of-month
 * int. If the provided day-of-month is out of range for the combination of
 * year/month, the month and year will be increased or decreased as necessary to
 * produce a valid date.
 *
 * ```reason
 * makeWrapped(2019, Feb, 29) == makeWrapped(2019, Mar, 1);
 * makeWrapped(2018, Jan, 0) == makeWrapped(2017, Dec, 31);
 * ```
 */
let makeWrapped: (int, ReludeEon_Month.t, int) => t;

/**
 * Construct a LocalDate from a year int, a Month, and a 1-based day-of-month
 * int. If the provided day-of-month is not a valid day in the given Month, it
 * will be clamped in the range `1...daysInMonth(month)` (e.g. between 1 and 31
 * inclusive for January).
 *
 * ```reason
 * makeClamped(2020, Feb, 30) == makeClamped(2020, Feb, 29);
 * ```
 */
let makeClamped: (int, ReludeEon_Month.t, int) => t;

/**
 * Construct a LocalDate from a year int, a Month, and a 1-based day-of-month
 * int. If the provided day-of-month wouldn't be a valid day in the given month,
 * `None` is returned.
 *
 * ```reason
 * make(2020, Feb, 29); // Some(...)
 * make(2019, Feb, 29); // None
 * ```
 */
let make: (int, ReludeEon_Month.t, int) => option(t);

/**
 * Given a LocalDate, return a tuple (year, month, day). Use this when pattern
 * matching, since the actual LocalDate type is hidden to prevent incorrect
 * construction.
 */
let toTuple: t => (int, ReludeEon_Month.t, int);

/**
 * Extract the year as an `int`
 */
let getYear: t => int;

/**
 * Extract the month.
 */
let getMonth: t => ReludeEon_Month.t;

/**
 * Extract the 1-based day-of-month as an `int`
 */
let getDayOfMonth: t => int;

/**
 * Add an `int` number of years to a LocalDaate. When starting on a leap year
 * and ending on a non-leap year, Feb 29 will turn into Feb 28.
 */
let addYears: (int, t) => t;

/**
 * Subtract one year from a given local date, clamping Feb 29 to Feb 28 if
 * necessary.
 */
let prevYear: t => t;

/**
 * Add one year to a given local date, clamping Feb 29 to Feb 28 if necessary.
 */
let nextYear: t => t;

/**
 * Add an `int` number of months to a LocalDate, rolling the year forward or
 * backward as necessary. If the dayOfMonth would exceed the valid number of
 * days in the resulting month, it's clamped to the end of the month.
 *
 * ```reason
 * addMonths(-2, makeClamped(2019, Jan, 1)) == makeClamped(2018, Nov, 1);
 * addMonths(13, makeClamped(2019, Jan, 31)) == makeClamped(2020, Mar, 31);
 * ```
 */
let addMonths: (int, t) => t;

/**
 * Returns a new LocalDate representing the same point in the previous month.
 * The new date is clamped to the range of valid days in the new month. When
 * given a Jan date, `prevMonth` will return a date in Dec of the previous year.
 *
 * ```reason
 * prevMonth(makeClamped(2019, Jan, 18)) == makeClamped(2018, Dec, 18);
 * prevMonth(makeClamped(2019, May, 31)) == makeClamped(2019, Apr, 30);
 * ```
 */
let prevMonth: t => t;

/**
 * Returns a new LocalDate representing the same point in the next month. The
 * new date is clamped to the range of valid days in the new month. When given a
 * Dec date, `nextMonth` will return a date in Jan of the next year.
 *
 * ```reason
 * nextMonth(makeClamped(2020, Jan, 31)) == makeClamped(2020, Feb, 29);
 * nextMonth(makeClamped(2017, Dec, 31)) == makeClamped(2018, Jan, 31);
 * ```
 */
let nextMonth: t => t;

/**
 * Add an `int` number of days to a LocalDate. The year and month will be rolled
 * forward or backward as necessary.
 *
 * ```reason
 * addDays(-7, makeClamped(2019, Jan, 1)) == makeClamped(2018, Dec, 25);
 * ```
 */
let addDays: (int, t) => t;

/**
 * Add one day to a given LocalDate. This will roll the month (and even year)
 * forward if necessary.
 *
 * ```reason
 * nextDay(makeClamped(2015, Jan, 31)) == makeClamped(2015, Feb, 1);
 * ```
 */
let nextDay: t => t;

/**
 * Subtract one day from a given LocalDate. This will roll the month (and even
 * year) backward if necessary.
 *
 * ```reason
 * prevDay(makeClamped(2019, Apr, 1)) == makeClamped(2019, Mar, 31);
 * ```
 */
let prevDay: t => t;

/**
 * Given a LocalDate, returns true if the year is a leap year.
 */
let isLeapYear: t => bool;

/**
 * Returns the total number of days in a LocalDate's year: 366 for leap years,
 * 365 for all others.
 */
let daysInYear: t => int;

/**
 * Determine whether two LocalDate values have the same year, month, and day.
 */
let eq: (t, t) => bool;

/**
 * Determine whether the first of two LocalDate values is less than, greater
 * than, or equal to the second.
 *
 * ```reason
 * let nov2019 = makeClamped(2019, Nov, 30);
 * let jan2020 = makeClamped(2020, Jan, 4);
 * compare(nov2019, jan2020) == `less_than;
 * ```
 */
let compare: (t, t) => BsAbstract.Interface.ordering;

module Eq: BsAbstract.Interface.EQ with type t = t;
module Ord: BsAbstract.Interface.ORD with type t = t;

/**
 * Compare two LocalDate values, returning `1` if the first is greater than the
 * second, `-1` if it's smaller, or `0` if the two are equal.
 */
let compareAsInt: (t, t) => int;

/**
 * Return the smaller of two LocalDate values
 */
let min: (t, t) => t;

/**
 * Return the larger of two LocalDate values
 */
let max: (t, t) => t;

/**
 * Determine whether the first LocalDate value is smaller than the second.
 */
let lessThan: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is smaller than or equal to the
 * second.
 */
let lessThanOrEq: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is greater than the second.
 */
let greaterThan: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is greater than or equal to the
 * second.
 */
let greaterThanOrEq: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is smaller than the second.
 */
let lt: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is smaller than or equal to the
 * second.
 */
let lte: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is greater than the second.
 */
let gt: (t, t) => bool;

/**
 * Determine whether the first LocalDate value is greater than or equal to the
 * second.
 */
let gte: (t, t) => bool;

/**
 * Ensure that a LocalDate value falls between a provided min and max.
 */
let clamp: (~min: t, ~max: t, t) => t;

/**
 * Determine whether a LocalDate value falls between a provided min and max.
 */
let between: (~min: t, ~max: t, t) => bool;
