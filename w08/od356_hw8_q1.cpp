#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
using namespace std;

// Constants
const int MAX_CHECK_LIST_SIZE = 100;
const bool CASHED = true;
const bool UNCASHED = false;
const string BANK_NAME = "Terminal Bank, Inc.";
const string DEFAULT_CHECK_LIST_LABEL = "CHECKS";
const string DIVIDOR = "---------------------\n";
const string HEAVY_DIVIDOR = "####################\n";

// Money prototype
class Money {
  public:
    // Overloads + operator to support additions
    friend Money operator +(const Money& amount1, const Money& amount2);
    // Overloads - operator to support subtractions
    friend Money operator -(const Money& amount1, const Money& amount2);
    // Overloads - operator to support negations
    friend Money operator -(const Money& amount);
    // Overloads == operator to support equality comparisons
    friend bool operator ==(const Money& amount1, const Money& amount2);
    // Overloads < operator to support < comparisons
    friend bool operator <(const Money& amount1, const Money& amount2);
    // Overloads >= operator to support >= comparisons
    friend bool operator >=(const Money& amount1, const Money& amount2);
    // Constructor for dollars and cents
    Money(long dollars, int cents);
    // Constructor for only dollars
    Money(long dollars);
    // Null/default value constructor
    Money();
    // value getter
    double get_value() const { return all_cents; };
    // Overloads >> to support reading from input stream
    friend istream& operator >>(istream& ins, Money& amount);
    // Overloads << to support writing to output stream
    friend ostream& operator <<(ostream& outs, const Money& amount);
  private:
    // Data holder
    long all_cents;
};

// Check prototype
class Check {
  public:
    // Constructor for new check with all pieces provided.
    Check(int newNumber, Money& newAmount, bool newCashedStatus);
    // Constructor for new check with default values provided
    Check(): number(0), amount(Money(0)), cashedStatus(false) {};
    // Getter for the check number
    int getNumber();
    // Getter for the check status (cashed or not cashed)
    bool getStatus();
    // Getter for the check amount as Money type.
    Money& getAmount();
    // Overloads << to support writing to output stream
    friend ostream& operator <<(ostream& outs, const Check& check);
    // Overloads >> to support reading from input stream
    friend istream& operator >>(istream& ins, Check& check);
  private:
    // Data holder for check number
    int number;
    // Data holder for check amount as Money type
    Money amount;
    // Data holder for check cashed status (true or false)
    bool cashedStatus;
};

// CheckList prototype
class CheckList {
  public:
    // Constructor for an empty CheckList with a default label
    CheckList(): label(DEFAULT_CHECK_LIST_LABEL) {};
    // Constructor for an empty CheckList with a specified label
    CheckList(string newLabel){ size = 0; label = newLabel; };
    // Constructor for an empty CheckList from a file and with a specified label
    CheckList(string filename, string label);
    // Adds a check to the CheckList
    void addCheck(Check& check);
    // Returns true if the CheckList is full
    bool full() const;
    // Uses insertion sort to sort the CheckList without mutations, cloning etc
    void sort();
    // Getter that sums all cashed checks and returns a Money amount balance
    Money getBalance();
    // Prints all checks in CheckList
    void outputChecks(ostream& outs) const;
    // Prints all checks in CheckList with a given checkStatus
    void outputChecksByStatus(ostream& outs, bool checkStatus) const;
    // Overloads the << operator to print check list
    friend ostream& operator <<(ostream& outs, const CheckList& checkObj);
  private:
    // Swaps check positions
    void swap(int i1, int i2);
    // An array that holds all check data
    Check list[MAX_CHECK_LIST_SIZE];
    // Current size of the check array
    int size;
    // A label for the CheckList (for example "CHECKS" or "DEPOSITS") to be printed above list
    string label;
};

// Utility functions
int digit_to_int(char c);

/**
 * 
 * Main function
 * 
 */
int main() {
  int depositCounter = 1;
  string userInputFilename;
  Money nullDeposit(0);
  Money currentDeposit(0,1);
  Check currentCheck;
  Money originalBalance(0);
  Money balance(0);
  CheckList deposits("DEPOSITS");

  cout << "Please enter the filename of the check data: " << endl;
  cin >> userInputFilename;
  CheckList checkbook(userInputFilename, DEFAULT_CHECK_LIST_LABEL);

  cout << HEAVY_DIVIDOR;
  cout << BANK_NAME << endl;
  cout << HEAVY_DIVIDOR;

  originalBalance = checkbook.getBalance();
  balance = balance + originalBalance;
  
  while (!(currentDeposit == nullDeposit) && !cin.fail()) {
    checkbook.outputChecksByStatus(cout, CASHED);
    checkbook.outputChecksByStatus(cout, UNCASHED);
    deposits.outputChecks(cout);
    cout << DIVIDOR;
    cout << "BALANCES:\t" << endl << endl;
    cout << "CashedChecks:\t" << checkbook.getBalance() << endl;
    cout << "TotalDeposits:\t" << -deposits.getBalance() << endl;
    cout << "Old Balance:\t" << originalBalance << endl;
    cout << "New Balance:\t" << balance << endl;
    cout << "Difference:\t" << balance - originalBalance << endl;
    cout << DIVIDOR;
    cout << endl;
    cout << "PLEASE ENTER A DEPOSIT AMOUNT (in the format $DD.CC or deposit $0.00 to quit):" << endl;
    cin >> currentDeposit;
    currentCheck = Check(depositCounter, currentDeposit, true);
    deposits.addCheck(currentCheck);
    balance = balance + currentDeposit;
    depositCounter++;
  }
  return 0;
}

/**
 *
 * Utility function implementations
 *
 */

int digit_to_int(char c) {
  return (static_cast<int>(c) - static_cast<int>('0'));
}

/**
 *
 * CheckList implementation
 *
 */

CheckList::CheckList(string filename, string newLabel) {
  fstream fs;
  bool isEOF;
  int counter = 0;
  size = 0;
  label = newLabel;
  CheckList checksSinceLastBalance;
  Check check;

  fs.open(filename);

  if (fs.fail()) {
    cout << "Error: could not open file: '" << filename << "'" << endl;
    exit(1);
  }

  isEOF = fs.eof();

  while (!isEOF || counter > MAX_CHECK_LIST_SIZE) {
    fs >> check;
    isEOF = fs.eof();
    if (!isEOF) {
      addCheck(check);
    }
    counter++;
  }

  fs.close();
};

void CheckList::addCheck(Check& check) {
  if (full()) {
    cout << "Error: adding to a full CheckList." << endl;
    exit(1);
  } else {
    list[size] = check;
    size = size + 1;
  }
  // Sort the list after adding a new check to keep it auto-sorted
  sort();
}

bool CheckList::full() const {
  return (size == MAX_CHECK_LIST_SIZE);
}

void CheckList::swap(int i1, int i2) {
  Check tmp = list[i1];
  list[i1] = list[i2];
  list[i2] = tmp;
};

void CheckList::sort() {
  int i, j;
  for (i = 0; i < size; i++) {
    j = i;
    while(j > 0 && list[j].getNumber() < list[j - 1].getNumber()) {
      swap(j, j - 1);
      j--;
    }
  }
}

Money CheckList::getBalance() {
  Money balance(0);
  for (int i = 0; i < size; i++)
    if (list[i].getStatus())
      balance = balance - list[i].getAmount();
  return balance;
}

void CheckList::outputChecks(ostream& outs) const {
  Check currentCheck;
  outs << DIVIDOR;
  if (size <= 0)
    outs << "NO " << label << endl;
  else {
    outs << label << ": " << endl << endl;
    for (int i = 0; i < size; i++) {
      currentCheck = list[i];
      outs << currentCheck << endl;
    }
  }
  outs << DIVIDOR;
}

void CheckList::outputChecksByStatus(ostream& outs, bool checkStatus) const {
  Check currentCheck;
  string statusString = (checkStatus ? "CASHED" : "UNCASHED");
  outs << DIVIDOR;
  outs << statusString << " " << label << ": " << endl << endl;
  for (int i = 0; i < size; i++) {
    currentCheck = list[i];
    if (currentCheck.getStatus() == checkStatus)
      outs << currentCheck << endl;
  }
  outs << DIVIDOR;
}

ostream& operator <<(ostream& outs, const CheckList& checks) {
  checks.outputChecks(outs);
  return outs;
}

/**
 *
 * Money implementation
 *
 */

Money::Money(long dollars, int cents) {
  // If one is negative and one is positive...
  if (dollars * cents < 0) {
    cout << "Error: Illegal values for dollars and cents.\n";
    exit(1);
  } else {
    all_cents = dollars * 100 + cents;
  }
}

Money::Money(long dollars) : all_cents(dollars * 100) {};

Money::Money() : all_cents(0) {};

istream& operator>>(istream& ins, Money& amount) {
  char one_char, decimal_point, digit1, digit2;

  long dollars;
  int cents;
  bool negative;
  long all_cents;

  ins >> one_char;

  if (one_char == '-') {
    negative = true;
    ins >> one_char; // read $
  } else {
    negative = false; // if input is legal, then one_char == '$'
  }

  ins >> dollars >> decimal_point >> digit1 >> digit2;

  // Soft fail
  if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2)) {
    return ins;
  }

  cents = (digit_to_int(digit1) * 10) + digit_to_int(digit2);

  all_cents = (dollars * 100) + cents;
  if (negative)
    all_cents = -all_cents;

  amount.all_cents = all_cents;
  return ins;
};

ostream& operator<<(ostream& outs, const Money& amount) {
  long positive_cents, dollars, cents;
  long all_cents = amount.get_value();
  positive_cents = labs(all_cents);
  dollars = positive_cents / 100;
  cents = positive_cents % 100;

  if (all_cents < 0)
    outs << "-$" << dollars << '.';
  else
    outs << "$" << dollars << '.';

  if (cents < 10)
    outs << '0';
  return outs << cents;
}

Money operator +(const Money& amount1, const Money& amount2) {
  Money temp;
  temp.all_cents = amount1.all_cents + amount2.all_cents;
  return temp;
}

Money operator -(const Money& amount1, const Money& amount2) {
  Money temp;
  temp.all_cents = amount1.all_cents - amount2.all_cents;
  return temp;
}

Money operator -(const Money& amount) {
  Money temp;
  temp.all_cents = -amount.all_cents;
  return temp;
}

bool operator ==(const Money& amount1, const Money& amount2) {
  return amount1.all_cents == amount2.all_cents;
}

bool operator <(const Money& amount1, const Money& amount2) {
  return amount1.all_cents < amount2.all_cents;
}

bool operator >=(const Money& amount1, const Money& amount2) {
  return amount1.all_cents >= amount2.all_cents;
}

/**
 *
 * Check implementation
 *
 */

Check::Check(int newNumber, Money& newAmount, bool newCashedStatus) {
  number = newNumber;
  amount = newAmount;
  cashedStatus = newCashedStatus;
};

int Check::getNumber() {
  return number;
}

bool Check::getStatus() {
  return cashedStatus;
}

Money& Check::getAmount() {
  return amount;
}


ostream& operator<<(ostream& outs, const Check& check) {
  return outs << "#" << check.number << "\t" << check.amount;
}

istream& operator>>(istream& ins, Check& check) {
  int number;
  Money amount;
  bool newCashedStatus;
  ins >> number >> amount >> newCashedStatus;
  check.number = number;
  check.amount = amount;
  check.cashedStatus = newCashedStatus;
  return ins;
};
