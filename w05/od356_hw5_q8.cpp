#include <iostream>
#include <string>
using namespace std;

const int MAX_LETTERS = 26;
const string ALPHABET_UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHABET_LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

void initializeLetterCounts(int letterCounts[]);
void setLetterCounts(string s, int letterCounts[]);
bool isLetterChar(char c);
bool isUppercase(char c);

int main() {
  string userInput1,
         userInput2;

  int letterCounts1[MAX_LETTERS];
  int letterCounts2[MAX_LETTERS];

  initializeLetterCounts(letterCounts1);
  initializeLetterCounts(letterCounts2);

  bool mismatchedCountFound = false;

  cout<<"Please enter the first string: "<<endl;
  getline(cin, userInput1);
  cout<<"Please enter the second string: "<<endl;
  getline(cin, userInput2);

  setLetterCounts(userInput1, letterCounts1);
  setLetterCounts(userInput2, letterCounts2);

  int i = 0;

  while (i < MAX_LETTERS && !mismatchedCountFound) {
    mismatchedCountFound = letterCounts1[i] != letterCounts2[i];
    i++;
  }

  if (mismatchedCountFound)
    cout<<"The two strings are not anagrams."<<endl;
  else
    cout<<"The two strings are anagrams."<<endl;
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

