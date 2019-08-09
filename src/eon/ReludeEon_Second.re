open Relude.Globals;

type t =
  | Second(int);

module Eq: BsAbstract.Interface.EQ with type t = t = {
  type nonrec t = t;
  let eq = (Second(a), Second(b)) => Int.eq(a, b);
};

module Ord: BsAbstract.Interface.ORD with type t = t = {
  include Eq;
  let compare = (Second(a), Second(b)) => Int.compare(a, b);
};

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Second(0);
  let top = Second(59);
};

// private, but useful internally
module IntCompat = {
  type nonrec t = t;
  type other = int;
  let toOther = (Second(m)) => m;
  let fromOther = i => Second(i);
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
let makeClamped = i => BoundExtras.clamp(Second(i));
let make = i => BoundExtras.ensure(Second(i));

let addSeconds = WrappedExtras.addWrapped;
let getSeconds = IntCompat.toOther;

let eq = Eq.eq;
let compare = Ord.compare;
include Relude_Extensions_Ord.Make(Ord);
