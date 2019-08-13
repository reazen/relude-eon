# Relude Eon

[![build status](https://img.shields.io/circleci/project/github/reazen/relude-eon/master.svg)](https://circleci.com/gh/reazen/relude-eon)
[![test coverage](https://img.shields.io/coveralls/github/reazen/relude-eon.svg)](https://coveralls.io/github/reazen/relude-eon)
[![npm version](https://img.shields.io/npm/v/relude-eon.svg)](https://www.npmjs.com/package/relude-eon)
[![license](https://img.shields.io/github/license/reazen/relude-eon.svg)](https://github.com/reazen/relude-eon/blob/master/LICENSE)

Relude Eon is a ReasonML library for working with type-safe date and time values in a sane way.

## Installation

**Install via npm:**

`npm install --save relude-eon`

**Update your bsconfig.json**

```
"bs-dependencies": [
  "relude-eon"
],
```

Eon has `peerDependencies` on `relude` and `bs-abstract`, so make sure to `npm install --save relude bs-abstract` and add them to your `bsconfig.json`.

## Project Status

This just might be useful!

### Things That Work

- All of the core building blocks are there (see below)
- The useful types (e.g. `Instant`, `LocalDate`, `LocalTime`) all support basic date math
- Basic interop with `Js.Date` exists
- Most things have at least _some_ tests

### Not Quite Yet

- Durations (for generic date math, building ranges, etc)
- Weekdays
- String functions (parsers, formatters)
- Timezones (we have offsets, but currently there's no support for named zones, daylight savings time, etc)

### Currently Out-Of-Scope

- Julian Calendar (leap years are calculated based on the Gregorian calendar, no mattter how far back in time you go)
- Leap Seconds ([there's a plan](https://github.com/reazen/relude-eon/issues/4), but it isn't currently a priority)
- Native (we're currently Bucklescript-only, but that's mostly because of our dependencies)

## Core Concepts

Dates in Eon are built from smaller, typed building blocks. These building blocks can be combined to form more complex types that represent fundamentally different pieces of data.

For example, a 3-tuple of Year, Month, Day (which we call a `LocalDate`) is different from a specific moment in time (which we call `Instant`), but they are built from some of the same underlying pieces.

### Building Blocks

Eon provides the following primitives for constructing different kinds of dates:

| Module | Purpose & Usage |
|--------|------------------------|
| Year | An integer representing a year. Currently there's no validation (other than being an `int`). |
| Month | A variant type that is one of the 12 named months (where each constructor is the first 3 letters of the month name in English, e.g. `Oct`). |
| DayOfMonth | A 1-based day in a given month. Technically unbounded on its own, but validation is enforced in the context of a Month (see `LocalDate`, `Instant`, etc). |
| Hour | An `int` bound to the range 0...23 (inclusive). |
| Minute | An `int` bound to the range 0...59 (inclusive). |
| Second | An `int` bound to the range 0...59 (inclusive). |
| Millisecond | An `int` bound to the range 0...999 (inclusive). |
| OffsetMinute | An `int` representing the offset from UTC, in minutes. `-480` is `-08:00` in ISO-8601, which is used by US Pacific Time (standard, not daylight savings), along with several other timezones. |

### Useful Types

The building blocks are fine, but they're a lot more useful when you start combining them. You're certainly free to make your own types, but here are some common ones we provide:

| Module | Purpose & Usage |
| ------ | --------------- |
| LocalDate | A 3-tuple of (year, month, day), where `day` is always validated against the combination of year and month. Feb 29 can exist in the year 2020, but not in 2019. |
| LocalTime | A 4-tuple of (hour, minute, second, millisecond). The lower bound is midnight (0, 0, 0, 0), and the upper bound is the millisecond before midnight (23, 59, 59, 999) |
| LocalDateTime | Combines a `LocalDate` with a `LocalTime`, effectively year, month, day, hour, minute, second, millisecond. Note that this does not assume any particular timezone/offset. |
| Instant | A `LocalDate` paired with a UTC offset in minutes. _This_ is the type you want if you're looking to represent an exact moment in time, as JS dates do. Indeed, this type can be converted to or from JavaScript dates (though the original offset will be lost when converting to JS). |
| InstantUTC | Exactly like `Instant`, except the UTC offset is assumed to be `0`. This is slightly less powerful than a normal `Instant`, but it can be converted 1:1 with a JS date, and it can be ordered or checked for equality more easily because there aren't multiple ways to represent the same value. |

### Differences from JS Date

Cinco de Mayo happens every year on May 5. This year, it was on May 5, 2019. The Cinco de Mayo parade began at exactly 2pm Mountain Time (-360 minutes from UTC) on May 5, 2019.

These statements represent different types of data, which may seem obvious, but if you've used JavaScript dates in the browser, you've probably run into calendar widgets that return a `Date` object, which suggests that the user has selected a precise `Instant`.

In reality, choosing a date from a calendar should only imply Year, Month, Day. Worse, you can't even safely convert that `Date` object into a Year, Month, Day, without more ontext, because the `Date.getDate` function (which returns the day-of-month) could give different answers depending on the client's timezone offset.

Eon solves all this by treating those pieces of data as different types, while providing functions to easily, _but explicitly_, convert between those types.

## Examples

Note that these examples may be accurate, but they may also be aspirational. For now, [the tests](https://github.com/reazen/relude-eon/tree/master/test) are the best place to look for correct information about usage.

### Schedule Birthday Email

Imagine we're writing a function that collects a user's birthdate (which they selected from a calendar widget that returned a sad Js.Date.t). We want to use this information, along with the user's timezone offset (an `int`) and the current timestamp as a ReludeEon.Instant.t, to schedule a "happy birthday" email to be sent at 10am on the user's next birthday.

```reason
open ReludeEon;

// Note: this function does everything from reading raw dates from JS to sending
// or scheduling fake emails. This is a poorly-designed function. It does way
// too much for the purpose of demonstrating ReludeEon features.
let scheduleBdayEmail =
  (bday: Js.Date.t, offsetMinute: int, now: InstantUTC.t) => {
  // First of all, having a date object (i.e. an exact moment in UTC time) that
  // represents the user's birthday doesn't make much sense, so we convert it
  // to a ReludeEon LocalDate value. We assume that the `Date` represents
  // midnight on the chosen day _in the user's timezone_, but this is where the
  // ambiguity of JS Dates can cause problems.
  let birthday =
    // turn the Js.Date into an Instant.t in the user's timezone, then throw
    // away hour/minute/second/milli and offset
    Interop.JsDate.toInstant(~offsetMinute, bday) |> Instant.getDate;

  // break down the "now" timestamp to the bits we care about
  let today = InstantUTC.getDate(now);
  let currentYear = LocalDate.getYear(today);

  // here we alias some comparison helpers. Note that these are not the usual
  // polymorphic (==) and (>) functions. These are type-safe, efficient
  // functions that only work with LocalDate values.
  let ((==) , (>)) = LocalDate.(eq, greaterThan);

  // next, set the year to this year, then determine if the birthday has already
  // happened this year (in which case we should schedule for next year)
  let birthdayThisYear = LocalDate.setYear(currentYear, birthday);

  if (birthdayThisYear == today) {
    sendTheEmailRightNow(); // it's not too late!
  } else {
    // if the birthday already happened this year, schedule for next year
    let targetDay = birthdayThisYear > today
      ? birthdayThisYear : LocalDate.nextYear(birthdayThisYear);

    // make it a specific time (10am given the user's offset), adjusted to UTC
    // and written as an ISO-8601 string for compatibility with some imaginary
    // external service
    let targetInstant =
      Instant.fromDateClamped(~hour=10, ~offsetMinute, targetDay)
      |> Instant.adjustToUTC
      |> Instant.formatISO;

    // let's assume we're integrating with an external scheduling system that
    // wants UTC times provided as ISO-8601 strings
    scheduleForLater(targetInstant);
  };
};
```

### Filter Login Times

Eon provides utilities that are meant to be composed with other functions from the Relude ecosystem. For example, instead of providing you with a function to sort a list of dates, we provide you with a `compare` function (and an implementation of the `Ord` module type) that allow you to use existing functions from `Relude.List`.

In this example, we work with a list of login timestamps for a user (e.g. from some audit logs) and determine whether the user logged in between two specific dates.

```reason
open ReludeEon;

// imagine our system was known to be in a bad state from Mar 17, 2019 at
// 04:00:00UTC until Mar 26, 2019 at 17:30:00UTC. We want to look at a list of
// user login timestamps and determine if they logged in during that period.
let loggedInAtBadTime = (loginTimes: list(InstantUTC.t)) => {
  let badStart = InstantUTC.makeClamped(
    ~year=2019,
    ~month=Mar,
    ~dayOfMonth=17,
    ~hour=4,
    ()
  );

  let badEnd = InstantUTC.makeClamped(
    ~year=2019,
    ~month=Mar,
    ~dayOfMonth=26,
    ~hour=17,
    ~minute=30,
    ()
  );

  // do any of the user's login times fall between this start and end?
  List.any(InstantUTC.between(~min=badStart, ~max=badEnd), loginTimes);

  // or maybe we want to find (optionally) the first time they logged in after
  // the issue was over
  let (>) = InstantUTC.greaterThan;

  loginTimes
  |> List.filter(login => login > badEnd)
  |> List.minBy(InstantUTC.compare); // or List.min((module InstantUTC.Ord))
};
```

### Date Math: Build a Range

Most of the provided types (particularly the useful combination types) provide math helpers to add and subtract months, days, hours, etc. Here we use these features to build a list of the next 5 Fridays after a given date (e.g., to show options to the user in a dropdown).

```reason
// TODO
```

## Contributing

If you want to contribute code, that'd be awesome, but just _using_ Eon and providing feedback about any inconsistencies in the API or anything else that isn't quite clear is also incredibly valuable! For more details about how you can help, ([see CONTRIBUTING](https://github.com/reazen/relude-eon/blob/master/CONTRIBUTING.md)).

## License

Released under the [MIT license](https://github.com/reazen/relude-eon/blob/master/LICENSE).
