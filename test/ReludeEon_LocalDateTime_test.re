open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("LocalDateTime", () => {
  test("makeWrapped", () =>
    expect(
      LocalDateTime.(makeWrapped(2019, Dec, 31, 23, 59, 59, 1000) |> toTuple),
    )
    |> toEqual((2020, Month.Jan, 1, 0, 0, 0, 0))
  );

  test("makeWrappedLabels", () =>
    expect(
      LocalDateTime.(
        makeWrappedLabels(~year=2020, ~month=Jan, ~day=1, ()) |> toTuple
      ),
    )
    |> toEqual((2020, Month.Jan, 1, 0, 0, 0, 0))
  );

  test("makeClamped", () =>
    expect(
      LocalDateTime.(makeClamped(2019, Dec, 31, 23, 59, 59, 1000) |> toTuple),
    )
    |> toEqual((2019, Month.Dec, 31, 23, 59, 59, 999))
  );

  test("makeClampedLabels", () =>
    expect(
      LocalDateTime.(
        makeClampedLabels(
          ~year=2000,
          ~month=Feb,
          ~day=29,
          ~hour=23,
          ~minute=59,
          ~second=60,
          ~millisecond=123,
          (),
        )
        |> toTuple
      ),
    )
    |> toEqual((2000, Month.Feb, 29, 23, 59, 59, 123))
  );

  test("getYear", () =>
    expect(LocalDateTime.getYear(dtMilliBefore2019)) |> toEqual(2018)
  );

  test("getMonth", () =>
    expect(LocalDateTime.getMonth(dtMilliBefore2019)) |> toEqual(Month.Dec)
  );

  test("getDay", () =>
    expect(LocalDateTime.getDayOfMonth(dtMilliBefore2019)) |> toEqual(31)
  );

  test("getHour", () =>
    expect(LocalDateTime.getHour(dtMilliBefore2019)) |> toEqual(23)
  );

  test("getMinute", () =>
    expect(LocalDateTime.getMinute(dtMilliBefore2019)) |> toEqual(59)
  );

  test("getSecond", () =>
    expect(LocalDateTime.getSecond(dtMilliBefore2019)) |> toEqual(59)
  );

  test("getMillisecond", () =>
    expect(LocalDateTime.getMillisecond(dtMilliBefore2019)) |> toEqual(999)
  );

  test("addYears", () =>
    expect(LocalDateTime.addYears(2, dt20180101midnight))
    |> toEqual(dt20200101midnight)
  );

  test("prevYear", () =>
    expect(LocalDateTime.prevYear(dt20200101midnight))
    |> toEqual(dt20190101midnight)
  );

  test("nextYear", () =>
    expect(LocalDateTime.nextYear(dt20200101midnight))
    |> toEqual(
         LocalDateTime.makeClampedLabels(~year=2021, ~month=Jan, ~day=1, ()),
       )
  );

  test("addMonths (wraps forward)", () =>
    expect(
      LocalDateTime.(
        addMonths(2, fromDateAndTime(ymd20181231, LocalTime.noon))
      ),
    )
    |> toEqual(LocalDateTime.fromDateAndTime(ymd20190228, LocalTime.noon))
  );

  test("addMonths (more than one year backward)", () =>
    expect(
      LocalDateTime.(
        addMonths(-15, makeClampedLabels(~year=2018, ~month=Jan, ~day=4, ()))
      ),
    )
    |> toEqual(
         LocalDateTime.makeClampedLabels(~year=2016, ~month=Oct, ~day=4, ()),
       )
  );

  test("prevMonth (wraps backward)", () =>
    expect(
      LocalDateTime.(
        prevMonth(fromDateAndTime(ymd20190101, LocalTime.midnight))
      ),
    )
    |> toEqual(
         LocalDateTime.fromDateAndTime(ymd20181201, LocalTime.midnight),
       )
  );

  test("nextMillisecond (wraps year)", () =>
    expect(LocalDateTime.nextMillisecond(dtMilliBefore2019))
    |> toEqual(dt20190101midnight)
  );

  test("eq (true)", () =>
    expect(LocalDateTime.eq(dtMilliBefore2019, dtMilliBefore2019))
    |> toEqual(true)
  );

  test("eq (false)", () =>
    expect(LocalDateTime.eq(dtMilliBefore2019, dt20190101midnight))
    |> toEqual(false)
  );

  test("compare (eq)", () =>
    expect(LocalDateTime.compare(dt20200101noon, dt20200101noon))
    |> toEqual(`equal_to)
  );

  test("compare (date gt)", () =>
    expect(LocalDateTime.compare(dt20190101midnight, dtMilliBefore2019))
    |> toEqual(`greater_than)
  );

  test("compare (same date, lt time)", () =>
    expect(LocalDateTime.compare(dt20200101midnight, dt20200101noon))
    |> toEqual(`less_than)
  );
});
