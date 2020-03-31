open Relude.Globals;

module Hour = ReludeEon_Hour;
module Minute = ReludeEon_Minute;
module Second = ReludeEon_Second;
module Millisecond = ReludeEon_Millisecond;
module Math = ReludeEon_DateMath;

type t =
  | LocalTime(Hour.t, Minute.t, Second.t, Millisecond.t);

let unsafeFromMillisecond = ms => {
  let (/) = Math.divWithRemainder;
  let (hours, remainder) = ms / (60 * 60 * 1000);
  let (minutes, remainder) = remainder / (60 * 1000);
  let (seconds, millis) = remainder / 1000;

  (hours, minutes, seconds, millis);
};

let fromMillisecondsWrapped = ms => {
  let (h, m, s, ms) = unsafeFromMillisecond(ms);
  LocalTime(
    Hour.makeWrapped(h),
    Minute.makeClamped(m),
    Second.makeClamped(s),
    Millisecond.makeClamped(ms),
  );
};

let fromMillisecondsClamped = ms => {
  let (h, m, s, ms) =
    unsafeFromMillisecond(Int.clamp(~min=0, ~max=86399999, ms));

  LocalTime(
    Hour.makeClamped(h),
    Minute.makeClamped(m),
    Second.makeClamped(s),
    Millisecond.makeClamped(ms),
  );
};

module IntLike = {
  type nonrec t = t;

  let toInt = (LocalTime(h, m, s, ms)) =>
    Math.hoursToMillis(Hour.getHour(h))
    + Math.minutesToMillis(Minute.getMinute(m))
    + Math.secondsToMillis(Second.getSecond(s))
    + Millisecond.getMillisecond(ms);

  let fromInt = fromMillisecondsWrapped;
};

include ReludeEon_IntLike.MakeExtras(IntLike);

module Bounded: BsBastet.Interface.BOUNDED with type t = t = {
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
    Minute.makeClamped(abs(minute)),
    Second.makeClamped(abs(second)),
    Millisecond.makeClamped(millisecond),
  );

let makeClampedLabels = (~hour=0, ~minute=0, ~second=0, ~millisecond=0, ()) =>
  makeClamped(hour, minute, second, millisecond);

let midnight = Bounded.bottom;
let noon = makeClamped(12, 0, 0, 0);

let toTuple = (LocalTime(h, m, s, ms)) => (
  Hour.getHour(h),
  Minute.getMinute(m),
  Second.getSecond(s),
  Millisecond.getMillisecond(ms),
);

let getHour = (LocalTime(hour, _, _, _)) => Hour.getHour(hour);
let getMinute = (LocalTime(_, minute, _, _)) => Minute.getMinute(minute);
let getSecond = (LocalTime(_, _, second, _)) => Second.getSecond(second);
let getMillisecond = (LocalTime(_, _, _, millisecond)) =>
  Millisecond.getMillisecond(millisecond);

/* TODO: add asMilliseconds (== toInt, different from getMillisecond*/

let add = (fn, time) => {
  let (hour, minute, second, milli) = toTuple(time);
  let (_, h, m, s, ms) = fn(hour, minute, second, milli);
  makeClamped(h, m, s, ms);
};

let addHours = howMany => add(Math.addHours(howMany));
let prevHour = addHours(-1);
let nextHour = addHours(1);

let addMinutes = howMany => add(Math.addMinutes(howMany));
let prevMinute = addMinutes(-1);
let nextMinute = addMinutes(1);

let addSeconds = howMany => add(Math.addSeconds(howMany));
let prevSecond = addSeconds(-1);
let nextSecond = addSeconds(1);

let addMilliseconds = howMany => add(Math.addMillis(howMany));
let prevMillisecond = addMilliseconds(-1);
let nextMillisecond = addMilliseconds(1);
