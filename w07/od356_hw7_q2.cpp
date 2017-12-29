#include <iostream>
using namespace std;

int sumOfSquares(int arr[], int arrSize);
bool isSorted(int arr[], int arrSize);
void printArr(int arr[], int arrSize);

const int ARRAY_1_SIZE = 4;
const int ARRAY_2_SIZE = 4;
const int ARRAY_3_SIZE = 8;

int main() {
  int a1[ARRAY_1_SIZE] = { 2, -1, 3, 10 };
  int a2[ARRAY_2_SIZE] = { 10, -11, 13, 14 };
  int a3[ARRAY_3_SIZE] = { -5, -3, -1, 0, 1, 3, 5, 7 };

  cout << "section a: " << endl;
  cout << "sumOfSquares(";
  printArr(a1, ARRAY_1_SIZE);
  cout << ", "; 
  cout << ARRAY_1_SIZE << ") -> ";
  cout << sumOfSquares(a1, ARRAY_1_SIZE) << endl;

  cout << endl << "section b: " << endl;
  cout << "isSorted(";
  printArr(a2, ARRAY_2_SIZE);
  cout << ", "; 
  cout << ARRAY_2_SIZE << ") -> ";
  cout << isSorted(a2, ARRAY_2_SIZE) << endl;
  cout << "isSorted(";
  printArr(a3, ARRAY_3_SIZE);
  cout << ", "; 
  cout << ARRAY_3_SIZE << ") -> ";
  cout << isSorted(a3, ARRAY_3_SIZE) << endl;

  return 0;
}

/**
 * Prints values in an array to standard out.
 * 
 * @param   int arr[]     - the array of integers
 * @param   int arrSize   - the size of the array
 *
 */

void printArr(int arr[], int arrSize) {
  cout << '[';
  for (int i = 0; i < arrSize; i++) {
    cout<<arr[i];
    if (i < arrSize - 1)
      cout<<", ";
  }
  cout << ']';
}

int sumOfSquares(int arr[], int arrSize) {
  // Base case: array of size 0 or less adds no more to sum
  if (arrSize <= 0) {
    return 0;
  // n - 1 case: multiply product of last values in array and add them
  // to the result of a recursive call to an array 1 element smaller.
  // eventually, an array of size 0 or less will end the recursion
  // and return the correct sum.
  } else {
    return arr[arrSize - 1] * arr[arrSize - 1] + sumOfSquares(arr, arrSize - 1);
  }
}

bool isSorted(int arr[], int arrSize) {
  // Base case: an array of size 1 or zero is considered sorted
  if (arrSize <= 1) {
    return true;
  } else {
  // Otherwise, check if last element is greater than penultimate element.
    return (arr[arrSize - 1] > arr[arrSize - 2]) && isSorted(arr, arrSize - 1);
  }
}
