#include <iostream>
#include <string>
using namespace std;

const int MAX_LETTERS = 26;
const string ALPHABET_UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHABET_LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

void setLetterCounts(string s, int letterCounts[]);
void printLetterCounts(string s, int letterCounts[]);
void initializeLetterCounts(int letterCounts[]);
bool isLetterChar(char c);
bool isUppercase(char c);
int countWords(string s);
bool isSpaceChar(char c);

int main() {
  string userInput;
  int wordCount;
  int letterCounts[MAX_LETTERS];

  cout<<"Please enter a line of text:"<<endl;
  getline(cin, userInput);

  wordCount = countWords(userInput);

  cout<<wordCount<<'\t'<<"words"<<endl;

  initializeLetterCounts(letterCounts);
  setLetterCounts(userInput, letterCounts);
  printLetterCounts(userInput, letterCounts);

  return 0;
}

/**
 *
 * Initializes an empty array of letter counts set to 0 for each letter
 *
 */

void initializeLetterCounts(int letterCounts[]) {
  for (int i = 0; i < MAX_LETTERS; i++) {
    letterCounts[i] = 0;
  }
}

/**
 * 
 * Calculates the number of occurences of each letter in a string
 * and updates the array of counts.
 *
 */

void setLetterCounts(string s, int letterCounts[]) {
  char currentChar;
  int letterIndex,
      stringLength;

  stringLength = s.length();
  for (int i = 0; i < stringLength; i++) {
    currentChar = s[i];
    if (isLetterChar(currentChar)) {
      if (isUppercase(currentChar)) {
        letterIndex = ALPHABET_UPPERCASE.find(currentChar);
        letterCounts[letterIndex] += 1;
      } else {
        letterIndex = ALPHABET_LOWERCASE.find(currentChar);
        letterCounts[letterIndex] += 1;
      }
    }
  }
}

/**
 *
 * Returns an int representing the total number of words in a string.
 *
 */

int countWords(string s) {
  int counter = 0;
  int stringLength = s.length();
  char currentChar;
  int nextSpaceIdx;
  int i = 0;
  string fragment;

  while (i < stringLength && nextSpaceIdx != -1) {
    currentChar = s[i];
    if (isSpaceChar(currentChar)) {
      i++;
    } else {
      counter += 1;
      nextSpaceIdx = s
        .substr(i, stringLength - i)
        .find(' '); 
      i += nextSpaceIdx;
    }
  }

  return counter;
}

/**
 *
 * Prints letter counts when there is at least 1 occurence of the letter in string s
 *
 */

void printLetterCounts(string s, int letterCounts[]) {
  int currentLetterCount;
  for (int i = 0; i < MAX_LETTERS; i++) {
    currentLetterCount = letterCounts[i];
    if (currentLetterCount > 0)
      cout<<currentLetterCount<<'\t'<<ALPHABET_LOWERCASE[i]<<endl;
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
 * Returns true when a character is an uppercase letter
 *
 */

bool isUppercase(char c) {
  return ('A' <= c && c <= 'Z');
}

/**
 *
 *  Returns true when a character is a space
 *
 */

bool isSpaceChar(char c) {
  return c == ' ';
}
