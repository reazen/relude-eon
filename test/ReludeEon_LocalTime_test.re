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

  test("makeWrappedLabels (ms too high)", () =>
    expect(
      LocalTime.makeWrappedLabels(
        ~hour=1,
        ~minute=2,
        ~second=3,
        ~millisecond=1000,
        (),
      )
      |> LocalTime.toTuple,
    )
    |> toEqual((1, 2, 4, 0))
  );

  test("makeWrapped (minute too high)", () =>
    expect(LocalTime.makeWrapped(12, 90, 0, 0)) |> toEqual(time1330)
  );

  test("makeClampedLabels (no values provided)", () =>
    expect(LocalTime.makeClampedLabels()) |> toEqual(LocalTime.midnight)
  );

  test("makeClamped (clamps minute, does not increase hour)", () =>
    expect(LocalTime.(makeClamped(12, 60, 0, 0) |> toTuple))
    |> toEqual((12, 59, 0, 0))
  );

  test("fromMillisecondsClamped (too high)", () =>
    expect(LocalTime.fromMillisecondsClamped(86400000))
    |> toEqual(LocalTime.Bounded.top)
  );

  test("fromMillisecondsClamped (too low)", () =>
    expect(LocalTime.fromMillisecondsClamped(-1))
    |> toEqual(LocalTime.Bounded.bottom)
  );

  test("fromMillisecondsWrapped (too high)", () =>
    expect(LocalTime.fromMillisecondsWrapped(86400000))
    |> toEqual(LocalTime.Bounded.bottom)
  );

  test("addHours", () =>
    expect(LocalTime.addHours(12, timeMin)) |> toEqual(LocalTime.noon)
  );

  test("addHours (wraps)", () =>
    expect(LocalTime.addHours(12, LocalTime.noon)) |> toEqual(timeMin)
  );

  test("addHours (24 is same time)", () =>
    expect(LocalTime.addHours(24, time1330)) |> toEqual(time1330)
  );

  test("addHours (large number does not overflow)", () =>
    expect(LocalTime.addHours(961, timeMin))
    |> toEqual(LocalTime.addHours(1, timeMin))
  );

  test("prevMinute", () =>
    expect(LocalTime.(prevMinute(midnight) |> toTuple))
    |> toEqual((23, 59, 0, 0))
  );

  test("negative zero?", () =>
    expect((-60) mod 60) |> toEqual(0)
  );

  test("addSecond (-60 == -1 minute)", () =>
    expect(LocalTime.(addSeconds(-60, noon)))
    |> toEqual(LocalTime.(addMinutes(-1, noon)))
  );

  test("nextSecond", () =>
    expect(LocalTime.(makeClamped(13, 59, 59, 0) |> nextSecond))
    |> toEqual(LocalTime.makeClamped(14, 0, 0, 0))
  );

  test("addMilliseconds (wraps)", () =>
    expect(LocalTime.addMilliseconds(1, timeMax)) |> toEqual(timeMin)
  );
});
