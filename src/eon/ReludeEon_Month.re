open Relude.Globals;

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
let fromInt1BasedWrapped = i => {
  // force the provided value to be in the range 0...12 (inclusive)
  let normalized =
    if (i > 12) {
      i mod 12;
    } else if (i < 0) {
      let multiplier =
        Float.abs(Float.fromInt(i)) /. 12.0 |> Float.ceilAsInt;
      i + 12 * multiplier;
    } else {
      i;
    };

  switch (normalized) {
  | 1 => Jan
  | 2 => Feb
  | 3 => Mar
  | 4 => Apr
  | 5 => May
  | 6 => Jun
  | 7 => Jul
  | 8 => Aug
  | 9 => Sep
  | 10 => Oct
  | 11 => Nov
  | _ => Dec // the only remaining values are 0 and 12 (both Dec)
  };
};

/**
 * Given an int in the range 1...12 (inclusive), return `Some(Month.t)`. If the
 * provided int falls outside that range, `None` is returned.
 */
let fromInt1Based = i =>
  i >= 1 && i <= 12 ? Some(fromInt1BasedWrapped(i)) : None;

/**
 * Given any int, return a `Month.t` where `0 => Jan` and `11 => Dec`. Values
 * outside tof the range 0...11 will be wrapped, such athat `12 => Jan` and
 * `-1 => Dec`
 */
let fromInt0BasedWrapped = i => fromInt1BasedWrapped(i + 1);

/**
 * Given an int in the range 0...11 (inclusive), return `Some(Month.t)`. If the
 * provided int falls outside that range, `None` is returned.
 */
let fromInt0Based = i => fromInt1Based(i + 1);

/**
 * Convert a `Month.t` to an integer value in the range 1...12.
 */
let toInt1Based =
  fun
  | Jan => 1
  | Feb => 2
  | Mar => 3
  | Apr => 4
  | May => 5
  | Jun => 6
  | Jul => 7
  | Aug => 8
  | Sep => 9
  | Oct => 10
  | Nov => 11
  | Dec => 12;

/**
 * Convert a `Month.t` to an integer value in the range 0...11.
 */
let toInt0Based = v => toInt1Based(v) - 1;

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
let addMonths = (howMany, v) =>
  fromInt1BasedWrapped(toInt1Based(v) + howMany);

/**
 * Return the month following the provided month.
 *
 * ```reason
 * Month.next(Mar) == Apr;
 * Month.next(Dec) == Jan;
 * ```
 */
let next = v => addMonths(1, v);

/**
 * Return the month prior to the provided month.
 *
 * ```reason
 * Month.prev(Nov) == Oct;
 * Month.prev(Jan) == Dec;
 * ```
 */
let prev = v => addMonths(-1, v);

/**
 * Return the count of days in the month, handling Feb with a lear year flag
 *
 * ```reason
 * Month.totalDays(false, Mar) => 31;
 * Month.totalDays(true, Feb) => 29;
 * ```
 */
let totalDays = isLeapYear =>
  fun
  | Jan => 31
  | Feb when isLeapYear => 29
  | Feb => 28
  | Mar => 31
  | Apr => 30
  | May => 31
  | Jun => 30
  | Jul => 31
  | Aug => 31
  | Sep => 30
  | Oct => 31
  | Nov => 30
  | Dec => 31;

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
let compare = (a, b) => Int.compare(toInt1Based(a), toInt1Based(b));

/**
 * Determine whether two month values are the same
 */
let eq = (a, b) => compare(a, b) == `equal_to;
