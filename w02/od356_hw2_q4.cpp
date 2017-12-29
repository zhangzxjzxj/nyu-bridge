#include <iostream>
#include <cmath>
using namespace std;

const string OUTPUT_MESSAGE       = "This equation has "; 

const string SOLUTIONS_INFINITE   = "an infinite number of solutions ";
const string SOLUTIONS_NONE       = "no solution";
const string SOLUTIONS_NO_REAL    = "no real solution";
const string SOLUTIONS_ONE        = "a single real solution ";
const string SOLUTIONS_TWO        = "two real solutions ";

int main()
{
  int a, b, c;

  double discriminant,
         sqrtResult,
         x1,
         x2;

  bool isValidX1,
       isValidX2;

  cout<<"Please enter value of a: ";
  cin>>a;
  cout<<"Please enter value of b: ";
  cin>>b;
  cout<<"Please enter value of c: ";
  cin>>c;

  // Formats console output
  cout.setf(ios::fixed);
  cout.precision(1);

  if (a == 0 && b == 0 && c != 0) { // Case for no solutions
    cout<<OUTPUT_MESSAGE<<SOLUTIONS_NONE;
  } else if (a == 0 && b == 0 && c == 0) { // Case for infinite solutions
    cout<<OUTPUT_MESSAGE<<SOLUTIONS_INFINITE;
  } else if (a == 0 && b != 0) {
    x1 = (-1 * c) / b;
    cout<<OUTPUT_MESSAGE<<SOLUTIONS_ONE<<"x="<<x1;
  } else {
    // Calculates discriminante
    discriminant = (pow(b, 2) - (4 * a * c));

    if (discriminant < 0) { // Case for no real solutions
      cout<<OUTPUT_MESSAGE<<SOLUTIONS_NO_REAL<<endl;
    } else if (discriminant == 0) { // Case for 1 solution
      x1 = (-1 * b) / (2 * a); // Calculate 1 solution

      // check solution
      isValidX1 = 0 == (a * pow(x1, 2) + (b * x1) + c);
      if (isValidX1)
        cout<<OUTPUT_MESSAGE<<SOLUTIONS_ONE<<"x="<<x1<<endl;
      else
        cout<<OUTPUT_MESSAGE<<SOLUTIONS_NONE<<endl;
    } else { // Case for 2 solutions: disciminant > 0
      sqrtResult = sqrt(discriminant);
      x1 = ((-1 * b) + sqrtResult) / (2 * a);
      x2 = ((-1 * b) - sqrtResult) / (2 * a);

      // check both solutions
      isValidX1 = 0 == (a * pow(x1, 2) + (b * x1) + c);
      isValidX2 = 0 == (a * pow(x2, 2) + (b * x2) + c);

      if (isValidX1 && isValidX1)
        cout<<OUTPUT_MESSAGE<<SOLUTIONS_TWO<<"x="<<x1<<" and x="<<x2<<endl;
      else
        cout<<OUTPUT_MESSAGE<<SOLUTIONS_NONE<<endl;
    }
  }

  return 0;
}
