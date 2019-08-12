type t =
  | Minute(int);

module IntLike = {
  type nonrec t = t;
  let toInt = (Minute(v)) => v;
  let fromInt = v => Minute(v);
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Minute(0);
  let top = Minute(59);
};

// private, but useful internally
module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras = ReludeEon_IntLike.MakeBoundedExtras(IntLike, Bounded);

let makeWrapped = i => WrappedExtras.wrappedFromRing(i);
let makeClamped = i => BoundExtras.clamp(Minute(i));
let make = i => BoundExtras.ensure(Minute(i));

let addMinutes = WrappedExtras.addWrapped;
let getMinute = IntLike.toInt;
