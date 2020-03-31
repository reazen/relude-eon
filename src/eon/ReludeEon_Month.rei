type t =
  | Jan
  | Feb
  | Mar
  | Apr
  | May
  | Jun
  | Jul
  | Aug
  | Sep
  | Oct
  | Nov
  | Dec;

/**
 * Given any int, return a `Month.t` where `1 => Jan` and `12 => Dec`. Values
 * outside of the range 1...12 will be wrapped, such that `13 => Jan` and
 * `0 => Dec`.
 */
let fromInt1BasedWrapped: int => t;

/**
 * Given any int, return a `Month.t` where values <= 1 are `Jan`, and values
 * >=12 are `Dec`. All other ints correspond with the 1-based Month.
 */
let fromInt1BasedClamped: int => t;

/**
 * Given an int in the range 1...12 (inclusive), return `Some(Month.t)`. If the
 * provided int falls outside that range, `None` is returned.
 */
let fromInt1Based: int => option(t);

/**
 * Given any int, return a `Month.t` where `0 => Jan` and `11 => Dec`. Values
 * outside tof the range 0...11 will be wrapped, such athat `12 => Jan` and
 * `-1 => Dec`
 */
let fromInt0BasedWrapped: int => t;

/**
 * Given any int, return a `Month.t` where values <= 0 are `Jan`, and values
 * >=11 are `Dec`. All other ints correspond with the 0-based Month.
 */
let fromInt0BasedClamped: int => t;


/**
 * Given an int in the range 0...11 (inclusive), return `Some(Month.t)`. If the
 * provided int falls outside that range, `None` is returned.
 */
let fromInt0Based: int => option(t);

/**
 * Convert a `Month.t` to an integer value in the range 1...12.
 */
let toInt1Based: t => int;

/**
 * Convert a `Month.t` to an integer value in the range 0...11.
 */
let toInt0Based: t => int;

/**
 * Given an int and a current month, find the month that comes _that many_ after
 * (for a positive int) or before (for a negative int) the provided month.
 *
 * ```reason
 * Month.addMonths(5, Feb) == Jul;
 * Month.addMonths(-4, Jan) == Sep;
 * Month.addMonths(0, Aug) == Aug;
 * ```
 */
let addMonths: (int, t) => t;

/**
 * Return the month following the provided month.
 *
 * ```reason
 * Month.next(Mar) == Apr;
 * Month.next(Dec) == Jan;
 * ```
 */
let next: t => t;

/**
 * Return the month prior to the provided month.
 *
 * ```reason
 * Month.prev(Nov) == Oct;
 * Month.prev(Jan) == Dec;
 * ```
 */
let prev: t => t;

/**
 * Return the count of days in the month, handling Feb with a lear year flag
 *
 * ```reason
 * Month.totalDays(false, Mar) => 31;
 * Month.totalDays(true, Feb) => 29;
 * ```
 */
let totalDays: (bool, t) => int;

/**
 * Given two months, determine whether the first is greater than, less than, or
 * equal to the second month.
 *
 * ```reason
 * Month.compare(Jan, Sep) == `less_than;
 * Month.compare(Jul, Jul) == `equal_to;
 * Month.compare(Feb, Jan) == `greater_than;
 * ```
 */
let compare: (t, t) => BsBastet.Interface.ordering;

/**
 * Determine whether two month values are the same
 */
let eq: (t, t) => bool;

module Eq: BsBastet.Interface.EQ with type t = t;
module Ord: BsBastet.Interface.ORD with type t = t;

/**
 * Compare two months, returning `1` if the first is greater, `0` if they are
 * equal, and `-1` if the first is smaller.
 */
let compareAsInt: (t, t) => int;

/**
 * Given two month values, return the smallest
 */
let min: (t, t) => t;

/**
 * Given two month values, return the largest
 */
let max: (t, t) => t;

/**
 * Given two months, `lessThan` returns `true` if the first is smaller than the
 * second
 */
let lessThan: (t, t) => bool;

/**
 * Given two months, `lessThanOrEq` returns `true` if the first is smaller or
 * equal to the second
 */
let lessThanOrEq: (t, t) => bool;

/**
 * Given two months, `greaterThan` returns `true` if the first is larger than
 * the second
 */
let greaterThan: (t, t) => bool;

/**
 * Given two months, `greaterThanOrEq` returns `true` if the first is larger
 * or equal to the second
 */
let greaterThanOrEq: (t, t) => bool;

/**
 * Given two months, `lt` returns `true` if the first is smaller than the second
 */
let lt: (t, t) => bool;

/**
 * Given two months, `lte` returns `true` if the first is smaller or equal to
 * the second
 */
let lte: (t, t) => bool;

/**
 * Given two months, `gt` returns `true` if the first is larger than the second
 */
let gt: (t, t) => bool;

/**
 * Given two months, `gte` returns `true` if the first is larger or equal to the
 * second
 */
let gte: (t, t) => bool;

/**
 * Ensure the given month falls between (inclusive) the provided min and max.
 *
 * ```reason
 * Month.clamp(~min=Jun, ~max=Oct, Nov) == Oct;
 * ```
 */
let clamp: (~min: t, ~max: t, t) => t;

/**
 * Determine whether a given month falls between (inclusive) a provided min and
 * max.
 *
 * ```reason
 * Month.between(~min=Apr, ~max=Jun, Jun) == true;
 * ```
 */
let between: (~min: t, ~max: t, t) => bool;
