#include <iostream>
#include <ctime>
using namespace std;

const int POSSIBLE_DIGITS = 10;
const int PIN_SIZE        = 5;
int PIN[PIN_SIZE]         = {1, 2, 3, 4, 5};

void printArr(int arr[], int arrSize);

void makeEmptyRow(int arr[], int size);
void printPinLabel(int maxDigits);
void printNumMapping(int mapping[], int size);
void getUserInputArr(int arr[]);

int numberCharToInt(char c);

int main() {
  int mapping[POSSIBLE_DIGITS];     // an array of possible digits
  int userInput[PIN_SIZE];          // an array of digits entered by user
  int c1;                           // a misc counter

  /*
   * The lookupTable is used for transforming user-entered digits,
   * back into real pin digits.  It starts in a null state like
   * the one below:
   *
   * [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
   *  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
   *  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
   *
   *  Each row index represents a possible value (1 to 3, though
   *  normalized to 0 - 2 in this case) and each row is an array
   *  whose index represents a digit 0 - 9 from the real PIN.
   *
   *  Assuming a mapping such as this:
   *
   *  [3, 2, 3, 1, 1, 3, 2, 2, 1, 3]
   *
   *  And the pin 12345
   *
   *  The lookup table would be populated as follows
   *
   * [[0, 0, 0, 1, 1, 0, 0, 0, 1, 0]
   *  [0, 1, 0, 0, 0, 0, 1, 1, 0, 0]
   *  [0, 0, 1, 0, 0, 1, 0, 0, 0, 1]]
   *
   *  This would allow the real pin digit to be discovered
   *  as a "hit" or "miss" on a digit by digit basis using
   *  a loop going through each user entered digit and the
   *  real pin in parallel and executing the following
   *  expression at each step:
   *
   *  lookupTable[userInputDigit][realPinValueAtCurrentPosition] == 1;
   *
   *  When true, the digit is correct, when false it's incorrect.
   *
   */

  int lookupTable[3][10];

  // Seed the rand function with current time for better randomization
  srand((int) time(0));

  // Make empty lookup table
  for (int i = 0; i < 3; i++) {
    makeEmptyRow(lookupTable[i], POSSIBLE_DIGITS);
  }

  printPinLabel(POSSIBLE_DIGITS);

  // Enter the real pin into the lookup table based on mapping
  for (int i = 0; i < POSSIBLE_DIGITS; i++) {
    c1 = (rand() % 3) + 1;
    mapping[i] = c1;
    lookupTable[c1 - 1][i] = 1;
  } 

  printNumMapping(mapping, POSSIBLE_DIGITS);

  getUserInputArr(userInput);

  int val;
  int realPinVal;
  int i = 0;
  bool mismatchedDigitFound = false;

  while ((i < PIN_SIZE) && !mismatchedDigitFound) {
    val = userInput[i];
    realPinVal = PIN[i];
    mismatchedDigitFound = lookupTable[val - 1][realPinVal] != 1;
    i++;
  }

  if (mismatchedDigitFound)
    cout<<"Your PIN is not correct"<<endl;
  else
    cout<<"Your PIN is correct"<<endl;

  return 0;
}

void makeEmptyRow(int arr[], int size) {
  for (int j = 0; j < size; j++) {
    arr[j] = 0;
  }
}

void printPinLabel(int maxDigits) {
  cout<<"PIN: ";
  for (int i = 0; i < POSSIBLE_DIGITS; i++) {
    cout<<i<<' ';
  }
  cout<<endl;
}

void printNumMapping(int mapping[], int size) {
  cout<<"NUM: ";
  printArr(mapping, size);
}

void getUserInputArr(int arr[]) {
  int digit;
  int c2 = 0;
  string userInputString;

  getline(cin, userInputString, '\n');

  for (int i = 0; i < userInputString.length(); i++) {
    digit = numberCharToInt(userInputString[i]);
    arr[i] = digit;
  }
}

int numberCharToInt(char c) {
  return (int)c - 48;
}

void printArr(int arr[], int arrSize) {
  int i;
  for (i = 0; i < arrSize; i++) {
    cout<<arr[i]<<' ';
  }
  cout<<endl;
}
