#include <iostream>
#include <string>
using namespace std;

string reverseString(string str);

int main() {
  string userInputString, reversedString;

  cout<<"Please enter a string to be reversed: "<<endl;
  getline(cin, userInputString);

  reversedString = reverseString(userInputString);
  cout<<"Reversed string: "<<endl;
  cout<<reversedString<<endl;

  return 0;
};

string reverseString(string str) {
  char tmp,         // holds character during swap
       *leftPtr,    // points to current left most char of string
       *rightPtr;   // points to current right most char of string

  // Initialize variables, counters
  int i = 0;
  leftPtr = &str[i];
  rightPtr = &str[str.length() - 1];

  // Iterate until the midpoint of the string is reached.
  // Note: for odd number lengths the middle character will just
  // remain the same during the reversal.
  while (i < str.length() / 2) {
    tmp = rightPtr[0];          // keep track of old value at rightPtr position
    rightPtr[0] = leftPtr[0];   // set rightPtr to leftPtr
    leftPtr[0] = tmp;           // set the old value stored in temp to leftPtr position

    // Update pointers and counter
    leftPtr++;              
    rightPtr--;
    i++;
  }

  // Return the updated string
  return str;
}
