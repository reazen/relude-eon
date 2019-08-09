type t;

module Eq: BsAbstract.Interface.EQ with type t = t;
module Ord: BsAbstract.Interface.ORD with type t = t;
module Bounded: BsAbstract.Interface.BOUNDED with type t = t;

let makeClamped: int => t;
let makeWrapped: int => t;
let make: int => option(t);

let addMinutes: (int, t) => t;
let getMinutes: t => int;

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
