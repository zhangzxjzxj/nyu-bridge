#include <iostream>
#include <cmath>
using namespace std;

const int FLOOR_ROUND = 1;
const int CEILING_ROUND = 2;
const int ROUND = 3;

int main()
{
  float numberInput,
        modOneOfNumber;
  int selectionInput,
      result;

  cout<<"Please enter a Real number: "<<endl;
  cin>>numberInput;

  cout<<"Choose your rounding method: "<<endl;
  cout<<"1. Floor round"<<endl;
  cout<<"2. Ceiling round"<<endl;
  cout<<"3. Round to the nearest whole number"<<endl;
  cin>>selectionInput;

  // rounds according to selection
  switch (selectionInput) {
    case FLOOR_ROUND:
      result = (int)(numberInput);
      break;
    case CEILING_ROUND:
      result = (int)(numberInput + 1);
      break;
    case ROUND:
    default:
      result = (int)(numberInput + 0.5);
      break;
  }

  // prints result
  cout<<result<<endl;

  return 0;
}
