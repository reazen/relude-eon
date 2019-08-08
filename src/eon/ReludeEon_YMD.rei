type t;

let isLeapYear: t => bool;
let daysInMonth: t => int;
let prevMonth: t => t;
let nextMonth: t => t;
let addDays: (int, t) => t;
let nextDay: t => t;
let prevDay: t => t;
let makeWrapped: (int, ReludeEon_Month.t, int) => t;
let makeClamped: (int, ReludeEon_Month.t, int) => t;
let make: (int, ReludeEon_Month.t, int) => option(t);
let eq: (t, t) => bool;
let compare: (t, t) => BsAbstract.Interface.ordering;
module Eq: {
  type nonrec t = t;
  let eq: (t, t) => bool;
};
module Ord: {
  type nonrec t = t;
  let eq: (t, t) => bool;
  let compare: (t, t) => BsAbstract.Interface.ordering;
};
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
