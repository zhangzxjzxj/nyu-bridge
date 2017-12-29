#include <iostream>
using namespace std;

int MAX_ARRAY_SIZE = 20;

int minInArray(int arr[], int arrSize, int& outOccurences);
int indexOf(int num, int arr[], int outIndices[], int expectedOccurences);
void printArr(int arr[], int arrSize);

int main() {
  int integers[MAX_ARRAY_SIZE];
  int currentVal,                 // keeps track of running value
      outOccurences;              // holds the total occurences of value

  // Get numbers from user
  cout<<"Please enter 20 integers separated by a space: "<<endl;
  for (int counter = 0; counter < MAX_ARRAY_SIZE; counter++) {
    cin>>currentVal;
    integers[counter] = currentVal;
  }

  // Initialize number of occurences
  outOccurences = 0;
  // Get min value
  int minOf = minInArray(integers, MAX_ARRAY_SIZE, outOccurences);

  // Find indices of min value
  int outIndices[outOccurences];
  indexOf(minOf, integers, outIndices, outOccurences);
  
  // Print output
  cout<<"The minimum value is "<<minOf<<", and it is located in the following indices: ";
  printArr(outIndices, outOccurences);
  cout<<endl;

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
  for (int i = 0; i < arrSize; i++) {
    cout<<arr[i];
    if (i < arrSize)
      cout<<' ';
  }
}

/**
 *
 * Finds minimum value in an array of integers.
 *
 * @param   int[] arr           - an array of integers
 * @param   int arrSize         - size of the array
 * @param   int& outOccurences  - output param pointer
 *
 * @returns int                 - the minimum value in an array
 * @returns int outOccurences   - the number of occurences
 *
 */

int minInArray(int arr[], int arrSize, int& outOccurences) {
  int currentMin = arr[0];  // initialize currentMin to whatever is in the first position of the array. 
  int counter = 0;          // initialize counter to 0

  // Iterate over the array looking for min
  for (int i = 0; i < arrSize; i++) {
    // When current value is the same as currentMin increment the occurences counter
    if (arr[i] == currentMin) {
      counter++;
    // When the current value is less than the currentMin, set it to the new min and re-initialize occurences counter
    } else if (arr[i] < currentMin) {
      currentMin = arr[i];
      counter = 1;
    }
    cout<<endl;
  }

  outOccurences = counter;
  return currentMin;
}

/**
 *
 * Finds index of a value in an array of integers
 *
 * @param   int num                   - a number
 * @param   int arr[]                 - an array of numbers
 * @param   int outIndices[]          - an array of indices
 * @param   int expectedOccurences    - expected number of occurences
 *
 *
 * @returns int                       - the index of a number in an array
 * @returns outIndices[]              - an array of indices indicating all the locations where that number occurs in arr[].
 *
 */

int indexOf(int num, int arr[], int outIndices[], int expectedOccurences) {
  int index = 0;
  int counter = 0;

  while (counter < expectedOccurences) {
    if (num == arr[index]) {
      outIndices[counter] = index;
      counter++;
    }
    index++;
  }

  return outIndices[0];
}
