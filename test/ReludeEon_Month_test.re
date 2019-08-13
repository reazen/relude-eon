open Jest;
open Expect;
open ReludeEon;

describe("Month", () => {
  test("fromInt1BasedWrapped (in range)", () =>
    expect(Month.fromInt1BasedWrapped(4)) |> toEqual(Month.Apr)
  );

  test("fromInt1BasedWrapped (below range)", () =>
    expect(Month.fromInt1BasedWrapped(-1)) |> toEqual(Month.Nov)
  );

  test("fromInt1BasedWrapped (way below range)", () =>
    expect(Month.fromInt1BasedWrapped(-26)) |> toEqual(Month.Oct)
  );

  test("fromInt1BasedWrapped (above range)", () =>
    expect(Month.fromInt1BasedWrapped(15)) |> toEqual(Month.Mar)
  );

  test("fromInt1BasedWrapped (way above range)", () =>
    expect(Month.fromInt1BasedWrapped(38)) |> toEqual(Month.Feb)
  );

  test("fromInt1BasedClamped (in range)", () =>
    expect(Month.fromInt1BasedClamped(4)) |> toEqual(Month.Apr)
  );

  test("fromInt1BasedClamped (below range)", () =>
    expect(Month.fromInt1BasedClamped(-1)) |> toEqual(Month.Jan)
  );

  test("fromInt1BasedClamped (above range)", () =>
    expect(Month.fromInt1BasedClamped(13)) |> toEqual(Month.Dec)
  );

  test("fromInt1Based (lower bound)", () =>
    expect(Month.fromInt1Based(1)) |> toEqual(Some(Month.Jan))
  );

  test("fromInt1Based (upper bound)", () =>
    expect(Month.fromInt1Based(12)) |> toEqual(Some(Month.Dec))
  );

  test("fromInt1Based (above range)", () =>
    expect(Month.fromInt1Based(13)) |> toEqual(None)
  );

  test("fromInt1Based (below range)", () =>
    expect(Month.fromInt1Based(0)) |> toEqual(None)
  );

  test("fromInt0BasedWrapped (above range)", () =>
    expect(Month.fromInt0BasedWrapped(12)) |> toEqual(Month.Jan)
  );

  test("fromInt0BasedWrapped (below range)", () =>
    expect(Month.fromInt0BasedWrapped(-4)) |> toEqual(Month.Sep)
  );

  test("fromInt0BasedClamped (in range)", () =>
    expect(Month.fromInt0BasedClamped(11)) |> toEqual(Month.Dec)
  );

  test("fromInt0BasedClamped (below range)", () =>
    expect(Month.fromInt0BasedClamped(-11)) |> toEqual(Month.Jan)
  );

  test("fromInt0BasedClamped (above range)", () =>
    expect(Month.fromInt0BasedClamped(111)) |> toEqual(Month.Dec)
  );

  test("fromInt0Based", () =>
    expect(Month.fromInt0Based(4)) |> toEqual(Some(Month.May))
  );

  test("toInt1Based", () =>
    expect(Month.toInt1Based(Jul)) |> toEqual(7)
  );

  test("toInt1Based", () =>
    expect(Month.toInt1Based(Aug)) |> toEqual(8)
  );

  test("toInt1Based", () =>
    expect(Month.toInt1Based(Dec)) |> toEqual(12)
  );

  test("toInt0Based", () =>
    expect(Month.toInt0Based(Jan)) |> toEqual(0)
  );

  test("toInt0Based", () =>
    expect(Month.toInt0Based(Feb)) |> toEqual(1)
  );

  test("addMonths", () =>
    expect(Month.addMonths(5, Feb)) |> toEqual(Month.Jul)
  );

  test("addMonths (negative)", () =>
    expect(Month.addMonths(-4, Jan)) |> toEqual(Month.Sep)
  );

  test("addMonths (zero)", () =>
    expect(Month.addMonths(0, Aug)) |> toEqual(Month.Aug)
  );

  test("addMonths (more than 12)", () =>
    expect(Month.addMonths(13, Oct)) |> toEqual(Month.Nov)
  );

  test("next", () =>
    expect(Month.next(Apr)) |> toEqual(Month.May)
  );

  test("next (wraps)", () =>
    expect(Month.next(Dec)) |> toEqual(Month.Jan)
  );

  test("prev", () =>
    expect(Month.prev(Dec)) |> toEqual(Month.Nov)
  );

  test("prev (wraps)", () =>
    expect(Month.prev(Jan)) |> toEqual(Month.Dec)
  );

  test("daysInMonth (Jan)", () =>
    expect(Month.totalDays(false, Jan)) |> toEqual(31)
  );

  test("daysInMonth (Feb, non-leap-year)", () =>
    expect(Month.totalDays(false, Feb)) |> toEqual(28)
  );

  test("daysInMonth (Feb, leap-year)", () =>
    expect(Month.totalDays(true, Feb)) |> toEqual(29)
  );

  test("daysInMonth (Apr)", () =>
    expect(Month.totalDays(false, Apr)) |> toEqual(30)
  );

  test("compare (Jan, Sep is LT)", () =>
    expect(Month.compare(Jan, Sep)) |> toEqual(`less_than)
  );

  test("compare (Jul, Jul is EQ)", () =>
    expect(Month.compare(Jul, Jul)) |> toEqual(`equal_to)
  );

  test("compare (Feb, Jan is GT)", () =>
    expect(Month.compare(Feb, Jan)) |> toEqual(`greater_than)
  );

  test("eq (true)", () =>
    expect(Month.eq(Sep, Sep)) |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(Month.eq(Jun, Sep)) |> toEqual(false)
  );
});
