#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TOTAL_GUESSES = 5;

int main() {
  int targetNumber,
      currentMin,
      currentMax,
      currentGuess,
      numGuesses;

  srand(time(0));

  currentMin = 1;
  currentMax = 100;
  numGuesses = TOTAL_GUESSES;
  targetNumber = (rand() % 100) + 1;


  cout<<"I thought of a number between "<<currentMin<<" and "<<currentMax<<"! Try to guess it."<<endl;

  while (numGuesses > 0) {
    cout<<"Range: ["<<currentMin<<","<<currentMax<<"], Number of guesses left: "<<numGuesses<<endl;
    cout<<"Your guess: ";
    cin>>currentGuess;
    if (currentGuess > targetNumber) {
      cout<<"Wrong! My number is smaller."<<endl;
      currentMax = currentGuess;
      numGuesses--;
    } else if (currentGuess < targetNumber) {
      cout<<"Wrong! My number is bigger."<<endl;
      currentMin = currentGuess;
      numGuesses--;
    } else {
      cout<<"Congrats! You guessed my number in "<<(TOTAL_GUESSES - numGuesses)<<" guesses."<<endl;
      return 0;
    }
  }

  cout<<"Out of guesses! My number is "<<targetNumber<<endl;

  return 0;
}
