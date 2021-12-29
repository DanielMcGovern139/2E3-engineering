#include <iostream>
#include <string>
#include "event.hpp"
using namespace std;

event::event(string description, int y, int m, int d): date (y, m ,d) 
{
   name_of_event = description; 
}
event :: event(){
  year = 0;
  month = 0;
  day = 0;
  name_of_event = " Default Constructor Works ";
};

void event::print_event () 
{
  date::print_diagnostics();
  cout << " " << name_of_event;
  cout << endl;
};
