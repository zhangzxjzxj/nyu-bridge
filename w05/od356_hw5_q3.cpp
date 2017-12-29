#include <iostream>
using namespace std;

// Core functions
void reverseArray(int arr[], int arrSize);
void removeOdd(int arr[], int& arrSize);
void splitParity(int arr[], int arrSize);
void printArray(int arr[], int arrSize);

// Helper functions
void swap(int arr[], int leftIdx, int rightIdx);
bool isEven(int n);

int main() {
  int arr1[10] = {9, 2, 14, 12, -3};
  int arr1Size = 5;
  int arr2[10] = {21, 12, 6, 7, 14};
  int arr2Size = 5;
  int arr3[10] = {3, 6, 4, 1, 12};
  int arr3Size = 5;

  reverseArray(arr1, arr1Size);
  printArray(arr1, arr1Size);

  removeOdd(arr2, arr2Size);
  printArray(arr2, arr2Size);

  splitParity(arr3, arr3Size);
  printArray(arr3, arr3Size);

  return 0;
}

/**
 *
 * Swaps values at two different indexes in the array.
 *
 * @param   int arr[]       - an array of integers
 * @param   int leftIdx     - an index in the array
 * @param   int rightIdx    - another index in the array
 *
 */

void swap(int arr[], int leftIdx, int rightIdx) {
  if (leftIdx == rightIdx) return;  // Nothing to be done here
  int tmp;
  tmp = arr[leftIdx];
  arr[leftIdx] = arr[rightIdx];
  arr[rightIdx] = tmp;
}

/**
 * 
 * Determines if a number is even
 *
 * @param   int n         - a number
 *
 */

bool isEven(int n) {
  return n % 2 == 0; 
}

void splitParity(int arr[], int arrSize) {
  int i = 0;
  int j = arrSize - 1;
  while (i < j) {
    if (!isEven(arr[j]) && isEven(arr[j])) {
      swap(arr, i, j);
    }
    i++;
    j--;
  }
}

void removeOdd(int arr[], int& arrSize) {
  int i,                    // counter 1
      j,                    // counter 2
      oddNumbersFound;      // holds the total odd numbers found in array

  // Initialize counters, etc
  i = 0;
  j = 0;
  oddNumbersFound = 0; 

  // Loop through the array until counter j reaches the end, checking values at positions i and j along the way.
  while (j < arrSize) {
    // When the ith value is even, keep moving.  Nothing to see here.
    if (isEven(arr[i])) {
      i++;
    // When the ith value is odd
    } else {
      // When the jth value is even
      if (isEven(arr[j])) {
        swap(arr, i, j);    // Swap values at positions i and j 
        i = j;              // Synchronize counters
      // When the jth value is odd
      } else {
        oddNumbersFound++;  // Increment the number of odd numbers found 
      }
      // Continue processing next part of list
    }
    j++;
  }

  // Update arrSize parameter to the new list size 
  arrSize -= oddNumbersFound;
}

void reverseArray(int arr[], int arrSize) {
  int i = 0;
  int j = arrSize - 1;
  int tmp;

  // Loop through the array, item by item from outside in
  while (j > 0) {
    swap(arr, i, j);    // swaps outermost position with innermost position
    i++;                // increments i
    j--;                // decrements j
  }
}

void printArray(int arr[], int arrSize){
  int i;
  for (i = 0; i < arrSize; i++) {
    cout<<arr[i]<<' ';
  }
  cout<<endl;
}
