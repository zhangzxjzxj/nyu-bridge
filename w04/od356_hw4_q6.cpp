#include <iostream>
#include <cmath>
using namespace std;

double eApprox(int n);

int main() {
  cout.precision(30);
  for (int n = 1; n <= 15; n++) {
    cout<<"n = "<<n<<'\t'<<eApprox(n)<<endl;
  }
  return 0;
}

double eApprox(int n) {
  // initializes variables
  double sum = 1.0;
  double f = 1.0;
  
  // NOTE: using one loop for both sum for efficiency
  for (int counter = 1; counter <= n; counter++) {
    f *= (double)counter;
    sum += ((double)1.0 / f);
  }

  return sum;
}
