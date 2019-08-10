// integer division that returns both quotient and remainder
let divWithRemainder = (a, b) => (a / b, a mod b);

let secondsToMillis = s => s * 1000;
let minutesToMillis = m => secondsToMillis(m * 60);
let hoursToMillis = h => minutesToMillis(h * 60);
let sumMillis = (h, m, s, mil) =>
  hoursToMillis(h) + minutesToMillis(m) + secondsToMillis(s) + mil;

// wrapping helpers that return the number of the next-largest unit, plus the
// remainder, e.g. wrapMillis(1234) => (1, 234)
let millisToSeconds = ms => divWithRemainder(ms, 1000);
let secondsToMinutes = s => divWithRemainder(s, 60);
let minutesToHours = m => divWithRemainder(m, 60);
let hourstoDays = h => divWithRemainder(h, 24);

// takes different units of time as arguments, returns a tuple of
// (days, hours, minutes, seconds, millis)
// where each value is in the correct range
let wrapTime = (hour, minute, second, millisecond) => {
  let (s, milliseconds) = millisToSeconds(millisecond);
  let (m, seconds) = secondsToMinutes(second + s);
  let (h, minutes) = minutesToHours(minute + m);
  let (days, hours) = hourstoDays(hour + h);

  (days, hours, minutes, seconds, milliseconds);
};
