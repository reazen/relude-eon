module LocalDateTime = ReludeEon_LocalDateTime;

type t =
  | InstantUTC(LocalDateTime.t);

let fromLocalDateTime = dt => InstantUTC(dt);

let getLocalDateTime = (InstantUTC(dt)) => dt;

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = (InstantUTC(a), InstantUTC(b)) => LocalDateTime.eq(a, b);
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = (InstantUTC(a), InstantUTC(b)) =>
    LocalDateTime.compare(a, b);
};

let eq = Eq.eq;
let compare = Ord.compare;
include Relude_Extensions_Ord.Make(Ord);
