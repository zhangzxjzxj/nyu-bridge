#include <iostream>
#include <cmath>
using namespace std;

// char constants for each roman numeral character to keep code below more readable
const int ROMAN_1     = 'I';
const int ROMAN_5     = 'V';
const int ROMAN_10    = 'X';
const int ROMAN_50    = 'L';
const int ROMAN_100   = 'C';
const int ROMAN_500   = 'D';
const int ROMAN_1000  = 'M';

int main() {
  int numberInput,                // holds the number the user input
      intermediateResult,         // holds the intermediate result during looping
      c1,                         // one of two loop counters
      c2,                         // second of two loop counters
      c2mod2,                     // holds the result of the c2 counter mod 2
      numeralValue,               // the current numeral grouping
      currentNumeralInstances;    // the number of times the current numeral character is repeated in output string;

  string output,                  // holds the output string
         fragment,                // holds each fragment of the output string in progress
         numSign;                 // holds char value of sign of number (- or +

  char currentRomanNumeralChar;   // holds the current roman numeral character being used

  bool isNegative;                // holds information about whether user entered a negative value

  // prompts user for a number
  cout<<"Enter a decimal number: "<<endl;
  cin>>numberInput;

  if (numberInput == 0) {
    // exits program early when number is 0;
    cout<<numberInput<<" is nulla"<<endl;
    return 0;
  } else if (numberInput < 0) {
    // removes sign temporarily when number is negative
    numberInput *= -1;
    isNegative = true;
    numSign = " -";
  } else {
    // proceeds normally otherwise
    isNegative = false;
    numSign = " ";
  }

  // initializes the loop below
  intermediateResult = numberInput;
  c1 = 3;
  c2 = 6;
  numeralValue = 1;

  while (c1 >= 0) { // reverse loop over each roman numeral value
    c2mod2 = c2 % 2; // used for numeral value computation
    numeralValue = (pow(5,(c2mod2))) * (pow(10, c1)); // generates roman numeral values based on counters

    // selects a roman numeral char based on the value
    if (numeralValue == 1)
        currentRomanNumeralChar = ROMAN_1;
    else if (numeralValue == 5)
        currentRomanNumeralChar = ROMAN_5;
    else if (numeralValue == 10)
        currentRomanNumeralChar = ROMAN_10;
    else if (numeralValue == 50)
        currentRomanNumeralChar = ROMAN_50;
    else if (numeralValue == 100)
        currentRomanNumeralChar = ROMAN_100;
    else if (numeralValue == 500)
        currentRomanNumeralChar = ROMAN_500;
    else if (numeralValue == 1000)
        currentRomanNumeralChar = ROMAN_1000;
    else
        cout<<"No roman numeral found for: "<<numeralValue<<endl; // This should never fire, but it's here just in case.

    if (intermediateResult >= numeralValue) {
      fragment = ""; // resets the fragment variable
      currentNumeralInstances = intermediateResult / numeralValue;
      while (currentNumeralInstances > 0) { // adds appropriate number of instances of the current numeral to fragment string
        fragment += currentRomanNumeralChar;
        currentNumeralInstances--;
      }
      intermediateResult = intermediateResult % numeralValue;
      output += fragment;
    }

    // increments counter 1 only when the second counter is even
    if (c2mod2 == 0)
      c1--;
    c2--;
  }

  if (isNegative)
    numberInput *= -1;

  cout<<numberInput<<" is"<<numSign<<output<<endl;
  return 0;
}
