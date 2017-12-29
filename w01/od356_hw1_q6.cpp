#include <iostream>
#include <string>
using namespace std;

int main()
{
  int quarters;   // holds the number of quarters
  int dimes;      // holds the number of dimes
  int nickels;    // holds the number of nickels
  int pennies;    // holds the number of pennies
  int totalCents; // holds the total number of cents

  int dollars;    // holds the number of dollars
  int remainderCents;      // holds the remaining number of cents after whole dollars

  cout<<"Please enter number of coins:"<<endl;
  cout<<"# of quarters: ";
  cin>>quarters;
  cout<<"# of dimes: ";
  cin>>dimes;
  cout<<"# of nickels: ";
  cin>>nickels;
  cout<<"# of pennies: ";
  cin>>pennies;

  totalCents = (quarters * 25) + (dimes * 10) + (nickels * 5) + pennies;

  dollars = totalCents / 100;
  remainderCents = totalCents % 100;

  cout<<"The total is "<<dollars<<" dollars and "<<remainderCents<<" cents"<<endl;

  return 0;
}
