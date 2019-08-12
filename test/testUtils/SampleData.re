open ReludeEon;

// -----------------------------------------------------------------------------
// LocalDate (Year-Month-Day) values
// -----------------------------------------------------------------------------

let ymd20180131 = LocalDate.makeClamped(2018, Jan, 31);
let ymd20180808 = LocalDate.makeClamped(2018, Aug, 8);
let ymd20181004 = LocalDate.makeClamped(2018, Oct, 4);
let ymd20181201 = LocalDate.makeClamped(2018, Dec, 1);
let ymd20181231 = LocalDate.makeClamped(2018, Dec, 31);
let ymd20190101 = LocalDate.makeClamped(2019, Jan, 1);
let ymd20190131 = LocalDate.makeClamped(2019, Jan, 31);
let ymd20190221 = LocalDate.makeClamped(2019, Feb, 21);
let ymd20190228 = LocalDate.makeClamped(2019, Feb, 28);
let ymd20190301 = LocalDate.makeClamped(2019, Mar, 1);
let ymd20200131 = LocalDate.makeClamped(2020, Jan, 31);
let ymd20200228 = LocalDate.makeClamped(2020, Feb, 28);
let ymd20200229 = LocalDate.makeClamped(2020, Feb, 29);
let ymd20200301 = LocalDate.makeClamped(2020, Mar, 1);
let ymd20200331 = LocalDate.makeClamped(2020, Mar, 31);

// -----------------------------------------------------------------------------
// LocalTime (Hour-Minute-Second-Milli) values
// -----------------------------------------------------------------------------

let timeMin = LocalTime.fromMillisecondsClamped(0);
let timeMax =
  LocalTime.makeClampedLabels(
    ~hour=23,
    ~minute=59,
    ~second=59,
    ~millisecond=999,
    (),
  );
