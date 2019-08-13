open Jest;
open Expect;
open ReludeEon;

open SampleData;

describe("Interop.JsDate", () => {
  let utc20200229 =
    InstantUTC.fromLocalDateTime(LocalDateTime.fromDateClamped(ymd20200229));

  let d20200229 =
    Js.Date.(
      fromFloat(utcWithYMD(~year=2020.0, ~month=1.0, ~date=29.0, ()))
    );

  test("fromInstantUTC", () =>
    expect(Interop.JsDate.fromInstantUTC(utc20200229)) |> toEqual(d20200229)
  );

  test("toInstantUTC", () =>
    expect(Interop.JsDate.toInstantUTC(d20200229)) |> toEqual(utc20200229)
  );
});
