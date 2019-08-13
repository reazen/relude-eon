open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("Instant", () => {
  test("makeWrapped", () =>
    expect(Instant.makeWrapped(2019, Jan, 1, 0, 0, 0, 0, -300))
    |> toEqual(inst2019EST)
  );

  test("overwriteOffset (changes offset minute)", () =>
    expect(
      Instant.(overwriteOffset(offsetMST, inst2019EST) |> getOffsetMinute),
    )
    |> toEqual(-420)
  );

  test("overwriteOffset (doesn't change datetime)", () => {
    let overwritten = Instant.overwriteOffset(offsetMST, inst2019EST);
    let date = Instant.getDate(overwritten);
    let time = Instant.getTime(overwritten);
    expect((date, time)) |> toEqual((ymd20190101, timeMin));
  });

  test("addYears", () =>
    expect(Instant.(addYears(2, fromDateTime(dt20180101midnight))))
    |> toEqual(Instant.fromDateTime(dt20200101midnight))
  );

  test("addMonths (wraps forward)", () =>
    expect(
      Instant.(addMonths(2, fromDateAndTime(ymd20181231, LocalTime.noon))),
    )
    |> toEqual(Instant.fromDateAndTime(ymd20190228, LocalTime.noon))
  );

  test("addMonths (more than one year backward)", () =>
    expect(
      Instant.(
        addMonths(-15, makeClampedLabels(~year=2018, ~month=Jan, ~day=4, ()))
      ),
    )
    |> toEqual(Instant.makeClampedLabels(~year=2016, ~month=Oct, ~day=4, ()))
  );

  test("addMonths (-12 == -1 year)", () =>
    expect(Instant.addMonths(-12, inst2019EST))
    |> toEqual(Instant.prevYear(inst2019EST))
  );

  test("nextSecond", () =>
    expect(Instant.nextSecond(inst2019EST))
    |> toEqual(
         Instant.fromDateClamped(~second=1, ~offsetMinute=-300, ymd20190101),
       )
  );

  test("nextMillisecond", () =>
    expect(
      Instant.(fromDateAndTime(ymd20181231, timeMax) |> nextMillisecond),
    )
    |> toEqual(
         Instant.(fromDateAndTime(~offsetMinute=0, ymd20190101, timeMin)),
       )
  );

  test("prevMillisecond", () =>
    expect(Instant.(nextMillisecond(inst2019EST) |> prevMillisecond))
    |> toEqual(inst2019EST)
  );

  test("makeWrappedLabels", () =>
    expect(
      Instant.makeWrappedLabels(
        ~year=2020,
        ~month=Feb,
        ~day=29,
        ~hour=23,
        ~minute=59,
        ~second=59,
        ~millisecond=1000,
        ~offset=-300,
        (),
      )
      |> Instant.toTuple,
    )
    |> toEqual((2020, Month.Mar, 1, 0, 0, 0, 0, (-300)))
  );

  test("adjustOffset (MST -> EST)", () =>
    expect(
      Instant.(
        makeClampedLabels(
          ~year=2018,
          ~month=Dec,
          ~day=31,
          ~hour=22,
          ~offsetMinute=-420,
          (),
        )
        |> adjustOffset(offsetEST)
      ),
    )
    |> toEqual(inst2019EST)
  );

  test("adjustOffsetClamped", () =>
    expect(
      Instant.adjustOffsetClamped(-420, inst2019EST) |> Instant.getOffset,
    )
    |> toEqual(offsetMST)
  );

  test("adjustToUTC (correct offset)", () =>
    expect(Instant.adjustToUTC(inst2019EST) |> Instant.getOffset)
    |> toEqual(OffsetMinute.utc)
  );

  test("adjustToUTC (correct datetime)", () =>
    expect(Instant.adjustToUTC(inst2019EST) |> Instant.getDateTime)
    |> toEqual(LocalDateTime.makeClamped(2019, Jan, 1, 5, 0, 0, 0))
  );

  test("toInstantUTC", () =>
    expect(Instant.toInstantUTC(inst2019EST))
    |> toEqual(
         InstantUTC.fromLocalDateTime(
           LocalDateTime.makeClamped(2019, Jan, 1, 5, 0, 0, 0),
         ),
       )
  );

  test("toInstantUTC/fromInstantUTC (round-trip)", () =>
    expect(
      Instant.(
        fromInstantUTC(~offsetMinute=-300, toInstantUTC(inst2019EST))
      ),
    )
    |> toEqual(inst2019EST)
  );

  test("eq (fromLocalDateTime and fromInstantUTC are different)", () =>
    expect(
      Instant.eq(
        Instant.fromDateTime(~offsetMinute=-360, dt20200101noon),
        Instant.fromInstantUTC(
          ~offsetMinute=-360,
          InstantUTC.fromLocalDateTime(dt20200101noon),
        ),
      ),
    )
    |> toEqual(false)
  );

  test("eq (true)", () =>
    expect(Instant.eq(inst2019EST, inst2019EST)) |> toEqual(true)
  );

  test("eq (false, different offset)", () =>
    expect(
      Instant.(
        eq(
          fromDateTime(~offsetMinute=0, dt20200101noon),
          fromDateTime(~offsetMinute=-420, dt20200101noon),
        )
      ),
    )
    |> toEqual(false)
  );

  test("eq (false, different datetime)", () =>
    expect(
      Instant.(
        eq(fromDateTime(dt20200101noon), fromDateTime(dt20200101midnight))
      ),
    )
    |> toEqual(false)
  );
});
