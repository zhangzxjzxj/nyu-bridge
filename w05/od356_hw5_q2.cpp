#include <iostream>
using namespace std;

bool isPalindrome(string str);

int main() {
  string word;
  bool result;

  cout<<"Please enter a word: ";
  cin>>word;

  result = isPalindrome(word);

  if (result)
    cout<<word<<" is a palindrome."<<endl;
  else
    cout<<word<<" is not a palindrome."<<endl;

  return 0;
}

bool isPalindrome(string str) {
  bool result;
  int i = 0;
  int j = str.length() - 1;
  // Iterate over the string char by char from outside in
  while (i < j) {
    // check if chars match
    if (str[i] != str[j])
      // if not, return and exit loop because it's not a palindrome
      return false;
    // keep iterating when the chars match
    i++;
    j--;
  }
  return true;
}
