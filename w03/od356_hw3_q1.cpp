#include <iostream>
using namespace std;

int main() {
  int n;
  int counter = 1;

  cout<<"Please enter a positive integer: ";
  cin>>n;

  cout<<"section a"<<endl;
  while (counter <= n) {
    cout<<(2 * counter)<<endl;
    counter++;
  }

  cout<<"section b"<<endl;
  for (int counter2 = 1; counter2 <= n; counter2++) {
    cout<<(2 * counter2)<<endl;
  }

  return 0;
}
