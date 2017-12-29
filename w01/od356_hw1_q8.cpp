#include <iostream>
#include <string>
using namespace std;

const int MINUTES_IN_HOUR     = 60;
const int MINUTES_IN_DAY      = MINUTES_IN_HOUR * 24;

int main()
{
  string person1 = "John";
  string person2 = "Bill";

  int days1;      // number of days person 1 worked
  int hours1;     // number of hours person 1 worked
  int minutes1;   // number of minutes person 1 worked

  int days2;      // number of days person 2 worked
  int hours2;     // number of hours person 2 worked
  int minutes2;   // number of minutes person 2 worked

  int combinedMinutes; // all the minutes between both

  int totalDays;    // total number of days between both for final result
  int totalHours;   // total number of hours between both for final result
  int totalMinutes; // total number of minutes between both for final result

  int currentRemainder; // a running tally of the remainder after each operation

  // Get data for person 1
  cout<<"Please enter the number of days "<<person1<<" has worked: ";
  cin>>days1;

  cout<<"Please enter the number of hours "<<person1<<" has worked: ";
  cin>>hours1;

  cout<<"Please enter the number of minutes "<<person1<<" has worked: ";
  cin>>minutes1;

  cout<<endl;

  // Get data for person 2
  cout<<"Please enter the number of days "<<person2<<" has worked: ";
  cin>>days2;

  cout<<"Please enter the number of hours "<<person2<<" has worked: ";
  cin>>hours2;

  cout<<"Please enter the number of minutes "<<person2<<" has worked: ";
  cin>>minutes2;

  cout<<endl;

  // Normalizes all the inputs into a single unit: minutes
  combinedMinutes = ((days1 + days2) * MINUTES_IN_DAY) + ((hours1 + hours2) * MINUTES_IN_HOUR) + (minutes1 + minutes2);

  // De-normalizes minutes into total days for final result and updates running tally
  totalDays = combinedMinutes / MINUTES_IN_DAY;
  currentRemainder = combinedMinutes % MINUTES_IN_DAY;

  // De-normalizes minutes into total hours for final result and updates running tally
  totalHours = (currentRemainder / MINUTES_IN_HOUR);
  currentRemainder = currentRemainder % MINUTES_IN_HOUR;

  // Whatever is left here is the final result for minutes
  totalMinutes = currentRemainder;

  cout<<"The total time both of them worked together is: "<<totalDays<<" days, "<<totalHours<<" hours and "<<totalMinutes<<" minutes."<<endl;

  return 0;
}
