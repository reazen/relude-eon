// integer division that returns both quotient and remainder

let positiveMod = (a, b) =>
  if (abs(a) == abs(b)) {
    0; // (-60 mod 60) kept turning into -0 instead of 0, which made tests fail
  } else {
    let remainder = a mod b;
    remainder < 0 ? remainder + b : remainder;
  };

let divWithRemainder = (a, b) => {
  let floatDiv = floor(float_of_int(a) /. float_of_int(b));
  (int_of_float(floatDiv), positiveMod(a, b));
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
