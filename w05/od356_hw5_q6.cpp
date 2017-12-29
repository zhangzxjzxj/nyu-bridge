#include <iostream>
#include <string>
using namespace std;

// Making this a constant for easy reconfiguration to any character.
const char SANITIZED_CHAR = 'x';

// Type annotations for helper functions
bool isLetterChar(char c);
bool isSpaceChar(char c);
int getNextSpaceIndex(string s, int strLength, bool& hasOnlyNumbers);
void sanitizeNumbersInWord(string& s, int start, int end);

int main() {
  string userInput,               // holds user input string
         wordFragment;            // holds current word fragment being processed

  int stringLength,               // holds total number of characters in string
      stringPositionsRemaining,   // holds remaining positions of string to check
      i,                          // keeps track of current position in string loop
      wordEndIndex;               // keeps track of the index where the current word ends

  char currentChar;                   // keeps track of current character being read
  bool currentWordIsNumberSequence;   // keeps track of whether current word is a number sequence or not

  // Receives user inputs
  cout<<"Please enter a line of text:"<<endl;
  getline(cin, userInput);

  // Storing this to a variable to avoid repeated 
  // computations of a static value.
  stringLength = userInput.length();

  // Initializing counters
  i = 0;
  stringPositionsRemaining = stringLength;

  // Loop over string char by char
  while (i < stringLength) {
    currentChar = userInput[i];
    // If space is encountered, move on.  Otherwise process the word.
    if (isSpaceChar(currentChar)) {
      i++;
    } else {
      wordFragment = userInput.substr(i, stringPositionsRemaining); // Turns remaining string into a fragment
      wordEndIndex = getNextSpaceIndex(wordFragment, stringPositionsRemaining, currentWordIsNumberSequence); // Gets the index of the next space and identifies word boundaries
      // When word is a number sequence
      if (currentWordIsNumberSequence) {
        sanitizeNumbersInWord(userInput, i, i + wordEndIndex); // sanitize it
      }

      // Increment string position counter
      i += wordEndIndex;
    }
  }

  // Outputs sanitized string
  cout<<userInput<<endl;

  return 0;
}

/**
 *  HELPER FUNCTIONS
 */

/**
 *
 * Returns the index of the next space character in a string and determines
 * if it has only numbers or not.
 *
 */

int getNextSpaceIndex(string s, int strLength, bool& hasOnlyNumbers) {
  int idx = 0;
  int currentChar = 0;
  hasOnlyNumbers = true;
  if (isSpaceChar(s[idx])) return 0;

  for (idx = 0; idx < strLength; idx++) {
    currentChar = s[idx];
    if (isLetterChar(currentChar))
      hasOnlyNumbers = false;
    if (isSpaceChar(currentChar))
      return idx;
  }
  return strLength;
}

/**
 *
 * When word is a number sequence, this replaces all of them
 * with a special character.
 *
 */

void sanitizeNumbersInWord(string& s, int start, int end) {
  int endIndex = end;
  for (int i = start; i < endIndex; i++) {
    s[i] = SANITIZED_CHAR;
  }
}

/**
 *
 * Returns true when a character is a letter
 *
 */

bool isLetterChar(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

/**
 * 
 * Returns true when a character is a space
 *
 */

bool isSpaceChar(char c) {
  return c == ' ';
}
