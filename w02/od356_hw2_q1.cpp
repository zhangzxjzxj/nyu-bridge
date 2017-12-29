#include <iostream>
using namespace std;

int main()
{
  // allocate int variables for most values
  int num1,
      num2,
      sum,
      difference,
      product,
      divQuotient,
      mod;

  // ...except the quotient which needs to be a float
  float quotient;

  cout<<"Please enter two positive integers, separated by a space:"<<endl;
  cin>>num1>>num2;

  // compute all results and store to variables
  sum = num1 + num2;
  difference = num1 - num2;
  product = num1 * num2;
  quotient = (float)num1 / (float)num2;
  divQuotient = num1 / num2;
  mod = num1 % num2;

  // print all expressions
  cout<<num1<<" + "<<num2<<" = "<<sum<<endl;
  cout<<num1<<" - "<<num2<<" = "<<difference<<endl;
  cout<<num1<<" * "<<num2<<" = "<<product<<endl;
  cout<<num1<<" / "<<num2<<" = "<<quotient<<endl;
  cout<<num1<<" div "<<num2<<" = "<<divQuotient<<endl;
  cout<<num1<<" mod "<<num2<<" = "<<mod<<endl;

  return 0;
}
