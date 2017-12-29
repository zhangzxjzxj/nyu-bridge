#include <iostream>
#include <cmath>
using namespace std;

// NOTE: although global variables are generally to be avoided,
// by setting a global max based on user input, the amicable number check can be
// limited to only sums less than the global max and allow the program to skip checks
// for amicable pairs outside of the valid range and make the program run faster
// and compute more amicable pairs.
int globalMax;

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs);
int sumDivisors(int num, int& outCount);
bool isPerfect(int num);
bool isNumInRange(int num, int minimum, int maximum);

int main() {
  int counter,
      num,
      outSumDivs,
      outCountDivs;

  cout<<"Please enter a number >=2: ";
  cin>>num;

  globalMax = num;
  counter = 2;

  while (counter <= num) {
    outSumDivs = 0;
    outCountDivs = 0;

    if (isPerfect(counter))
      cout<<" perfect number: "<<counter<<endl;
    counter++;
  }

  return 0;
}

bool isNumInRange(int num, int minimum, int maximum) {
  return minimum < num && num < maximum;
}

// Helper function that encapsulates the actual data needed by analyzeDividors
int sumDivisors(int num, int& outCount) {
  float squareRoot = sqrt(num);
  int sum = 0;
  int counter = 0;
  // Print divisors less than the square root
  for (int c1 = 1; c1 < squareRoot; c1++) {
    if (num % c1 == 0) {
      sum += c1;
      counter++;
    }
  }

  // Print complimentary divisiors
  for (int c2 = (int)squareRoot; c2 > 1; c2--) {
    if (num % c2 == 0) {
      sum += (num / c2);
      counter++;
    }
  }

  outCount = counter;
  return sum;
}

void analyzeDividors(int num, int& outCountDivs, int& outSumDivs){
  int count1 = 0;
  int sum = sumDivisors(num, count1);
  outSumDivs = sum;
  outCountDivs = count1;

  // When number is not prime and its sum is between itself and the max, then check for amicable pairing
  if (sum > 1 && isNumInRange(sum, num, globalMax)) {
    int count2 = 0;
    // :(
    int sum2 = sumDivisors(sum, count2);
    if (num == sum2)
      cout<<" amicable pair: ("<<sum2<<","<<sum<<")"<<endl;
  }
}

bool isPerfect(int num) {
  int outCountDivs, outSumDivs;
  analyzeDividors(num, outCountDivs, outSumDivs);
  return num == outSumDivs;
}
