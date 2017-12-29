#include <iostream>
#include <cmath>
using namespace std;

const char STAR = '*';
const char NOTCH = '-';

void printTriangle(int n);
void printOppositeTriangles(int n);
void printRuler(int n);

void printInverseTriangle(int n);
void printPixels(int n, bool inverted, char c);
void printPixelRow(int n, char c);

int main() {
  cout << "section a: " << endl;
  printTriangle(4);

  cout << endl << "section b: " << endl;
  printOppositeTriangles(4);

  cout << endl << "section c: " << endl;
  printRuler(4);

  return 0;
}


/**
 *
 * Prints a row of pixel of size N pixels
 *
 */

void printPixelRow(int n, char c) {
  for (int i = n; i > 0; i--) {
    cout << c;
  }
  cout << endl;
}

/**
 *
 * Prints a triangle of stars.
 *
 * (Wraps the more general star printer function)
 *
 */

void printTriangle(int n) {
  printPixels(n, false, STAR);
}

/**
 *
 * Prints an inverted triangle of stars.
 *
 * (Wraps the more general star printer function)
 *
 */

void printInverseTriangle(int n) {
  printPixels(n, true, STAR);
}

/**
 *
 * Helper function that delegates star printing.
 * The added boolean parameter allows for less
 * code repetition.
 *
 */

void printPixels(int n, bool inverted, char c) {
  // When n is < or == to 0, the base
  // case is just to stop printing stars.

  // When n > 0 print the star row, before
  // or after the recursive call depending
  // on whether to invert or not
  if (n > 0) {
    if (inverted)
      printPixelRow(n, c);
    printPixels(n - 1, inverted, c);
    if (!inverted)
      printPixelRow(n, c);
  }
}

void printOppositeTriangles(int n) {
  printInverseTriangle(n);
  printTriangle(n);
}

/**
 * 
 * Prints a series of lines of length 2^n - 1.
 *
 */

void printRuler(int n) {
  // Base case: print a single notch and end line
  if (n <= 1) {
    cout << NOTCH << endl;
  } else {
    // Recursively print a ruler of size n - 1
    printRuler(n - 1);
    // Print a ruler of size n
    printPixelRow(n, NOTCH);
    // Recursively print another ruler of size n - 1
    printRuler(n - 1);
  }
  return;
}
