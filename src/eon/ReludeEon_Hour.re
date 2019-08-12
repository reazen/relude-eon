type t =
  | Hour(int);

module IntLike = {
  type nonrec t = t;
  let toInt = (Hour(v)) => v;
  let fromInt = v => Hour(v);
};

include ReludeEon_IntLike.MakeExtras(IntLike); // Eq and Ord

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Hour(0);
  let top = Hour(23);
};

// private, but useful internally
module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras = ReludeEon_IntLike.MakeBoundedExtras(IntLike, Bounded);

let makeWrapped = i => WrappedExtras.wrappedFromRing(i);
let makeClamped = i => BoundExtras.clamp(Hour(i));
let make = i => BoundExtras.ensure(Hour(i));

let addHours = WrappedExtras.addWrapped;
let getHour = IntLike.toInt;
