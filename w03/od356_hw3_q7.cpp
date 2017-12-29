#include <iostream>
using namespace std;

int main() {
  int numberInput,      // holds number input by user
      row,              // holds the current matrix row number
      col,              // holds the current matrix col number
      currentProduct;   // holds the product to print in each cell of the matrix

  cout<<"Please enter a positive integer: "<<endl;
  cin>>numberInput;

  for (row = 1; row <= numberInput; row++) {
    for (col = 1; col <= numberInput; col++) {
      currentProduct = row * col;
      cout<<currentProduct<<'\t';
    }
    cout<<endl;
  }

  return 0;
}
