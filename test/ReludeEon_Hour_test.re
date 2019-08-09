open Jest;
open Expect;
open Relude.Globals;
open ReludeEon;

describe("Hour", () => {
  test("makeClamped (in range)", () =>
    expect(Hour.makeClamped(14) |> Hour.getHours) |> toEqual(14)
  );

  test("makeClamped (bottom bound)", () =>
    expect(Hour.makeClamped(0) |> Hour.getHours) |> toEqual(0)
  );

  test("makeClamped (top bound)", () =>
    expect(Hour.makeClamped(23) |> Hour.getHours) |> toEqual(23)
  );

  test("makeClamped (below bound)", () =>
    expect(Hour.makeClamped(-1) |> Hour.getHours) |> toEqual(0)
  );

  test("makeClamped (above bound)", () =>
    expect(Hour.makeClamped(24) |> Hour.getHours) |> toEqual(23)
  );

  test("makeWrapped (in range)", () =>
    expect(Hour.makeWrapped(10) |> Hour.getHours) |> toEqual(10)
  );

  test("makeWrapped (below range)", () =>
    expect(Hour.makeWrapped(-1) |> Hour.getHours) |> toEqual(23)
  );

  test("makeWrapped (above range)", () =>
    expect(Hour.makeWrapped(49) |> Hour.getHours) |> toEqual(1)
  );

  test("make (in range)", () =>
    expect(Hour.make(17) |> Option.map(Hour.getHours))
    |> toEqual(Some(17))
  );

  test("make (below range)", () =>
    expect(Hour.make(-25)) |> toEqual(None)
  );

  test("make (below range)", () =>
    expect(Hour.make(25)) |> toEqual(None)
  );

  test("addHours", () =>
    expect(Hour.(makeClamped(23) |> addHours(1) |> getHours)) |> toEqual(0)
  );

  test("addHours (negative)", () =>
    expect(Hour.(makeClamped(0) |> addHours(-1) |> getHours))
    |> toEqual(23)
  );

  test("addHours (forward 2 full days)", () =>
    expect(Hour.(makeClamped(7) |> addHours(48) |> getHours)) |> toEqual(7)
  );

  test("addHours (backward 2 full days)", () =>
    expect(Hour.(makeClamped(7) |> addHours(-48) |> getHours))
    |> toEqual(7)
  );

  test("eq (true)", () =>
    expect(Hour.(eq(makeClamped(13), makeWrapped(13)))) |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(Hour.(eq(makeClamped(0), makeWrapped(23)))) |> toEqual(false)
  );
});
