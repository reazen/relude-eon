module Hour = ReludeEon_Hour;
module Minute = ReludeEon_Minute;
module Second = ReludeEon_Second;
module Millisecond = ReludeEon_Millisecond;

type t =
  | LocalTime(Hour.t, Minute.t, Second.t, Millisecond.t);

// private helpers to convert non-millisecond units to millseconds
let secondsToMillis = s => s * 1000;
let minutesToMillis = m => secondsToMillis(m * 60);
let hoursToMillis = h => minutesToMillis(h * 60);
let sumMillis = (h, m, s, mil) =>
  hoursToMillis(h) + minutesToMillis(m) + secondsToMillis(s) + mil;

module IntLike = {
  type nonrec t = t;

  let toInt = (LocalTime(h, m, s, milli)) =>
    sumMillis(
      Hour.getHours(h),
      Minute.getMinutes(m),
      Second.getSeconds(s),
      Millisecond.getMilliseconds(milli),
    );

  let fromInt = i => {
    let (/) = (a, b) => (a / b, a mod b);
    let (hours, remainder) = i / (60 * 60 * 1000);
    let (minutes, remainder) = remainder / (60 * 1000);
    let (seconds, millis) = remainder / 1000;
    LocalTime(
      Hour.makeClamped(hours),
      Minute.makeClamped(minutes),
      Second.makeClamped(seconds),
      Millisecond.makeClamped(millis),
    );
  };
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsAbstract.Interface.BOUNDED with type t = t = {
  include Ord;

  let bottom =
    LocalTime(
      Hour.Bounded.bottom,
      Minute.Bounded.bottom,
      Second.Bounded.bottom,
      Millisecond.Bounded.bottom,
    );

  let top =
    LocalTime(
      Hour.Bounded.top,
      Minute.Bounded.top,
      Second.Bounded.top,
      Millisecond.Bounded.top,
    );
};

module BoundExtras = ReludeEon_Bounded.MakeExtras(Bounded);
module WrappedExtras = ReludeEon_IntLike.MakeBoundedExtras(IntLike, Bounded);

let fromMillisecondsWrapped = ms => WrappedExtras.wrappedFromRing(ms);
let fromMillisecondsClamped = ms => BoundExtras.clamp(IntLike.fromInt(ms));

let makeWrappedLabels = (~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  fromMillisecondsWrapped(sumMillis(hour, minute, second, millisecond));

let makeClampedLabels = (~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  fromMillisecondsClamped(sumMillis(hour, minute, second, millisecond));

let addMilliseconds = WrappedExtras.addWrapped;
let addSeconds = howMany => addMilliseconds(secondsToMillis(howMany));
let addMinutes = howMany => addMilliseconds(minutesToMillis(howMany));
let addHours = howMany => addMilliseconds(hoursToMillis(howMany));

let toTuple = (LocalTime(h, m, s, mi)) => (
  Hour.getHours(h),
  Minute.getMinutes(m),
  Second.getSeconds(s),
  Millisecond.getMilliseconds(mi),
);

// TODO: add getHours, get...
// TODO: add asMilliseconds (== toInt, different from getMilliseconds)
