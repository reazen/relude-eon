module Math = ReludeEon_DateMath;

type t =
  | Jan
  | Feb
  | Mar
  | Apr
  | May
  | Jun
  | Jul
  | Aug
  | Sep
  | Oct
  | Nov
  | Dec;

module IntLike1Based = {
  type nonrec t = t;
  let toInt =
    fun
    | Jan => 1
    | Feb => 2
    | Mar => 3
    | Apr => 4
    | May => 5
    | Jun => 6
    | Jul => 7
    | Aug => 8
    | Sep => 9
    | Oct => 10
    | Nov => 11
    | Dec => 12;

  let fromInt = i => {
    // force the provided value to be in the range 0...12 (inclusive)
    let (_, normalized) = Math.divWithRemainder(i, 12);

    switch (normalized) {
    | 1 => Jan
    | 2 => Feb
    | 3 => Mar
    | 4 => Apr
    | 5 => May
    | 6 => Jun
    | 7 => Jul
    | 8 => Aug
    | 9 => Sep
    | 10 => Oct
    | 11 => Nov
    | _ => Dec // the only remaining values are 0 and 12 (both Dec)
    };
  };
};

include ReludeEon_IntLike.MakeExtras(IntLike1Based);

module Bounded: BsBastet.Interface.BOUNDED with type t = t = {
  include Ord;
  let bottom = Jan;
  let top = Dec;
};

module WrappedExtras1Based =
  ReludeEon_IntLike.MakeBoundedExtras(IntLike1Based, Bounded);

let fromInt1BasedWrapped = i => WrappedExtras1Based.wrappedFromRing(i);
let fromInt1BasedClamped = i => WrappedExtras1Based.clampedFromRing(i);
let fromInt1Based = i => WrappedExtras1Based.ensureFromRing(i);

let fromInt0BasedWrapped = i => WrappedExtras1Based.wrappedFromRing(i + 1);
let fromInt0BasedClamped = i => WrappedExtras1Based.clampedFromRing(i + 1);
let fromInt0Based = i => WrappedExtras1Based.ensureFromRing(i + 1);

let toInt1Based = m => IntLike1Based.toInt(m);
let toInt0Based = m => IntLike1Based.toInt(m) - 1;

let addMonths = WrappedExtras1Based.addWrapped;
let next = v => addMonths(1, v);
let prev = v => addMonths(-1, v);

let totalDays = isLeapYear =>
  fun
  | Jan => 31
  | Feb when isLeapYear => 29
  | Feb => 28
  | Mar => 31
  | Apr => 30
  | May => 31
  | Jun => 30
  | Jul => 31
  | Aug => 31
  | Sep => 30
  | Oct => 31
  | Nov => 30
  | Dec => 31;
