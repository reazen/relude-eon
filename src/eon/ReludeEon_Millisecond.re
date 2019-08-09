type t =
  | Millisecond(int);

module IntLike = {
  type nonrec t = t;
  let toInt = (Millisecond(v)) => v;
  let fromInt = v => Millisecond(v);
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Millisecond(0);
  let top = Millisecond(999);
};

module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras = ReludeEon_IntLike.MakeBoundedExtras(IntLike, Bounded);

let makeWrapped = WrappedExtras.wrappedFromRing;
let makeClamped = i => BoundExtras.clamp(Millisecond(i));
let make = i => BoundExtras.ensure(Millisecond(i));

let addMilliseconds = WrappedExtras.addWrapped;
let getMilliseconds = IntLike.toInt;
