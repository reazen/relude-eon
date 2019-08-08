open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("YMD", () => {
  test("daysInMonth (jan)", () =>
    expect(YMD.daysInMonth(ymd20190101)) |> toEqual(31)
  );

  test("daysInMonth (feb 2020)", () =>
    expect(YMD.daysInMonth(ymd20200229)) |> toEqual(29)
  );

  test("makeWrapped (no wrapping)", () =>
    expect(YMD.makeWrapped(2019, Feb, 28)) |> toEqual(ymd20190228)
  );

  test("makeWrapped (wrap forward)", () =>
    expect(YMD.makeWrapped(2019, Feb, 29)) |> toEqual(ymd20190301)
  );

  test("makeWrapped (wrap backward)", () =>
    expect(YMD.makeWrapped(2020, Mar, 0)) |> toEqual(ymd20200229)
  );

  test("make (valid)", () =>
    expect(YMD.make(2020, Feb, 29)) |> toEqual(Some(ymd20200229))
  );

  test("make (invalid, too high)", () =>
    expect(YMD.make(2019, Feb, 29)) |> toEqual(None)
  );

  test("make(invalid, too low)", () =>
    expect(YMD.make(2018, Jul, 0)) |> toEqual(None)
  );

  test("prevMonth (feb -> jan)", () =>
    expect(YMD.prevMonth(ymd20190228))
    |> toEqual(YMD.makeClamped(2019, Jan, 28))
  );

  test("prevMonth (jan -> dec)", () =>
    expect(YMD.prevMonth(ymd20190101)) |> toEqual(ymd20181201)
  );

  test("nextMonth (jan -> feb)", () =>
    expect(YMD.nextMonth(ymd20190131)) |> toEqual(ymd20190228)
  );

  test("nextMonth (dec -> jan)", () =>
    expect(YMD.nextMonth(ymd20181201)) |> toEqual(ymd20190101)
  );

  test("addDays", () =>
    expect(YMD.addDays(7, ymd20190221)) |> toEqual(ymd20190228)
  );

  test("addDays (more than one month)", () =>
    expect(YMD.addDays(57, ymd20180808)) |> toEqual(ymd20181004)
  );

  test("addDays (negative)", () =>
    expect(YMD.addDays(-30, ymd20190131)) |> toEqual(ymd20190101)
  );

  test("nextDay (year rollover)", () =>
    expect(YMD.nextDay(ymd20181231)) |> toEqual(ymd20190101)
  );

  test("prevDay (Mar 1, non-leap-year)", () =>
    expect(YMD.prevDay(ymd20190301)) |> toEqual(ymd20190228)
  );

  test("prevDay (Mar 1, leap-year)", () =>
    expect(YMD.prevDay(ymd20200301)) |> toEqual(ymd20200229)
  );

  test("isLeapYear (2019)", () =>
    expect(YMD.isLeapYear(ymd20190131)) |> toEqual(false)
  );

  test("isLeapYear (2020)", () =>
    expect(YMD.isLeapYear(ymd20200101)) |> toEqual(true)
  );

  test("daysInYear (2019)", () =>
    expect(YMD.daysInYear(ymd20190301)) |> toEqual(365)
  );

  test("daysInYear (2020)", () =>
    expect(YMD.daysInYear(ymd20200101)) |> toEqual(366)
  );

  test("eq (true)", () =>
    expect(YMD.eq(ymd20200301, ymd20200301)) |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(YMD.eq(ymd20190301, ymd20200301)) |> toEqual(false)
  );

  test("compare (eq)", () =>
    expect(YMD.compare(ymd20190301, ymd20190301)) |> toEqual(`equal_to)
  );

  test("compare (day is less-than)", () =>
    expect(YMD.compare(ymd20190221, ymd20190228)) |> toEqual(`less_than)
  );

  test("compare (month is less but year is greater", () =>
    expect(YMD.compare(ymd20200101, ymd20190301)) |> toEqual(`greater_than)
  );

  test("compare (year is the same, month is less-than", () =>
    expect(YMD.compare(ymd20190101, ymd20190228)) |> toEqual(`less_than)
  );
});
