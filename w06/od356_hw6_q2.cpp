#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void insert(int*& arr, int& arrSize, int newVal);
void initSortedArr(int* arr, int arrSize);
void printArr(int arr[], int arrSize);

int main() {
  int size,
      newNumber;

  cout<<"Please enter starting array size:"<<endl;
  cin>>size;

  srand(time(0));

  int* arr = new int[size];

  initSortedArr(arr, size);

  cout<<"Starting array: "<<endl;

  printArr(arr, size);

  cout<<"Please enter a number to add (or -1 to quit): "<<endl;
  cin>>newNumber;

  while (newNumber != -1) {
    insert(arr, size, newNumber);

    cout<<"Inserted '"<<newNumber<<"' into array:"<<endl;
    printArr(arr, size);

    cout<<"Please enter a number to add (or -1 to quit): "<<endl;
    cin>>newNumber;
  }

  return 0;
}

void insert(int*& arr, int& arrSize, int newVal) {
  int newSize = arrSize + 1;
  int* tmp = new int[newSize];
  bool shift = 0;
  for (int i = 0; i < newSize; i++) {
    // When 
    if (arr[i] > newVal && shift == 0) {
        tmp[i] = newVal;
        shift = 1;
    } else {
      tmp[i] = arr[i - shift];
    }
  }
  delete [] arr;
  arrSize = newSize;
  arr = tmp;
}

void initSortedArr(int* arr, int arrSize) {
  for (int i = 1; i < arrSize; i++) {
    arr[i] = i * 5;
  }
}

void printArr(int arr[], int arrSize) {
  cout<<"[";
  for (int i = 0; i < arrSize; i++) {
    cout<<arr[i];
    if (i < arrSize - 1)
      cout<<", ";
  }
  cout<<"]"<<endl;
}
