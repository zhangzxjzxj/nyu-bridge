#include <iostream>
#include <cmath>
using namespace std;

const float KILOS_PER_POUND       = 0.453592;
const float METERS_PER_INCH       = 0.0254;

const string STATUS_UNDERWEIGHT   = "Underweight";
const string STATUS_NORMAL        = "Normal";
const string STATUS_OVERWEIGHT    = "Overweight";
const string STATUS_OBESE         = "Obese";

int main()
{

  int weightPoundsInput,
      heightInchesInput;

  float weightKilos,
        heightMeters,
        BMIResult;

  string weightStatus;

  cout<<"Please enter weight (in pounds): ";
  cin>>weightPoundsInput;

  cout<<"Please enter height (in inches): ";
  cin>>heightInchesInput;

  weightKilos = weightPoundsInput * KILOS_PER_POUND;
  heightMeters = heightInchesInput * METERS_PER_INCH;

  BMIResult = weightKilos / pow(heightMeters, 2);

  if (BMIResult < 18.5) {
    weightStatus = STATUS_UNDERWEIGHT;
  } else if (BMIResult >= 18.5 && BMIResult < 25) {
    weightStatus = STATUS_NORMAL;
  } else if (BMIResult >= 25 && BMIResult < 30) {
    weightStatus = STATUS_OVERWEIGHT;
  } else {
    weightStatus = STATUS_OBESE;
  }

  cout<<"The weight status is: "<<weightStatus<<endl;

  return 0;
}
