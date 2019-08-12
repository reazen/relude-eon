type t =
  | Second(int);

module IntLike = {
  type nonrec t = t;
  let toInt = (Second(m)) => m;
  let fromInt = i => Second(i);
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Second(0);
  let top = Second(59);
};

// private, but useful internally
module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras = ReludeEon_IntLike.MakeBoundedExtras(IntLike, Bounded);

let makeWrapped = i => WrappedExtras.wrappedFromRing(i);
let makeClamped = i => BoundExtras.clamp(Second(i));
let make = i => BoundExtras.ensure(Second(i));

let addSeconds = WrappedExtras.addWrapped;
let getSecond = IntLike.toInt;
