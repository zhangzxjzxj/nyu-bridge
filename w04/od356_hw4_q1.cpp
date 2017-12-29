#include <iostream>
using namespace std;

int fib(int n);

int main() {
  int nInput, result;

  cout<<"Please enter a positive integer: ";
  cin>>nInput;

  result = fib(nInput);

  cout<<result<<endl;

  return 0;
}

int fib(int n) {
  int n_minus_1,  // holds th n-1st number in series
      n_minus_2,  // holds the n-2st number in series
      acc;        // holds accumulated result during loops

  // base case: first two numbers == 1
  if (n <= 1) {
    return 1;
  // otherwise, iterate to generate numbers 3 on in the series
  } else {
    // initialize values
    n_minus_1 = 1;
    n_minus_2 = 1;
    acc = n_minus_1 + n_minus_2;

    // loop over numbers in series
    for (int i = 3; i < n; i++) {
      n_minus_2 = n_minus_1;
      n_minus_1 = acc;
      acc = n_minus_1 + n_minus_2;
    }

    // return the last number computed
    return acc;
  }
};
