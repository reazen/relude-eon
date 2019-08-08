# Relude Eon

[![build status](https://img.shields.io/circleci/project/github/reazen/relude-eon/master.svg)](https://circleci.com/gh/reazen/relude-eon)
[![test coverage](https://img.shields.io/coveralls/github/reazen/relude-eon.svg)](https://coveralls.io/github/reazen/relude-eon)
[![npm version](https://img.shields.io/npm/v/relude-eon.svg)](https://www.npmjs.com/package/relude-eon)
[![license](https://img.shields.io/github/license/reazen/relude-eon.svg)](https://github.com/reazen/relude-eon/blob/master/LICENSE)

Relude Eon is a ReasonML library for working with type-safe date and time values in a sane way.

---
**Current Status:** There's a concrete plan to make everything outlined in this README a reality, but some of the docs here are aspirational rather than real. For now. Give it a couple days.
---

## Core Concepts

### Differences from JS Date

Dates in Eon are built from smaller, typed building blocks. We can assmble these pieces into different types, which represent fundamentally different concepts.

For example, if I say that Cinco de Mayo this year is "May 5, 2019", I'm essentially providing you with a 3-tuple of `(Year.t, Month.t, DayOfMonth.t)`. This is not the same thing as telling you that Cinco de Mayo this year started at 00:00:00 UTC (or worse, midnight in the client's local timezone), or that Cinco de Mayo 2019 is some number of second after the Unix epoch.

This may seem obvious, but if you're used to JavaScript dates in the browser, you've probably run into calendar widgets that return a midnight timestamp when the user actually picked a day on a calendar. And when you call `getHours` (or even `getMonth`) on a JS Date, you may get different answers for the exact same date, depending on what timezone the client is in.

### Building Blocks

Eon provides the following primitives for constructing different kinds of dates:

**Year**

An integer representing a year. Currently there's no validation (other than being an `int`).

**Month**

A variant type that is one of the 12 named months (where each constructor is the first 3 letters of the month name in English).

**DayOfMonth**

A 1-based day in a given month. Technically unbounded on its own, but validation is enforced in the context of a Month (see `LocalDate`, `Instant`, etc).

**Hour**

An `int` bound to the range 0...23 (inclusive).

**Minute**

An `int` bound to the range 0...59 (inclusive).

**Second**

An `int` bound to the range 0...59 (inclusive).

**Millisecond**

An `int` bound to the range 0...999 (inclusive).

**OffsetMinute**

An `int` representing the offset from UTC, in minutes. `-480` is `-08:00` in ISO-8601, which represents US Pacific Time (standard, not DST), along with several other timezones.


### Useful Types

The building blocks are fine, but they're a lot more useful when you start combining them together. You're certainly free to make your own types, but here are some common ones we provide:

**LocalDate**

A 3-tuple of (year, month, day), where `day` is always validated against the combination of year and month. Feb 29 can exist in the year 2020, but not in 2019.

**LocalTime**

A 4-tuple of (hour, minute, second, millisecond).

**LocalDateTime**

(year, month, day, hour, minute, second, millisecond). Still important to note that this is not assumed to be in any particular timezone.

**Instant**

All of the above, combined with a UTC offset. _This_ is the type you want if you're looking to represent an exact moment in time, as JS dates do. Indeed, this type can be converted to or from JavaScript dates (though the original offset will be lost when converting to JS).

**InstantUTC**

Exactly like `Instant`, except the UTC offset is assumed to be `0`. This is slightly less powerful than a normal `Instant`, but it can be converted 1:1 with a JS date, and it can be compared more easily because there aren't multiple ways to represent the same moment in time.

## Examples

### Schedule Birthday Email

Imagine we're writing a function that collects a user's birthdate (which they selected from a calendar widget that returned a sad Js.Date.t). We want to use this information, along with the user's timezone offset (an `int`) and the current timestamp as a ReludeEon.Instant.t, to schedule a "happy birthday" email to be sent at 10am on the user's next birthday.

```reason
open ReludeEon;

// Note: this function does everything from reading raw dates from JS to sending
// or scheduling fake emails. This is a poorly-designed function. It does way
// too much for the purpose of demonstrating ReludeEon features.
let scheduleBdayEmail = (bday: Js.Date.t, offset: int, now: Instant.t) => {
  // first of all, having a date object (i.e. an exact moment in UTC time) that
  // represents the user's birthday doesn't make much sense, so we convert it
  // to a ReludeEon YMD value:
  let birthday =
    Interop.fromRaw(bday) // turn the Js.Date into an Instant.t (as UTC)
    |> Instant.withOffset(offset) // adjust for user's offset
    |> Instant.toYMD; // throw away hour/minute/second/milli and offset

  // next, set the year to this year, then determine if the birthday has already
  // happened this year (in which case we should schedule for next year)
  let birthdayThisYear = YMD.withYear(Instant.getYear(now), birthday);
  let today = Instant.toYMD(now);

  // here we alias some comparison helpers. Note that these are not the usual
  // polymorphic (==) and (>) functions. These are type-safe, efficient
  // functions that only work with YMD values.
  let ((==) , (>)) = YMD.(eq, greaterThan);

  if (birthdayThisYear == today) {
    sendTheEmailRightNow(); // it's not too late!
  } else {
    // if the birthday already happened this year, schedule for next year
    let targetDay = birthdayThisYear > today
      ? birthdayThisYear : YMD.nextYear(birthdayThisYear);

    // make it a specific time (10am given the user's offset)
    let targetTime = Instant.fromYMD(~hour=10, ~offset, targetDay);

    // let's assume we're integrating with an external scheduling system that
    // wants UTC times provided as ISO-8601 strings
    scheduleForLater(Instant.(asUTC(targetTime) |> formatAsIso8601));
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
let loggedInAtBadTime = (loginTimes: InstantUTC.t) => {
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
