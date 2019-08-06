open Jest;
open Expect;
open ReludeEon;

describe("Year", () => {
  test("isLeapYear (2019)", () =>
    expect(Year.isLeapYear(Year(2019))) |> toEqual(false)
  );

  test("isLeapYear (2016)", () =>
    expect(Year.isLeapYear(Year(2016))) |> toEqual(true)
  );

  test("isLeapYear (2000)", () =>
    expect(Year.isLeapYear(Year(2000))) |> toEqual(true)
  );

  test("isLeapYear (1900)", () =>
    expect(Year.isLeapYear(Year(1900))) |> toEqual(false)
  );

  test("next", () =>
    expect(Year.next(Year(1986))) |> toEqual(Year.Year(1987))
  );

  test("prev", () =>
    expect(Year.prev(Year(1986))) |> toEqual(Year.Year(1985))
  );

  test("eq", () =>
    expect(Year.eq(Year(2001), Year(2001))) |> toEqual(true)
  );

  test("eq", () =>
    expect(Year.eq(Year(2001), Year(2014))) |> toEqual(false)
  );

  test("compare", () => {
    let (<=) = Year.lte;
    expect(Year(1999) <= Year(2019)) |> toEqual(true);
  });
});
