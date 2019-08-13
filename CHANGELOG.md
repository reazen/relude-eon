## 0.1.0 (Aug 13, 2019)

Initial release!

- Includes all of the core date building blocks, plus types like `LocalTime, `LocalDate`, `LocalDateTime`, and `Instant`, which represent different pieces of time using those building blocks.
- Most types have function like `addYears`, `addDays`, `addHours`, etc
- ReludeEon.Interop.JsDate has functions for converting to/from `Js.Date.t`, as well as retrieving the client's current time and timezone offset, wrapped in IO.
