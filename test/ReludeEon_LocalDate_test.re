open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("LocalDate", () => {
  test("daysInMonth (jan)", () =>
    expect(LocalDate.daysInMonth(ymd20190101)) |> toEqual(31)
  );

  test("daysInMonth (feb 2020)", () =>
    expect(LocalDate.daysInMonth(ymd20200229)) |> toEqual(29)
  );

  test("makeWrapped (no wrapping)", () =>
    expect(LocalDate.makeWrapped(2019, Feb, 28)) |> toEqual(ymd20190228)
  );

  test("makeWrapped (wrap forward)", () =>
    expect(LocalDate.makeWrapped(2019, Feb, 29)) |> toEqual(ymd20190301)
  );

  test("makeWrapped (wrap backward)", () =>
    expect(LocalDate.makeWrapped(2020, Mar, 0)) |> toEqual(ymd20200229)
  );

  test("make (valid)", () =>
    expect(LocalDate.make(2020, Feb, 29)) |> toEqual(Some(ymd20200229))
  );

  test("make (invalid, too high)", () =>
    expect(LocalDate.make(2019, Feb, 29)) |> toEqual(None)
  );

  test("make(invalid, too low)", () =>
    expect(LocalDate.make(2018, Jul, 0)) |> toEqual(None)
  );

  test("toTuple", () =>
    expect(LocalDate.toTuple(ymd20180808)) |> toEqual((2018, Month.Aug, 8))
  );

  test("getYear", () =>
    expect(LocalDate.getYear(ymd20190101)) |> toEqual(2019)
  );

  test("getMonth", () =>
    expect(LocalDate.getMonth(ymd20190101)) |> toEqual(Month.Jan)
  );

  test("getDayOfMonth", () =>
    expect(LocalDate.getDayOfMonth(ymd20190131)) |> toEqual(31)
  );

  test("prevYear (feb 29 -> feb 28", () =>
    expect(LocalDate.prevYear(ymd20200229)) |> toEqual(ymd20190228)
  );

  test("nextYear (feb 28 -> feb 28", () =>
    expect(LocalDate.nextYear(ymd20190228)) |> toEqual(ymd20200228)
  );

  test("addMonths (2, skips feb)", () =>
    expect(LocalDate.addMonths(2, ymd20200131)) |> toEqual(ymd20200331)
  );

  test("addMonths (24)", () =>
    expect(LocalDate.addMonths(24, ymd20180131)) |> toEqual(ymd20200131)
  );

  test("addMonths (-14)", () =>
    expect(LocalDate.addMonths(-14, ymd20200331)) |> toEqual(ymd20190131)
  );

  test("prevMonth (feb -> jan)", () =>
    expect(LocalDate.prevMonth(ymd20190228))
    |> toEqual(LocalDate.makeClamped(2019, Jan, 28))
  );

  test("prevMonth (jan -> dec)", () =>
    expect(LocalDate.prevMonth(ymd20190101)) |> toEqual(ymd20181201)
  );

  test("nextMonth (jan -> feb)", () =>
    expect(LocalDate.nextMonth(ymd20190131)) |> toEqual(ymd20190228)
  );

  test("nextMonth (dec -> jan)", () =>
    expect(LocalDate.nextMonth(ymd20181201)) |> toEqual(ymd20190101)
  );

  test("addDays", () =>
    expect(LocalDate.addDays(7, ymd20190221)) |> toEqual(ymd20190228)
  );

  test("addDays (more than one month)", () =>
    expect(LocalDate.addDays(57, ymd20180808)) |> toEqual(ymd20181004)
  );

  test("addDays (negative)", () =>
    expect(LocalDate.addDays(-30, ymd20190131)) |> toEqual(ymd20190101)
  );

  test("nextDay (year rollover)", () =>
    expect(LocalDate.nextDay(ymd20181231)) |> toEqual(ymd20190101)
  );

  test("prevDay (Mar 1, non-leap-year)", () =>
    expect(LocalDate.prevDay(ymd20190301)) |> toEqual(ymd20190228)
  );

  test("prevDay (Mar 1, leap-year)", () =>
    expect(LocalDate.prevDay(ymd20200301)) |> toEqual(ymd20200229)
  );

  test("isLeapYear (2019)", () =>
    expect(LocalDate.isLeapYear(ymd20190131)) |> toEqual(false)
  );

  test("isLeapYear (2020)", () =>
    expect(LocalDate.isLeapYear(ymd20200131)) |> toEqual(true)
  );

  test("daysInYear (2019)", () =>
    expect(LocalDate.daysInYear(ymd20190301)) |> toEqual(365)
  );

  test("daysInYear (2020)", () =>
    expect(LocalDate.daysInYear(ymd20200131)) |> toEqual(366)
  );

  test("eq (true)", () =>
    expect(LocalDate.eq(ymd20200301, ymd20200301)) |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(LocalDate.eq(ymd20190301, ymd20200301)) |> toEqual(false)
  );

  test("compare (eq)", () =>
    expect(LocalDate.compare(ymd20190301, ymd20190301))
    |> toEqual(`equal_to)
  );

  test("compare (day is less-than)", () =>
    expect(LocalDate.compare(ymd20190221, ymd20190228))
    |> toEqual(`less_than)
  );

  test("compare (month is less but year is greater", () =>
    expect(LocalDate.compare(ymd20200131, ymd20190301))
    |> toEqual(`greater_than)
  );

  test("compare (year is the same, month is less-than", () =>
    expect(LocalDate.compare(ymd20190101, ymd20190228))
    |> toEqual(`less_than)
  );
});
