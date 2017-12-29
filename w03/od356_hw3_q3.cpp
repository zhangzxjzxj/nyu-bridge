#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int numberInput,            // holds the number the user entered
      intermediateRemainder,  // holds a rolling remainder from the loop
      quotient,               // holds a rolling quotient from the loop
      intermediateResult;     // holds a rolling quotient in the while loop

  char binaryDigit;           // holds binary digit at each step of loop

  string output = "";         // holds the string of binary digits to show user

  // gets input from user
  cout<<"Enter decimal number: "<<endl;
  cin>>numberInput;

  // initializes loop
  intermediateResult = numberInput;

  while (intermediateResult > 0) {
    quotient = intermediateResult / 2;
    intermediateRemainder = intermediateResult % 2;

    // Determines whether to set a 1 or 0 at each position
    if (intermediateRemainder == 1)
        binaryDigit = '1';
    else
        binaryDigit = '0';

    output = binaryDigit + output; // prepends binary digit to output string
    intermediateResult = quotient; // re-assigns the rolling quotient for next loop iteration
  }

  cout<<"The binary representation of "<<numberInput<<" is "<<output<<endl;

  return 0;
}
