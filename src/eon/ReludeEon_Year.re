open Relude.Globals;

type t =
  | Year(int);

let isLeapYear = (Year(year)) =>
  year mod 4 == 0 && (year mod 100 != 0 || year mod 400 == 0);

let addYears = (howMany, Year(year)) => Year(year + howMany);

let next = year => addYears(1, year);

let prev = year => addYears(-1, year);

let eq = (Year(a), Year(b)) => a == b;

let compare = (Year(a), Year(b)) => Int.compare(a, b);

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = compare;
};

include Relude_Extensions_Ord.Make(Ord);
