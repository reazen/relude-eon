type t =
  | DayOfMonth(int);

module IntLike = {
  type nonrec t = t;
  let fromInt = v => DayOfMonth(v);
  let toInt = (DayOfMonth(v)) => v;
};

let fromInt = IntLike.fromInt;
let toInt = IntLike.toInt;

include ReludeEon_IntLike.MakeExtras(IntLike);
