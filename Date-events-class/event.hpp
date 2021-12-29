#pragma once
#include <string>
#include "date.hpp"
using namespace std;


class event : public date {
  protected:
  string name_of_event;
  public:
  event (string description, int y, int m, int d);
  event(); 
  void print_event (); 
};

