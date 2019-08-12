open Jest;
open Expect;
open ReludeEon;

describe("Minute", () => {
  test("makeClamped (in range)", () =>
    expect(Minute.(makeClamped(12) |> getMinute)) |> toEqual(12)
  );

  test("makeClamped (too low)", () =>
    expect(Minute.(makeClamped(-20) |> getMinute)) |> toEqual(0)
  );

  test("makeClamped (too high)", () =>
    expect(Minute.(makeClamped(120) |> getMinute)) |> toEqual(59)
  );

  test("makeWrapped (in range)", () =>
    expect(Minute.(makeWrapped(45) |> getMinute)) |> toEqual(45)
  );

  test("makeWrapped (too low)", () =>
    expect(Minute.(makeWrapped(-1) |> getMinute)) |> toEqual(59)
  );

  test("makeWrapped (too high)", () =>
    expect(Minute.(makeWrapped(60) |> getMinute)) |> toEqual(0)
  );

  test("make (ok)", () =>
    expect(Minute.make(31)) |> toEqual(Some(Minute.makeClamped(31)))
  );

  test("make (invalid)", () =>
    expect(Minute.make(80)) |> toEqual(None)
  );
});
