module Year = ReludeEon_Year;
module Month = ReludeEon_Month;
module DayOfMonth = ReludeEon_DayOfMonth;
module Hour = ReludeEon_Hour;
module Minute = ReludeEon_Minute;
module Second = ReludeEon_Second;
module Millisecond = ReludeEon_Millisecond;
module OffsetMinute = ReludeEon_OffsetMinute;

// common combinations of units
module LocalDate = ReludeEon_LocalDate; // (year, month, day)
module LocalTime = ReludeEon_LocalTime; // (hour, minute, second, millisecond)
module LocalDateTime = ReludeEon_LocalDateTime; // both of the above
module Instant = ReludeEon_Instant; // local date time + offset minutes
module InstantUTC = ReludeEon_InstantUTC; // instant with offset = 0

module Interop = {
  module JsDate = ReludeEon_Interop_JsDate;
};
