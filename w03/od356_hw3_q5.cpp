#include <iostream>
using namespace std;

// setting this as a global constant for easy extensibility (i.e. to make these $ or & or whatever with only one line changed)
const char PIXEL_CHAR = '*';
const char SPACE_CHAR = ' ';

int main() {
  int n,        // holds user input
      c1,       // outer loop counter
      c2,       // inner loop counter
      pixels;   // number of pixels to draw in each line 

  string currentLine;   // holds characters to draw in the current line

  cout<<"Please enter a positive integer: ";
  cin>>n;

  // each iteration draws one line
  for (c1 = n; c1 >= (-1 * n); c1--) {
    // when c1 is 0 there is no line to draw
    if (c1 != 0) {
      // initializes the current line as an empty string on each iteration
      currentLine = "";
      if (c1 < 0)
        pixels = c1 * -1;
      else
        pixels = c1;

      // add spaces
      for (c2 = (n - (pixels)); c2 > 0; c2--) {
        currentLine += SPACE_CHAR;
      }

      // add asterisks
      for (c2 = ((2 * pixels) - 1); c2 > 0; c2--) {
        currentLine += PIXEL_CHAR;
      }

      // print the current line string
      cout<<currentLine<<endl;
    }
  }

  return 0;
}
