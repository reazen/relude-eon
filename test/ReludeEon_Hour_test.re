open Jest;
open Expect;
open Relude.Globals;
open ReludeEon;

describe("Hour", () => {
  test("makeClamped (in range)", () =>
    expect(Hour.makeClamped(14) |> Hour.getHour) |> toEqual(14)
  );

  test("makeClamped (bottom bound)", () =>
    expect(Hour.makeClamped(0) |> Hour.getHour) |> toEqual(0)
  );

  test("makeClamped (top bound)", () =>
    expect(Hour.makeClamped(23) |> Hour.getHour) |> toEqual(23)
  );

  test("makeClamped (below bound)", () =>
    expect(Hour.makeClamped(-1) |> Hour.getHour) |> toEqual(0)
  );

  test("makeClamped (above bound)", () =>
    expect(Hour.makeClamped(24) |> Hour.getHour) |> toEqual(23)
  );

  test("makeWrapped (in range)", () =>
    expect(Hour.makeWrapped(10) |> Hour.getHour) |> toEqual(10)
  );

  test("makeWrapped (below range)", () =>
    expect(Hour.makeWrapped(-1) |> Hour.getHour) |> toEqual(23)
  );

  test("makeWrapped (above range)", () =>
    expect(Hour.makeWrapped(49) |> Hour.getHour) |> toEqual(1)
  );

  test("make (in range)", () =>
    expect(Hour.make(17) |> Option.map(Hour.getHour)) |> toEqual(Some(17))
  );

  test("make (below range)", () =>
    expect(Hour.make(-25)) |> toEqual(None)
  );

  test("make (below range)", () =>
    expect(Hour.make(25)) |> toEqual(None)
  );

  test("addHours", () =>
    expect(Hour.(makeClamped(23) |> addHours(1) |> getHour)) |> toEqual(0)
  );

  test("addHours (negative)", () =>
    expect(Hour.(makeClamped(0) |> addHours(-1) |> getHour)) |> toEqual(23)
  );

  test("addHours (forward 2 full days)", () =>
    expect(Hour.(makeClamped(7) |> addHours(48) |> getHour)) |> toEqual(7)
  );

  test("addHours (backward 2 full days)", () =>
    expect(Hour.(makeClamped(7) |> addHours(-48) |> getHour)) |> toEqual(7)
  );

  test("eq (true)", () =>
    expect(Hour.(eq(makeClamped(13), makeWrapped(13)))) |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(Hour.(eq(makeClamped(0), makeWrapped(23)))) |> toEqual(false)
  );
});
