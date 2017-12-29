#include <iostream>
using namespace std;

int main() {
  string firstNameInput,
      middleNameInput,
      lastNameInput;

  cout<<"Please enter your first name, middle name and last name:"<<endl;

  cin>>firstNameInput>>middleNameInput>>lastNameInput;

  cout<<lastNameInput<<", "<<firstNameInput<<' '<<middleNameInput[0]<<'.'<<endl;

  return 0;
}

