open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("InstantUTC", () => {
  test("eq (true)", () =>
    expect(
      InstantUTC.eq(
        Instant.toInstantUTC(inst2019EST),
        Instant.toInstantUTC(inst2hrBefore2019MST),
      ),
    )
    |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(
      InstantUTC.eq(
        Instant.toInstantUTC(inst2019EST),
        Instant.toInstantUTC(inst2019MST),
      ),
    )
    |> toEqual(false)
  );

  // midnight EST is before (less than) midnight MST
  test("compare", () =>
    expect(
      InstantUTC.compare(
        Instant.toInstantUTC(inst2019EST),
        Instant.toInstantUTC(inst2019MST),
      ),
    )
    |> toEqual(`less_than)
  );
});
