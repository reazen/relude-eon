open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("LocalTime", () => {
  test("fromMillisecondsClamped (zero)", () =>
    expect(LocalTime.toTuple(timeMin)) |> toEqual((0, 0, 0, 0))
  );

  test("makeWrappedLabels (zero)", () =>
    expect(LocalTime.makeWrappedLabels()) |> toEqual(timeMin)
  );

  // TODO: test that wrapping constructor wraps out-of-range hours
  // TODO: test that wrapping constructor wraps out-of-range milliseconds
  // TODO: test that clamping constructor clamps etc etc

  test("addMilliseconds (wraps)", () =>
    expect(LocalTime.addMilliseconds(1, timeMax)) |> toEqual(timeMin)
  );
});
