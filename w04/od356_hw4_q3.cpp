#include <iostream>
using namespace std;

// Constants
int const DAYS_IN_WEEK = 7;
int const NUM_OF_MONTHS = 12;

// Months
int const JAN = 1;
int const FEB = 2;
int const MAR = 3;
int const APR = 4;
int const MAY = 5;
int const JUN = 6;
int const JUL = 7;
int const AUG = 8;
int const SEP = 9;
int const OCT = 10;
int const NOV = 11;
int const DEC = 12;

// Function type annotations
int printMonthCalendar(int numOfDays, int startingDay);
bool isLeapYear(int year);
int daysInMonth(int month, bool isLeapYear);
string nameOfMonth(int month);
void printYearCalendar(int year, int startingDay);

// Program main
int main() {
  int startDay,     // holds user-entered start day of week for year
      year;         // holds user-entered year

  cout<<"Please enter the year: ";
  cin>>year;
  cout <<"Please enter the day of the week (1-7) the first day of the year lands on: ";
  cin>>startDay;

  printYearCalendar(year, startDay);

  return 0;
}

/**
 * 
 * Prints a formatted monthly calendar of that month.
 *
 * @param numOfDays - The number of days in the month
 * @param startingDay - a number 1-7 that represents the day in the week of the first day
 *
 * @return int - a number 1-7 that represents the day in the week of the last day in that month
 *
 */

int printMonthCalendar(int numOfDays, int startingDay) {
  int currentDayInWeek,     // a rolling counter of which is the current day in the week 0-6
      displayedDay,         // the numerical day to print for each day of month
      leadingSpaces,        // how many leading spaces to add (0 normalized)
      cells;                // a counter to compute current day of week. represents cells printed.

  leadingSpaces = (startingDay - 1) % DAYS_IN_WEEK;

  // Prints the heading for the month
  cout<<"Mon\tTue\tWed\tThr\tFri\tSat\tSun\n";

  // Initialize counter 
  cells = 0;

  for (int i = 1 - leadingSpaces; i <= numOfDays; i++) {
    // When i is negative or 0, the leading spaces are being printed
    if (i < 1) {
      cout<<'\t';
    // In other cases, numbers are being printed
    } else {
      currentDayInWeek = cells % DAYS_IN_WEEK; 
      displayedDay = i;
      if (displayedDay > 0)
        cout<<displayedDay;
      // follow each printed day with a tab
      cout<<'\t';
      // print spaces at the end of the week
      if (currentDayInWeek == DAYS_IN_WEEK - 1)
        cout<<endl;
    }
    // increments the printed cell counter
    cells++;
  }

  cout<<endl;
  return (currentDayInWeek % DAYS_IN_WEEK) + 1;
}

/**
 *
 * Determines if a year is a leap year in the Gregorian calendar system
 * is a leap year or not.
 *
 * @return bool
 *
 */ 

bool isLeapYear(int year) {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

/**
 * 
 * @param   int month       - the number of the month (starting with 1 for Januaray)
 * @param   int isLeapYear  - whether or not the month is in a leap year
 * @return  int             - number of days in a month
 *
 */

int daysInMonth(int month, bool isLeapYear) {
  switch (month) {
    case FEB:
      if (isLeapYear)
        return 29;
      else
        return 28;
    case APR:
    case JUN:
    case SEP:
    case NOV:
      return 30;
    default:
      return 31;
  }
}

string nameOfMonth(int month) {
  switch (month) {
    case JAN:
      return "January";
    case FEB:
      return "February";
    case MAR:
      return "March";
    case APR:
      return "April";
    case MAY:
      return "May";
    case JUN:
      return "June";
    case JUL:
      return "July";
    case AUG:
      return "August";
    case SEP:
      return "September";
    case OCT:
      return "October";
    case NOV:
      return "November";
    case DEC:
      return "December";
    default:
      return "UNKNOWN MONTH";
  }
  return "UNKNOWN MONTH";
}

void printYearCalendar(int year, int startingDay) {
  int lastMonthEndDay = startingDay - 1;
  int daysInCurrentMonth;
  bool isCurrentYearLeapYear = isLeapYear(year);
  for (int currentMonth = 1; currentMonth <= NUM_OF_MONTHS; currentMonth++) {
    daysInCurrentMonth = daysInMonth(currentMonth, isCurrentYearLeapYear);
    cout<<nameOfMonth(currentMonth)<<" "<<year<<endl;
    lastMonthEndDay = printMonthCalendar(daysInCurrentMonth, lastMonthEndDay + 1);
    cout<<endl;
  }
}
