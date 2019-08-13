type t =
  | Year(int);

module IntLike = {
  type nonrec t = t;
  let fromInt = v => Year(v);
  let toInt = (Year(v)) => v;
};

include ReludeEon_IntLike.MakeExtras(IntLike);

let isLeapYear = (Year(year)) =>
  year mod 4 == 0 && (year mod 100 != 0 || year mod 400 == 0);

let totalDays = year => isLeapYear(year) ? 366 : 365;

let fromInt = IntLike.fromInt;
let getYear = IntLike.toInt;

let addYears = (howMany, Year(year)) => Year(year + howMany);
let next = year => addYears(1, year);
let prev = year => addYears(-1, year);
