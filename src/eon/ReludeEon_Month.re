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

let fromInt1Based = i =>
  i >= 1 && i <= 12 ? Some(fromInt1BasedWrapped(i)) : None;

let fromInt0BasedWrapped = i => fromInt1BasedWrapped(i + 1);

let fromInt0Based = i => fromInt1Based(i + 1);

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

let toInt0Based = v => toInt1Based(v) - 1;

let addMonths = (howMany, v) =>
  fromInt1BasedWrapped(toInt1Based(v) + howMany);

let next = v => addMonths(1, v);

let prev = v => addMonths(-1, v);

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

let compare = (a, b) => Int.compare(toInt1Based(a), toInt1Based(b));

let eq = (a, b) => compare(a, b) == `equal_to;

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = compare;
};

include Relude_Extensions_Ord.Make(Ord);
