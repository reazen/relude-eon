open Relude.Globals;

type t =
  | DayOfMonth(int);

let fromInt = v => DayOfMonth(v);

let eq = (DayOfMonth(a), DayOfMonth(b)) => a == b;

let compare = (DayOfMonth(a), DayOfMonth(b)) => Int.compare(a, b);

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = eq;
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = compare;
};

include Relude_Extensions_Ord.Make(Ord);
