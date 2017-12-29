#include <iostream>
#include <string>

using namespace std;

const int MINUTES_PER_HOUR = 60;  // used for conversions

const int MINUTES_8_AM = 8 * MINUTES_PER_HOUR;      // 8:00am expressed in minutes since midnight
const int MINUTES_6_PM = 18 * MINUTES_PER_HOUR;     // 6:00pm expressed in minutes since midnight

int main()
{
  string timeStartInput;      // holds the HH:MM string value of call start time

  int timeStartMinutes,       // holds the normalized start time in minutes since midnight
      timeEndMinutes,         // holds the normalized end time in minutes since midnight
      callDuration;           // holds the call duration in minutes

  bool isWeekday;             // true if day is Mo - Fr, otherwise false
  string dayOfWeekInput;      // holds the user input day of week as Mo,Tu,We,Th,Fr,Sa,Su;

  float ratePerMinute;        // holds the rate of the call in dollars

  int startHours,             // holds the number of hours in the HH:MM time
      startMinutes,           // holds the number of minutes in the HH:MM time
      delimterLocation;       // holds the string char index of the ':' delimiter

  char delimiter;             // no-op
  double callCost;

  cout<<"Please enter the day of the week: ";
  cin>>dayOfWeekInput;

  cout<<"Please enter the time the call started (in 24-hour notation as HH:MM): ";
  cin>>startHours>>delimiter>>startMinutes;
  cout<<"Please enter the call duration in minutes: ";
  cin>>callDuration;

  // Parse the start time from the string input

  timeStartMinutes = (startHours * MINUTES_PER_HOUR) + startMinutes; // Normalizes the start time to minutes for easier comparisons below

  // Determines if it's a weekend or a weekday
  if (dayOfWeekInput == "Su" || dayOfWeekInput == "Sa")
    isWeekday = false;
  else
    isWeekday = true;

  // Weekdays
  if (isWeekday) {
    // Checks if call started within 8 - 6pm hours or not
    if (timeStartMinutes >= MINUTES_8_AM && timeStartMinutes <= MINUTES_6_PM) {
      ratePerMinute = 0.40;
    } else {
      ratePerMinute = 0.25;
    }
  // Weekends
  } else {
    ratePerMinute = 0.15;
  }

  callCost = callDuration * ratePerMinute;

  cout<<"Your call at "<<timeStartInput<<" for "<<callDuration<<" minutes costs: "<<endl;
  cout<<callCost<<endl;
  return 0;
}
