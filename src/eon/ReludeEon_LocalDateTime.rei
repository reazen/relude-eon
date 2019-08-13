type t;

let makeWrapped: (int, ReludeEon_Month.t, int, int, int, int, int) => t;
let makeWrappedLabels:
  (
    ~year: int,
    ~month: ReludeEon_Month.t,
    ~day: int,
    ~hour: int=?,
    ~minute: int=?,
    ~second: int=?,
    ~millisecond: int=?,
    unit
  ) =>
  t;

let makeClamped: (int, ReludeEon_Month.t, int, int, int, int, int) => t;
let makeClampedLabels:
  (
    ~year: int,
    ~month: ReludeEon_Month.t,
    ~day: int,
    ~hour: int=?,
    ~minute: int=?,
    ~second: int=?,
    ~millisecond: int=?,
    unit
  ) =>
  t;

let fromDateAndTime: (ReludeEon_LocalDate.t, ReludeEon_LocalTime.t) => t;
let fromDateClamped:
  (
    ~hour: int=?,
    ~minute: int=?,
    ~second: int=?,
    ~millisecond: int=?,
    ReludeEon_LocalDate.t
  ) =>
  t;

let toTuple: t => (int, ReludeEon_Month.t, int, int, int, int, int);
let getDate: t => ReludeEon_LocalDate.t;
let getYear: t => int;
let getMonth: t => ReludeEon_Month.t;
let getDayOfMonth: t => int;
let getTime: t => ReludeEon_LocalTime.t;
let getHour: t => int;
let getMinute: t => int;
let getSecond: t => int;
let getMillisecond: t => int;

let addYears: (int, t) => t;
let prevYear: t => t;
let nextYear: t => t;

let addMonths: (int, t) => t;
let prevMonth: t => t;
let nextMonth: t => t;

let addDays: (int, t) => t;
let prevDay: t => t;
let nextDay: t => t;

let addHours: (int, t) => t;
let prevHour: t => t;
let nextHour: t => t;

let addMinutes: (int, t) => t;
let prevMinute: t => t;
let nextMinute: t => t;

let addSeconds: (int, t) => t;
let prevSecond: t => t;
let nextSecond: t => t;

let addMilliseconds: (int, t) => t;
let prevMillisecond: t => t;
let nextMillisecond: t => t;

let eq: (t, t) => bool;
let compare: (t, t) => BsAbstract.Interface.ordering;

module Eq: BsAbstract.Interface.EQ with type t = t;
module Ord: BsAbstract.Interface.ORD with type t = t;

let compareAsInt: (t, t) => int;
let min: (t, t) => t;
let max: (t, t) => t;
let lessThan: (t, t) => bool;
let lessThanOrEq: (t, t) => bool;
let greaterThan: (t, t) => bool;
let greaterThanOrEq: (t, t) => bool;
let lt: (t, t) => bool;
let lte: (t, t) => bool;
let gt: (t, t) => bool;
let gte: (t, t) => bool;
let clamp: (~min: t, ~max: t, t) => t;
let between: (~min: t, ~max: t, t) => bool;
