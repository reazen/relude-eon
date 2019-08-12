module Hour = ReludeEon_Hour;
module Minute = ReludeEon_Minute;
module Second = ReludeEon_Second;
module Millisecond = ReludeEon_Millisecond;
module Math = ReludeEon_DateMath;

type t =
  | LocalTime(Hour.t, Minute.t, Second.t, Millisecond.t);

module IntLike = {
  type nonrec t = t;

  let toInt = (LocalTime(h, m, s, milli)) =>
    Math.sumMillis(
      Hour.getHour(h),
      Minute.getMinute(m),
      Second.getSecond(s),
      Millisecond.getMillisecond(milli),
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

let makeWrapped = (hour, minute, second, millisecond) => {
  let (_, h, m, s, ms) = Math.wrapTime(hour, minute, second, millisecond);
  LocalTime(
    Hour.makeClamped(h),
    Minute.makeClamped(m),
    Second.makeClamped(s),
    Millisecond.makeClamped(ms),
  );
};

let makeWrappedLabels = (~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  makeWrapped(hour, minute, second, millisecond);

let makeClamped = (hour, minute, second, millisecond) =>
  LocalTime(
    Hour.makeClamped(hour),
    Minute.makeClamped(minute),
    Second.makeClamped(second),
    Millisecond.makeClamped(millisecond),
  );

let makeClampedLabels = (~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  makeClamped(hour, minute, second, millisecond);

let addMilliseconds = WrappedExtras.addWrapped;
let addSeconds = howMany => addMilliseconds(Math.secondsToMillis(howMany));
let addMinutes = howMany => addMilliseconds(Math.minutesToMillis(howMany));
let addHours = howMany => addMilliseconds(Math.hoursToMillis(howMany));

let toTuple = (LocalTime(h, m, s, mi)) => (
  Hour.getHour(h),
  Minute.getMinute(m),
  Second.getSecond(s),
  Millisecond.getMillisecond(mi),
);

let getHour = (LocalTime(hour, _, _, _)) => Hour.getHour(hour);
let getMinute = (LocalTime(_, minute, _, _)) => Minute.getMinute(minute);
let getSecond = (LocalTime(_, _, second, _)) => Second.getSecond(second);
/* TODO: add asMilliseconds (== toInt, different from getMillisecond*/
let getMillisecond = (LocalTime(_, _, _, millisecond)) =>
  Millisecond.getMillisecond(millisecond);
