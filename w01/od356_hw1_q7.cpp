#include <iostream>
#include <string>
using namespace std;

const int VALUE_OF_QUARTER    = 25;
const int VALUE_OF_DIME       = 10;
const int VALUE_OF_NICKEL     = 5;
const int VALUE_OF_PENNY      = 1;

int main()
{
  int dollars;          // holds the number of user-entered dollars
  int cents;            // holds the number of user-entered cents
  int totalCents;       // holds the number of total cents (including whole dollars)

  int quarters  = 0;    // holds max amount of quarters, initialized to 0
  int dimes     = 0;    // holds max amount of dimes, initialized to 0
  int nickels   = 0;    // holds max amount of nickels, initalized to 0
  int pennies   = 0;    // holds max amount of pennies, initalized to 0

  int currentRemainder; // holds the remainders

  cout<<"Please enter your amount in the format of dollars and cents separated by a space"<<endl;
  cin>>dollars>>cents;
  cout<<dollars<<" dollars and "<<cents<<" cents are:"<<endl;

  totalCents = (dollars * 100) + cents;

  quarters = totalCents / VALUE_OF_QUARTER;
  currentRemainder = totalCents % VALUE_OF_QUARTER;

  dimes = currentRemainder / VALUE_OF_DIME;
  currentRemainder = currentRemainder % VALUE_OF_DIME;

  nickels = currentRemainder / VALUE_OF_NICKEL;
  currentRemainder = currentRemainder % VALUE_OF_NICKEL;

  pennies = currentRemainder;

  cout<<quarters<<" quarters, "<<dimes<<" dimes, "<<nickels<<" nickels and "<<pennies<<" pennies"<<endl;

  return 0;
}
