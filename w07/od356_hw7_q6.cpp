#include <iostream>
#include <cmath>
using namespace std;

int binarySearch(int arr[], int arrSize, int val);
void printArr(int arr[], int arrSize);

int main() {
  int a1[6] = { 1, 3, 5, 7, 7, 11 };
  int a2[8] = { -5, -3, -1, 0, 1, 3, 5, 7 };

  // Call functions with test arrays and print results
  cout << "1. binarySearch(";
  printArr(a1, 6);
  cout << ", 6, 11) -> ";
  cout << binarySearch(a1, 6, 11) << endl;

  cout << "2. binarySearch(";
  printArr(a2, 8);
  cout << ", 8, 5) -> ";
  cout << binarySearch(a2, 8, 5) << endl;

  return 0;
}

int binarySearch(int arr[], int arrSize, int val) {
  int mid, low, high, ind;
  low = 0;
  high = arrSize - 1;
  bool found = false;
  while ((found == false) && (low <= high)) {
    mid = (low + high) / 2;
    if (arr[mid] == val) {
      found = true;
      ind = mid;
    } else if (val < arr[mid]) {
      high = mid - 1;
    // Val is greater than mid val
    } else {
      low = mid + 1;
    }
  }

  if (found == true)
    return ind;
  else
    return -1;
};

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
