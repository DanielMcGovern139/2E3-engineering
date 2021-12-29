//this code takes in dates, calculates the daynumber and reads them out in order from smallest to largest 
//input
/*
2020 10 23
2000 2 14
2017 7 19
2008 4 16
2040 1 31
0 0 0
*/

//output
//2000 2 14 44
//2008 4 16 3028
//2017 7 19 6409
//2020 10 23 7601
//2040 1 31 14640

#include <iostream>
#include "dates.hpp"
using namespace std;


int main() {
const int array_size=21;
int total= 0;
int daynumber[array_size];
date dates[array_size];
int input = 1;
int y,m,d;



cout << "Enter the dates in year month day format, one per line. To finish, enter the date 0 0 0." << endl;

while (input > 0)   
{
  cin >> y >> m >> d;
  date da(y,m,d);
  
  dates[total] = da; // just stores the date for sorting later on  
  daynumber[total] = da.get_date_number(); // returns the daynumber of each slot
  total++;
  input = da.get_date_number(); 
} 

for (int start=0;start<total;start++)
	{		
		for(int i=start+1;i<total;i++)  
		{
			if(daynumber[start]>daynumber[i])
			{
				int smallest_number_so_far = daynumber[start]; //assume smallest number so far is the first position in array
				daynumber[start]=daynumber[i]; // swapping positions 
				daynumber[i] =smallest_number_so_far; // 2nd position is now smallest 

        date smallest_date_so_far = dates[start];
        dates[start] = dates[i];
        dates[i] = smallest_date_so_far;

			}
		}
	}

  
  for(int i=1;i<total; i++){
  dates[i].print_diagnostics(); 
  cout << " "<< daynumber[i] << endl;
      
   }

return 0; 
}

  
