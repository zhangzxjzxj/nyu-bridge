#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class LList;

// LinkedList Node
template <class T>
class LListNode {
private:
    T data;
    LListNode<T>* next;
public:
    LListNode(T newdata = T(), LListNode<T>* newNext = nullptr):
        data(newdata), next(newNext) {};
    T getData() { return data; }
    void setData(T newdata) { data = newdata; };
    friend class LList<T>;
};

// LinkedList
template <class T>
class LList {
private:
    LListNode<T>* head;
    LListNode<T>* recursiveCopy(LListNode<T>* rhs);
public:
    LList() : head(nullptr) {};
    LList(const LList& rhs) :head(nullptr) { *this = rhs; };
    LList<T>& operator=(const LList<T>& rhs);
    ~LList() { clear(); };
    void insertAtHead(T newdata);
    T removeFromHead();
    bool isEmpty() const { return head == nullptr; };
    void clear();
    void insertAtEnd(T newdata);
    void insertAtPoint(LListNode<T>* ptr, T newdata);
    // getter for the head
    LListNode<T>* atHead();
    // getter for the tail or next node in the list
    LListNode<T>* nextOf(LListNode<T>* nodePtr);
    int size() const;
    // Prints items in the list
    ostream& print(ostream& outs, bool prettyPrint);
    friend ostream operator <<(ostream& outs, LList<T> list);
};

// Employee prototype
class Employee {
    public:
        // Constructors
        Employee(): id(-1), payRate(0.0), employeeName(nullptr), hoursWorked(0) {};
        Employee(int newId, double newPayRate, string newName, int newHoursWorked);
        // Overloaded operators
        friend ostream& operator <<(ostream& outs, Employee& employee);
        friend bool operator >=(const Employee& e1, const Employee& e2);
        friend bool operator <(const Employee& e1, const Employee& e2);
        // Getters and setters
        string& getEmployeeName() { return employeeName; };
        int getId() { return id; };
        double getPayRate() { return payRate; };
        int getHoursWorked() { return hoursWorked; };
        void setHoursWorked(int newVal) { hoursWorked = newVal; }
        // Calculates the total pay for the employee
        int getTotalPay() { return static_cast<int>(payRate * hoursWorked); }
    private:
        // Stores employee id
        int id;
        // Stores the number of hours worked
        int hoursWorked;
        // Stores the rate of pay for the employee
        double payRate;
        // Stores the employee name
        string employeeName;
};

// A class that encapsulates the employee list operations without
// modifying the abstract class for SLL and SLL Node.
class EmployeeList {
public:
    // Constructor/Destructor
    EmployeeList(): employees(nullptr) {};
    ~EmployeeList() { clearList(); }
    EmployeeList(string filename);
    // Iterates through the list and returns a pointer to the employee with matching id.
    Employee* findEmployeeById(int id);
    // Creates a new employee object and adds to the list
    void createEmployee(int newEmployeeId, double newEmployeePayRate, string newEmployeeName);
    // Prints all employees in the list
    ostream& printAll(ostream& outs);
    // Adds hours to a specific employee's hoursWorked
    void addHoursToEmployee(int employeeId, int hoursToAdd);
    // Reads hours from an input file
    void readEmployeeHoursFromFile(string filename);
    // Prints employees in descending order by pay.
    void printSortedEmployeeList();
private:
    // Insertion sort helper function
    void swap(int i1, int i2, Employee** arr);
    // Uses insertion sort to print a sorted list of the employees by pay amount
    void sort(Employee** arr, int size);
    // Creates an EmployeeList by reading from the filesystem
    void readEmployeeListFromFile(string filename);
    // Deletes the list from memory
    void clearList();
    // A SLL pointer to the employee data
    LList<Employee*>* employees;
};

// Main function for the program
int main() {
    string filename1, filename2;

    // Asks the user to input desired file names
    cout << "Enter the name of the file for the employee list: " << endl;
    cin >> filename1;
    cout << "Enter the name of the file for the employee hours: " << endl;
    cin >> filename2;

    // Creates a new employee list based on the data in the file
    EmployeeList* employees = new EmployeeList(filename1);
    // Updates all the hours for each employee based on file data.
    employees->readEmployeeHoursFromFile(filename2);

    // Prints employee pay in descending order based on amount
    cout << "*********Payroll Information********" << endl;
    employees->printSortedEmployeeList();
    cout << "*********End payroll**************" << endl;

    // Cleans up memory used by list and objects
    delete employees;
    return 0;
}

// Employee implementation
ostream& operator <<(ostream& outs, Employee& employee) {
    // Prints a human readable version of the employee object
    outs << "Employee(";
    outs << "id: " << employee.getId();
    outs << ", name: '" << employee.getEmployeeName() << "'";
    outs << ", payRate: " << employee.getPayRate();
    outs << ", hoursWorked: " << employee.getHoursWorked() << ")";
    return outs;
}

Employee::Employee(int newId, double newPayRate, string newName, int newHoursWorked) {
    id = newId;
    payRate = newPayRate;
    employeeName = newName;
    hoursWorked = newHoursWorked;
}

bool operator >=(Employee& e1, Employee e2) {
    return e1.getHoursWorked() >= e2.getHoursWorked();
}

bool operator <(Employee& e1, Employee e2) {
    return e1.getHoursWorked() < e2.getHoursWorked();
}

template <class T>
int LList<T>::size() const {
    LListNode<T>* temp = head;
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

template <class T>
void LList<T>::insertAtEnd(T newdata) {
    if (isEmpty()) {
        insertAtHead(newdata);
        return;
    }
    LListNode<T>* temp = new LListNode<T>(newdata);
    LListNode<T>* end = head;
    while (end->next != nullptr) {
        end = end->next;
    }
    end->next = temp;
}

template <class T>
LListNode<T>* LList<T>::recursiveCopy(LListNode<T>* rhs) {
    if (rhs == nullptr)
        return nullptr;
    return new LListNode<T>(rhs->data, recursiveCopy(rhs->next));
}

template <class T>
void LList<T>::insertAtHead(T newdata) {
    LListNode<T>* newNode = new LListNode<T>(newdata);
    LListNode<T>* temp = head;
    head = newNode;
    newNode->next = temp;
}

template <class T>
void LList<T>::insertAtPoint(LListNode<T>* ptr, T newdata) {
    ptr->setData(newdata);
}

template <class T>
LListNode<T>* LList<T>::atHead() {
    return head;
}

template <class T>
LListNode<T>* LList<T>::nextOf(LListNode<T>* nodePtr) {
    return nodePtr->next;
}

template <class T>
ostream& LList<T>::print(ostream& outs, bool prettyPrint) {
    LListNode<T>* currentNode = head;
    if (currentNode == nullptr) {
        outs << "[]";
        if (prettyPrint)
            outs << endl;
        return outs;
    }
    outs << "[";
    if (prettyPrint)
        outs << endl;
    while (currentNode != nullptr) {
        if (prettyPrint)
            outs << '\t';
        outs << *currentNode->data;
        currentNode = currentNode->next;
        if (currentNode != nullptr)
            outs << ", ";
        if (prettyPrint)
            outs << endl;
    }
    outs << "]";
    if (prettyPrint)
        outs << endl;
    return outs;
}

template <class T>
void LList<T>::clear() {
    if (isEmpty()) return;
    LListNode<T>* currentNode = head;
    LListNode<T>* nextNode = head;
    while (nextNode != nullptr) {
        nextNode = currentNode->next;
        if (nextNode != nullptr)
            delete currentNode;
        currentNode = nextNode;
    }
    // Set head to null
    head = nullptr;
}

template <class T>
ostream& operator <<(ostream& outs, LList<T> llist) {
    llist.print(outs, false);
    return outs;
}

// EmployeeList implementation
EmployeeList::EmployeeList(string filename) {
    // Creates an SLL from data in a file
    readEmployeeListFromFile(filename);
}

void EmployeeList::swap(int i1, int i2, Employee** arr) {
    Employee* tmp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
}

void EmployeeList::sort(Employee** arr, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        j = i;
        while (j > 0 && *arr[j] >= *arr[j - 1]) {
            swap(j, j - 1, arr);
            j--;
        }
    }
}

void EmployeeList::printSortedEmployeeList() {
    int listSize = employees->size();
    LListNode<Employee*>* cursor = nullptr;
    Employee* currentData;
    Employee** employeeArr = new Employee*[listSize];
    int counter = 0;
    // Add unsorted employess to list
    if (!employees->isEmpty()) {
        listSize = employees->size();
        cursor = employees->atHead();
        while (cursor != nullptr) {
            currentData = cursor->getData();
            employeeArr[counter] = currentData;
            cursor = employees->nextOf(cursor);
            counter++;
        }
    }
    // Sort the list
    sort(employeeArr, listSize);

    // Print sorted items from the list
    for (int i = 0; i < listSize; i++) {
        currentData = employeeArr[i];
        cout << currentData->getEmployeeName();
        cout << ", $" << currentData->getTotalPay() << endl;
    }

    // Delete the temporary list
    delete[] employeeArr;
}

void EmployeeList::addHoursToEmployee(int employeeId, int hoursToAdd) {
    Employee* employee = findEmployeeById(employeeId);
    int currentHours;
    if (employee == nullptr) {
        cout << "Warning: no employee with id " << employeeId;
        cout << " found. Unable to add " << hoursToAdd << " hours." << endl;
    } else {
        currentHours = employee->getHoursWorked();
        employee->setHoursWorked(currentHours + hoursToAdd);
    }
}

void EmployeeList::clearList() {
    LListNode<Employee*>* cursor = nullptr;
    Employee* currentData;

    // Deletes all Employee objects
    if (!employees->isEmpty()) {
        cursor = employees->atHead();
        while (cursor != nullptr) {
            currentData = cursor->getData();
            if (currentData != nullptr)
                delete currentData;
            cursor->setData(nullptr);
            cursor = employees->nextOf(cursor);
        }
    }

    // Deletes nodes in SLL
    employees->clear();
}

ostream& EmployeeList::printAll(ostream& outs) {
    employees->print(outs, true);
    return outs;
}

void EmployeeList::readEmployeeListFromFile(string filename) {
    fstream fs;
    bool isEOF;
    Employee* currentEmployee;
    int currentEmployeeId;
    double currentEmployeePayRate;
    string currentEmployeeName;
    fs.open(filename);
    employees = new LList<Employee*>;
    if (fs.fail()) {
        cout << "Error: Failed to open file: '" << filename << "'" << endl;
        exit(1);
    } else {
        isEOF = fs.eof();
        while (!isEOF) {
            fs >> currentEmployeeId >> currentEmployeePayRate;
            getline(fs, currentEmployeeName);
            // Removing the leading whitespace character
            currentEmployeeName = currentEmployeeName.substr(1, currentEmployeeName.length());
            createEmployee(currentEmployeeId, currentEmployeePayRate, currentEmployeeName);
            isEOF = fs.eof();
        }
    }
}

void EmployeeList::readEmployeeHoursFromFile(string filename) {
    fstream fs;
    bool isEOF;
    Employee* currentEmployee;
    int currentEmployeeId;
    int currentEmployeeHourEntry;
    fs.open(filename);
    if (fs.fail()) {
        cout << "Error: Failed to open file: '" << filename << "'" << endl;
        exit(1);
    } else {
        isEOF = fs.eof();
        while (!isEOF) {
            fs >> currentEmployeeId >> currentEmployeeHourEntry;
            addHoursToEmployee(currentEmployeeId, currentEmployeeHourEntry);
            isEOF = fs.eof();
        }
    }
}

void EmployeeList::createEmployee(int newEmployeeId, double newEmployeePayRate, string newEmployeeName) {
    Employee* newEmployeePtr = new Employee(newEmployeeId, newEmployeePayRate, newEmployeeName, 0);
    employees->insertAtEnd(newEmployeePtr);
}

Employee* EmployeeList::findEmployeeById(int id) {
    LListNode<Employee*>* cursor = nullptr;
    Employee* currentData;
    // If list is empty, no employee with that id can exist.
    if (employees->isEmpty()) {
        return nullptr;
    } else { // Otherwise, keep following pointers until a match is found.
        cursor = employees->atHead();
        while (cursor != nullptr) {
            currentData = cursor->getData();
            if (currentData->getId() == id)
                return currentData;
            cursor = employees->nextOf(cursor);
        }
        // If no employee found with matching ID, return a nullptr
        return nullptr;
    }
}
