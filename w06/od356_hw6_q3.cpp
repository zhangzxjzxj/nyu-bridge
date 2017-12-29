#include <iostream>
#include <vector>
using namespace std;

// Type Annotations
void emptyArray (int* arr, int arrSize);
void setGradeCounts (vector<int>& grades, int* gradeCounts);
void printGradeCounts (int* gradeCounts, int maxGrade);
void getGradesFromUser(vector<int>& grades, int& maxGrade);

int main() {
  int maxGrade;

  vector<int> grades;

  getGradesFromUser(grades, maxGrade);

  int* gradeCounts = new int[maxGrade + 1];

  emptyArray(gradeCounts, maxGrade + 1);

  setGradeCounts(grades, gradeCounts);

  printGradeCounts(gradeCounts, maxGrade);

  return 0;
}

/**
 *
 * Receives grades as input from user until -1 is entered.
 *
 */

void getGradesFromUser(vector<int>& grades, int& maxGrade) {
  int currentGrade;
  cout << "Please enter each student's grade (enter -1 to finish): " << endl;
  cin>>currentGrade;
  maxGrade = currentGrade;
  while (currentGrade != -1) {
    grades.push_back(currentGrade);
    if (currentGrade >= maxGrade)
      maxGrade = currentGrade;
    cin >> currentGrade;
  }
}

/**
 *
 * Sets the counts of each unique grade in a another array.
 *
 */

void setGradeCounts (vector<int>& grades, int* gradeCounts) {
  for (int i = 0; i < grades.size(); i++) {
    gradeCounts[grades[i]] += 1;
  }
}

/**
 *
 * Prints the counts of each grade
 *
 */

void printGradeCounts (int* gradeCounts, int maxGrade) {
  for (int i = 0; i <= maxGrade; i++) {
    if (gradeCounts[i] > 0)
      cout << "The number of "<< i << "'s: " << gradeCounts[i] << endl;
  }
  cout << endl;
}

/**
 *
 * Sets all positions of an array to 0
 *
 */

void emptyArray (int* arr, int arrSize) {
  for (int i = 0; i < arrSize; i++) {
    arr[i] = 0;
  }
}
