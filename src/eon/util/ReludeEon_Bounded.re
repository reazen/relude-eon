open BsAbstract.Interface;

module MakeExtras = (B: BOUNDED) => {
  let clamp =
    fun
    | v when B.compare(v, B.bottom) == `less_than => B.bottom
    | v when B.compare(v, B.top) == `greater_than => B.top
    | v => v;

  let ensure =
    fun
    | v when B.compare(v, B.bottom) == `less_than => None
    | v when B.compare(v, B.top) == `greater_than => None
    | v => Some(v);
};

module type Compatible = {
  type t;
  type other;
  let toOther: t => other;
  let fromOther: other => t;
};

// if your type can be converted to a `EuclideanRing`, we should be able to give
// you wrapping for free
module MakeRingLikeExtras =
       (
         Bounded: BOUNDED,
         Ring: EUCLIDEAN_RING,
         RingOrd: ORD with type t = Ring.t,
         RingLike: Compatible with type t = Bounded.t and type other = Ring.t,
       ) => {
  let (toRing, fromRing) = RingLike.(toOther, fromOther);
  /**
   * An add function that takes a value of the Ring type (e.g. Int) and
   * increases the provided bounded value
   */
  let addWrapped = (howMany, bounded) => {
    let (top, bottom) = (toRing(Bounded.top), toRing(Bounded.bottom));
    let ((+), (-)) = Ring.(add, subtract);
    let (>) = (a, b) => RingOrd.compare(a, b) == `greater_than;
    let (<) = (a, b) => RingOrd.compare(a, b) == `less_than;

    // find the difference between the bounded type's top and bottom
    let rangeSize = top - bottom + Ring.one;

    // if `howMany` is greater than the bounded range, we just need to know the
    // remainder, since wrapping around 20 times is the same as wrapping once
    let remainder = Ring.modulo(howMany, rangeSize);

    // if the target output is greater than the upper bound, instead add the
    // difference to the lower bound
    let target = toRing(bounded) + remainder;

    let output =
      if (target > top) {
        bottom + target - top - Ring.one;
      } else if (target < bottom) {
        top - (bottom - target) + Ring.one;
      } else {
        target;
      };

    fromRing(output);
  };

  /**
   * Given a value of the Ring type, return a valid Bounded value, wrapping as
   * needed.
   */
  let wrappedFromRing = ring => addWrapped(ring, fromRing(Ring.zero));

  /**
   * Given a value of the Ring type, return a vlid Bounded value, clamping to
   * the upper and lower Ring bounds
   */
  let clampedFromRing = ring => {
    let (top, bottom) = (toRing(Bounded.top), toRing(Bounded.bottom));
    let (>) = (a, b) => RingOrd.compare(a, b) == `greater_than;
    let (<) = (a, b) => RingOrd.compare(a, b) == `less_than;

    ring > top
      ? fromRing(top) : ring < bottom ? fromRing(bottom) : fromRing(ring);
  };

  let ensureFromRing = ring => {
    let (top, bottom) = (toRing(Bounded.top), toRing(Bounded.bottom));
    let (>) = (a, b) => RingOrd.compare(a, b) == `greater_than;
    let (<) = (a, b) => RingOrd.compare(a, b) == `less_than;

    ring > top || ring < bottom ? None : Some(fromRing(ring));
  };
};
