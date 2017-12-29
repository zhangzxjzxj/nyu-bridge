#include <iostream>
using namespace std;

void insertionSort(int a[], int aSize);
void swap(int a[], int i1, int i2);
void printArr(int arr[], int arrSize);

int main() {
  int a1[6] = {3, 4, 0, -3, 11, 1};
  int a2[6] = {20, 10, 3, 0, -3, -100};

  // Call functions with test arrays and print results
  cout << "1. insertionSort(";
  printArr(a1, 6);
  cout << ", 6) -> ";
  insertionSort(a1, 6);
  printArr(a1, 6);
  cout << endl;

  cout << "2. insertionSort(";
  printArr(a2, 6);
  cout << ", 6) -> ";
  insertionSort(a2, 6);
  printArr(a2, 6);
  cout << endl;

  return 0;
}

void swap(int a[], int i1, int i2) {
  int tmp = a[i1];
  a[i1] = a[i2];
  a[i2] = tmp;
}

void insertionSort(int a[], int aSize) {
  int i, j;
  for (i = 0; i < aSize; i++) {
    j = i;
    while(j > 0 && a[j] < a[j - 1]) {
      swap(a, j, j - 1);
      j--;
    }
  }
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
