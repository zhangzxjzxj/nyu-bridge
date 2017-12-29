#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int currentNumberInSequence,      // holds current number in sequence for section a
      currentNumberInSequence2,     // holds current number in sequence for section b
      rollingProduct,               // holds rolling product during iterations
      counter;                      // holds number of iterations of loops

  float sequenceLengthInput,        // holds user entered input length in section a
        exponent,                   // holds the fractional exponent used for computing the root
        result;                     // holds the result to show the user

  // Section A:
  cout<<"section a"<<endl<<endl;

  cout<<"Please enter the length of the sequence: ";
  cin>>sequenceLengthInput;

  cout<<"Please enter your sequence: "<<endl;

  // Initializes rollingProduct
  rollingProduct = 1;

  if (sequenceLengthInput == 0) { // handles a 0-length input
    currentNumberInSequence = 1;
  } else { // handles valid inputs
    for (counter = 1; counter <= sequenceLengthInput; counter++) {
      cin>>currentNumberInSequence;
      rollingProduct *= currentNumberInSequence;
    }
  }

  // calculates the nth root of the product of the numbers in the series
  exponent = (1.0 / sequenceLengthInput);
  result = pow(rollingProduct, exponent);

  cout<<"The geometric mean is: "<<result<<endl;

  cout<<endl<<endl<<"section b"<<endl<<endl;

  cout<<"Please enter a non-empty sequence of positive integers, each one in a separate line.  End your sequence by typing -1: "<<endl;

  rollingProduct = 1;
  cin>>currentNumberInSequence2;
  counter = 0;
  while (currentNumberInSequence2 != -1) {
    counter++;
    rollingProduct *= currentNumberInSequence2;
    cin>>currentNumberInSequence2;
  }

  // calculates the nth root of the product of the numbers in the series (type-coerces the counter from int to float)
  exponent = (1.0 / (float)counter);
  result = pow(rollingProduct, exponent);
  cout<<"The geometric mean is: "<<result<<endl;

  return 0;
}
