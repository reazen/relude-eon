type t =
  | OffsetMinute(int);

module IntLike = {
  type nonrec t = t;
  let toInt = (OffsetMinute(m)) => m;
  let fromInt = m => OffsetMinute(m);
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsBastet.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = OffsetMinute(-720); // no offsets beyond -12:00 exist
  let top = OffsetMinute(840); // no offsets above +14:00 exist
};

module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);

let makeClamped = i => BoundExtras.clamp(OffsetMinute(i));
let make = i => BoundExtras.ensure(OffsetMinute(i));

let utc = makeClamped(0);

let getOffsetMinute = IntLike.toInt;
