open Relude.Globals;

type t =
  | Minute(int);

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = (Minute(a), Minute(b)) => Int.eq(a, b);
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = (Minute(a), Minute(b)) => Int.compare(a, b);
};

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Minute(0);
  let top = Minute(59);
};

// private, but useful internally
module IntCompat = {
  type nonrec t = t;
  type other = int;
  let toOther = (Minute(m)) => m;
  let fromOther = i => Minute(i);
};

module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras =
  ReludeEon_Bounded.MakeRingLikeExtras(
    Bounded,
    BsAbstract.Int.Euclidean_Ring,
    Int.Ord,
    IntCompat,
  );

let makeWrapped = i => WrappedExtras.wrappedFromRing(i);
let makeClamped = i => BoundExtras.clamp(Minute(i));
let make = i => BoundExtras.ensure(Minute(i));

let addMinutes = WrappedExtras.addWrapped;
let getMinutes = IntCompat.toOther;

let eq = Eq.eq;
let compare = Ord.compare;
include Relude_Extensions_Ord.Make(Ord);
