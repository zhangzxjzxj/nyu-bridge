#include <iostream>
using namespace std;

const char SPACE_CHAR = ' '; // made this a const for easy configuration/changing

// Function type annotations
void printShiftedTriangle(int n, int m, char symbol);
void printPineTree(int n, char symbol);

int main (){
  char symbol;         // holds the symbol character from the user input
  int numTriangles;   // holds the number of triangles in the tree

  cout<<"Please enter the number of triangles in the tree: "<<endl;
  cin>>numTriangles;
  cout<<"Please enter the character to fill each triangle with: "<<endl;
  cin>>symbol;

  if (numTriangles > 0)
    printPineTree(numTriangles, symbol);
  
  return 0;
}

void printShiftedTriangle(int n, int m, char symbol) {
  int c1,       // outer loop counter
      c2,       // inner loop counter
      spaces,   // number of leading spaces
      symbols;   // number of symbols to draw in each line 

  string currentLine;   // holds characters to draw in the current line

  // each iteration draws one line
  for (c1 = 1; c1 < n; c1++) {
    // initializes the current line as an empty string on each iteration
    currentLine = "";

    spaces = n - c1 + m;
    symbols = (c1 * 2) - 1;

    // add spaces
    for (c2 = 1; c2 < spaces; c2++) {
      currentLine += SPACE_CHAR;
    }

    // add symbols
    for (c2 = 1; c2 <= symbols; c2++) {
      currentLine += symbol;
    }

    // print the current line string
    cout<<currentLine<<endl;
  }
}

void printPineTree(int n, char symbol) {
  for (int i = 3; i <= (n + 2); i++) {
    printShiftedTriangle(i, (n + 2) - i, symbol);
  }
}
