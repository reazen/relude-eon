open Jest;
open Expect;
open ReludeEon;

describe("Second", () => {
  test("makeClamped (in range)", () =>
    expect(Second.(makeClamped(12) |> getSecond)) |> toEqual(12)
  );

  test("makeClamped (too low)", () =>
    expect(Second.(makeClamped(-20) |> getSecond)) |> toEqual(0)
  );

  test("makeClamped (too high)", () =>
    expect(Second.(makeClamped(120) |> getSecond)) |> toEqual(59)
  );

  test("makeWrapped (in range)", () =>
    expect(Second.(makeWrapped(45) |> getSecond)) |> toEqual(45)
  );

  test("makeWrapped (too low)", () =>
    expect(Second.(makeWrapped(-1) |> getSecond)) |> toEqual(59)
  );

  test("makeWrapped (too high)", () =>
    expect(Second.(makeWrapped(60) |> getSecond)) |> toEqual(0)
  );

  test("make (ok)", () =>
    expect(Second.make(31)) |> toEqual(Some(Second.makeClamped(31)))
  );

  test("make (invalid)", () =>
    expect(Second.make(80)) |> toEqual(None)
  );
});
