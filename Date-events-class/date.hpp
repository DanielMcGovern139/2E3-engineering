#pragma once
class date {
  protected:
  int year;
  int month;
  int day; // day of month
  std::string weekday;
  public:
  date(int y, int m, int d); // convenience constructor
  date(); //default constructor
  ~date();

  void print_diagnostics(); // diagnostic only -- show us the values in the date object

  // getters and setters should be here

  // methods we are required to implement
  int get_date_number();
  int get_day_of_week();
};
