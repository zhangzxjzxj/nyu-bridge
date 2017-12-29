#include <iostream>
using namespace std;

int bestCost(int board[], int low, int high);
void printArr(int arr[], int arrSize);

int main() {
  int BOARD_1[6] = { 0, 3, 80, 6, 57, 10 };
  int BOARD_2[11] = { 0, 1, 1, 10, 20, 10, 9, 1, 2, 1, 3 };
  int res1, res2;

  cout << "bestCost(";
  res1 = bestCost(BOARD_1, 0, 5);
  printArr(BOARD_1, 6);
  cout << ") -> " << res1 << endl;

  cout << "bestCost(";
  res2 = bestCost(BOARD_2, 0, 10);
  printArr(BOARD_2, 11);
  cout << ") -> " << res2 << endl;

  return 0;
}

int bestCost(int board[], int low, int high) {
  int result;
  if (low == high) {
    // When the last element is reached, there is only one cost...
    return board[low];
  } else if (low == (high - 1)) {
    // Otherwise, when given the last two elements choose lowest
    if (board[low] > board[high])
      return board[high];
    else
      return board[low];
  } else {
    // In all other cases, add the value of the next
    // or next element to the result of a recursive 
    // call on either the next element or the next next 
    // element, depending on which of the two had the 
    // lowest cost.

    int a = board[low];
    int b = board[low + 1];
    if (a <= b)
      return a + bestCost(board, low + 1, high);
    else
      return b + bestCost(board, low + 2, high);
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
