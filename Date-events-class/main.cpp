//input
//2020 10 23:A day in October
//2000 2 14:Valentine's Day
//2017 7 19:A fine July day
//2008 4 16:April showers -- on and on for hours and hours
//2040 1 31:What a day this will be
//0 0 0

//output
//2000 2 14 Valentine's Day
//2008 4 16 April showers -- on and on for hours and hours
//2017 7 19 A fine July day
//2020 10 23 A day in October
//2040 1 31 What a day this will be



#include <iostream>
#include <string>
#include "event.hpp"
using namespace std;


int main() {

  const int size = 21;
  event event_type[size]; 
  int total = 0; 
  int testyear, testmonth, testday;
  
  cout << "Enter the events in year month day:description format, one per line. To finish, enter the date 0 0 0.";
  
  for (int i = 0; i < size; i++){
  char c;
  cin >> testyear >> testmonth >> testday;
  
    if (testyear == 0 && testmonth == 0 && testday == 0 ){
    break;
    }

  cin >> c; 
  string name_of_event;
  string description;
  getline(cin,name_of_event);
  
  int year,month, day;
    
    year = testyear;
    month = testmonth;
    day = testday;
    description = name_of_event; 
      
  event ev(description, year, month, day); //putting 4 things into ev object 
  event_type[i] = ev; //mathcing the object with the array
 
  total++;
  }

  cout << endl;
    

for (int i = 0; i < total; i++) {
    
    for (int j = i + 1; j < total; j++){
      if (event_type[i].get_date_number()>event_type[j].get_date_number()){  

      event smallest_date = event_type[i];
      event_type[i] = event_type[j]; // swap the posotions around 
      event_type[j] = smallest_date; 
  }
  }
}

   for ( int i = 0; i < total; i++)
   {
    event_type[i].print_event(); //this prints events in order of array
  
   }

   return 0;
}
