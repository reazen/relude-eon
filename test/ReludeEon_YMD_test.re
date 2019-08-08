open Jest;
open Expect;
open ReludeEon;

describe("YMD", () => {
  let ymd20181201 = YMD.makeClamped(2018, Dec, 1);
  let ymd20190101 = YMD.makeClamped(2019, Jan, 1);
  let ymd20190131 = YMD.makeClamped(2019, Jan, 31);
  let ymd20190228 = YMD.makeClamped(2019, Feb, 28);
  let ymd20190301 = YMD.makeClamped(2019, Mar, 1);
  let ymd20200101 = YMD.makeClamped(2020, Jan, 31);
  let ymd20200229 = YMD.makeClamped(2020, Feb, 29);
  // let ymd20200301 = YMD.makeClamped(2020, Mar, 1);

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

  test("isLeapYear (2019)", () =>
    expect(YMD.isLeapYear(ymd20190131)) |> toEqual(false)
  );

  test("isLeapYear (2020)", () =>
    expect(YMD.isLeapYear(ymd20200101)) |> toEqual(true)
  );

});
