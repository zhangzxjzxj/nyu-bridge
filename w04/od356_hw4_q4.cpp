#include <iostream>
#include <cmath>
using namespace std;

void printDivisors(int num);

int main() {
  int numberInput;    // holds user-entered number

  cout<<"Please enter a positive integer >= 2: ";
  cin>>numberInput;
  printDivisors(numberInput);
  return 0;
}

void printDivisors(int num) {
  float squareRoot = sqrt(num);
  // Print divisors less than the square root
  for (int counter = 1; counter < squareRoot; counter++) {
    if (num % counter == 0) {
      cout<<counter<<' ';
    }
  }

  // Print complimentary divisiors
  for (int counter = (int)squareRoot; counter >= 1; counter--) {
    if (num % counter == 0) {
      cout<<(num / counter)<<' ';
    }
  }

  cout<<endl;
}
