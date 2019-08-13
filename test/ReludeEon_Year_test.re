open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("Year", () => {
  test("isLeapYear (2019)", () =>
    expect(Year.isLeapYear(y2019)) |> toEqual(false)
  );

  test("isLeapYear (2016)", () =>
    expect(Year.isLeapYear(y2016)) |> toEqual(true)
  );

  test("isLeapYear (2000)", () =>
    expect(Year.isLeapYear(y2000)) |> toEqual(true)
  );

  test("isLeapYear (1900)", () =>
    expect(Year.isLeapYear(y1900)) |> toEqual(false)
  );

  test("next", () =>
    expect(Year.next(y1986)) |> toEqual(y1987)
  );

  test("prev", () =>
    expect(Year.prev(y1986)) |> toEqual(y1985)
  );

  test("eq", () =>
    expect(Year.eq(y2001, y2001)) |> toEqual(true)
  );

  test("eq", () =>
    expect(Year.eq(y2001, y2016)) |> toEqual(false)
  );

  test("compare", () => {
    let (<=) = Year.lte;
    expect(y1999 <= y2019) |> toEqual(true);
  });
});
