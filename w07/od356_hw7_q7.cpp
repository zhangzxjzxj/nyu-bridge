#include <iostream>
using namespace std;

int findChange(int arr01[], int arr01Size);
void printArr(int arr[], int arrSize);

int main() {
  int a1[10] = {0,0,0,1,1,1,1,1,1,1};
  int a2[10] = {0,0,0,0,0,0,0,0,1,1};
  int a3[8] = {0,0,0,0,0,1,1,1};

  // Call functions with test arrays and print results
  cout << "1. findChange(";
  printArr(a1, 10);
  cout << ", 10) -> ";
  cout << findChange(a1, 10) << endl;

  cout << "2. findChange(";
  printArr(a2, 10);
  cout << ", 10) -> ";
  cout << findChange(a2, 10) << endl;

  cout << "3. findChange(";
  printArr(a3, 8);
  cout << ", 8) -> ";
  cout << findChange(a3, 8) << endl;

  return 0;
}

int findChange(int arr01[], int arr01Size) {
  int mid, low, high, ind;
  bool found = false;

  low = 0;
  high = arr01Size - 1;

  while((found == false) && (low + high >= 2)) {
    mid = (low + high) / 2;
    // Found
    if ((arr01[mid] == 1) && arr01[mid - 1] == 0) {
      found = true;
      ind = mid;
    // Go lower
    } else if (arr01[mid] == 1) {
      high = mid - 1;
    // Go higher
    } else {
      low = mid + 1;
    }
  }

  if (found == true)
    return ind;
  else
    return -1;
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
