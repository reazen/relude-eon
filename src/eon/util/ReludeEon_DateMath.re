open Relude.Globals;

// integer division that returns both quotient and remainder
let divWithRemainder = (a, b) => {
  // mod function that always returns positive remainders
  let positiveMod = (a, b) => (a mod b + abs(b)) mod b;

  // divide two ints as a float
  let (/) = (a, b) => Int.toFloat(a) /. Int.toFloat(b);
  (Float.floorAsInt(a / b), positiveMod(a, b));
};

let secondsToMillis = s => s * 1000;
let minutesToMillis = m => secondsToMillis(m * 60);
let hoursToMillis = h => minutesToMillis(h * 60);

// takes different units of time as arguments, returns a tuple of
// (days, hours, minutes, seconds, millis)
// where each value is in the correct range, and `days` can be negative
let wrapTime = (hour, minute, second, ms) => {
  let (/) = divWithRemainder;
  let (s, milliseconds) = ms / 1000;
  let (m, seconds) = (second + s) / 60;
  let (h, minutes) = (minute + m) / 60;
  let (days, hours) = (hour + h) / 24;

  (days, hours, minutes, seconds, milliseconds);
};

let addHours = (howMany, h, m, s, ms) => wrapTime(h + howMany, m, s, ms);
let addMinutes = (howMany, h, m, s, ms) => wrapTime(h, m + howMany, s, ms);
let addSeconds = (howMany, h, m, s, ms) => wrapTime(h, m, s + howMany, ms);
let addMillis = (howMany, h, m, s, ms) => wrapTime(h, m, s, ms + howMany);
