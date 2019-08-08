type t =
  | Year(int);

/**
 * Determine whether a year is a leap year (i.e. its February has 29 days). The
 * rule is: a year is a leap year if it's divisible by 4, unless it's divisible
 * by 100. Years divisible by 400 are also leap years.
 */
let isLeapYear: t => bool;

/**
 * Find the total number of days in the year. Leap years have 366, all others
 * have 365.
 */
let totalDays: t => int;

/**
 * Increase a year by a given int.
 */
let addYears: (int, t) => t;

/**
 * Increase the year by 1.
 */
let next: t => t;

/**
 * Decrease the year by 1.
 */
let prev: t => t;

/**
 * Determine whether two years are equal.
 */
let eq: (t, t) => bool;

/**
 * Given two years, determine whether the first is less than, greater than, or
 * equal to the second.
 */
let compare: (t, t) => BsAbstract.Interface.ordering;

module Eq: BsAbstract.Interface.EQ with type t = t;
module Ord: BsAbstract.Interface.ORD with type t = t;

/**
 * Compare two years for `ordering`, returning `1` if the first is greater than
 * the second, `-1` if it's less, or `0` if the two are equal.
 */
let compareAsInt: (t, t) => int;

/**
 * Return the smaller of two years
 */
let min: (t, t) => t;

/**
 * Return the larger of two years
 */
let max: (t, t) => t;

/**
 * Determine whether the first year is smaller than the second.
 */
let lessThan: (t, t) => bool;

/**
 * Determine whether the first year is smaller than or equal to the second.
 */
let lessThanOrEq: (t, t) => bool;

/**
 * Determine whether the first year is greater than the second.
 */
let greaterThan: (t, t) => bool;

/**
 * Determine whether the first year is greater than or equal to the second.
 */
let greaterThanOrEq: (t, t) => bool;

/**
 * Determine whether the first year is smaller than the second.
 */
let lt: (t, t) => bool;

/**
 * Determine whether the first year is smaller than or equal to the second.
 */
let lte: (t, t) => bool;

/**
 * Determine whether the first year is greater than the second.
 */
let gt: (t, t) => bool;

/**
 * Determine whether the first year is greater than or equal to the second.
 */
let gte: (t, t) => bool;

/**
 * Ensure that a year falls between a provided min and max year.
 */
let clamp: (~min: t, ~max: t, t) => t;

/**
 * Determine whether a year falls between a provided min and max year.
 */
let between: (~min: t, ~max: t, t) => bool;
