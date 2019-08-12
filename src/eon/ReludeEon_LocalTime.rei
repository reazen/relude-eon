type t;

module Eq: BsAbstract.Interface.EQ with type t = t;
module Ord: BsAbstract.Interface.ORD with type t = t;
module Bounded: BsAbstract.Interface.BOUNDED with type t = t;

let eq: (t, t) => bool;
let compare: (t, t) => BsAbstract.Interface.ordering;
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

let fromMillisecondsWrapped: int => t;
let fromMillisecondsClamped: int => t;
let makeWrapped: (int, int, int, int) => t;
let makeWrappedLabels:
  (~hour: int=?, ~minute: int=?, ~second: int=?, ~millisecond: int=?, unit) =>
  t;
let makeClamped: (int, int, int, int) => t;
let makeClampedLabels:
  (~hour: int=?, ~minute: int=?, ~second: int=?, ~millisecond: int=?, unit) =>
  t;

let midnight: t;
let noon: t;

let toTuple: t => (int, int, int, int);
let getHour: t => int;
let getMinute: t => int;
let getSecond: t => int;
let getMillisecond: t => int;

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
