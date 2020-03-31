open BsBastet.Interface;
open Relude.Globals;

module type IntLike = {
  type t;
  let toInt: t => int;
  let fromInt: int => t;
};

module MakeExtras = (I: IntLike) => {
  module Eq = {
    type t = I.t;
    let eq = (a, b) => Int.eq(I.toInt(a), I.toInt(b));
  };

  module Ord = {
    include Eq;
    let compare = (a, b) => Int.compare(I.toInt(a), I.toInt(b));
  };

  let eq = Eq.eq;
  let compare = Ord.compare;
  include Relude_Extensions_Ord.OrdExtensions(Ord);
};

module MakeBoundedExtras = (I: IntLike, B: BOUNDED with type t = I.t) => {
  module IntCompat = {
    type t = I.t;
    type other = int;
    let toOther = I.toInt;
    let fromOther = I.fromInt;
  };

  include ReludeEon_Bounded.MakeRingLikeExtras(
            B,
            BsBastet.Int.Euclidean_Ring,
            Int.Ord,
            IntCompat,
          );
};
