#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int numberInput,      // holds the value of n the user entered
      digitShifter,     // holds a number used in digit-shifting-division during the inner while loop
      evenDigits,       // holds the number of even digits in the current number in the sequence
      totalDigits,      // holds the total number of digits in the current number in the sequence
      digit,            // holds the current number in the sequence
      numberInSequence, // a counter used in the outer most loop to hold current number in sequence
      shiftedNumber;    // a counter to store the number as it shifts over by a digit

  cout<<"Please enter a positive integer: ";
  cin>>numberInput;

  // initializes outer loop
  numberInSequence = 1;
  for (numberInSequence = 1; numberInSequence <= numberInput; numberInSequence++) {
    // initializes inner loop
    shiftedNumber = numberInSequence;
    totalDigits = 0;
    evenDigits = 0;
    // loops through digits one by one until it his the decimal point (i.e. 10 to the 0th power)
    while (shiftedNumber > 0) {
      digit = shiftedNumber % 10;
      totalDigits++;
      if (digit % 2 == 0) {
        evenDigits++;
      }
      shiftedNumber /= 10;
    }

    // if the number of even digits is more than half of the total digits then print the number
    if (evenDigits > (totalDigits / 2)) {
      cout<<numberInSequence<<endl;
    }
  }

  return 0;
}
