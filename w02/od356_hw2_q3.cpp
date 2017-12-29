#include <iostream>
#include <string>
using namespace std;

const string STATUS_GRADUATED   = "have Graduated";
const string STATUS_SENIOR      = "are a Freshman";
const string STATUS_JUNIOR      = "are a Junior";
const string STATUS_SOPHOMORE   = "are a Sophomore";
const string STATUS_FRESHMAN    = "are a Freshman";
const string STATUS_NOT_YET     = "are not in college yet";

int main()
{
  string nameInput,
        collegeStatus;

  int graduationYear,
      currentYear,
      yearDifference;

  cout<<"Please enter your name: ";
  cin>>nameInput;

  cout<<"Please enter your graduation year: ";
  cin>>graduationYear;

  cout<<"Please enter current year: ";
  cin>>currentYear;

  yearDifference = graduationYear - currentYear;

  switch (yearDifference) {
    case 1:
      collegeStatus = STATUS_SENIOR;
      break;
    case 2:
      collegeStatus = STATUS_JUNIOR;
      break;
    case 3:
      collegeStatus = STATUS_SOPHOMORE;
      break;
    case 4:
      collegeStatus = STATUS_FRESHMAN;
      break;
    default:
      if (yearDifference <= 0)
        collegeStatus = STATUS_GRADUATED;
      else
        collegeStatus = STATUS_NOT_YET;
      break;
  }

  cout<<nameInput<<", you "<<collegeStatus<<endl;

  return 0;
}
