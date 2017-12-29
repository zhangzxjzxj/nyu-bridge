#include <iostream>
using namespace std;

template <class T>
class Node {
    public:
        Node(T *mVal);
        T* getVal();
        void setVal(T newVal);
        friend ostream& operator <<(ostream& outs, Node<T>& n);
    private:
        T* val;
};

class Date {
private:
	int day;
	int month;
	int year;
public:
	// Constructor Function
	Date(int newD, int newM, int newY): day(newD), month(newM), year(newY){}
};

int main() {
    int x = 100;
    int y = 40;
    Node<int> *n = new Node<int>(&x);   // sets a mutable reference
    Node<int> &n2 = *n; // sets an immutable reference
    cout << "x: " << x << endl;
    cout << "n.val: " << *n->getVal() << endl;
    n2.setVal(200);
    cout << "x: " << x << endl;
    cout << "n2.val: " << *n2.getVal() << endl;
    n = new Node<int>(&y);
    cout << "y: " << y << endl;
    cout << "n.val: " << *n->getVal() << endl;
    n2 = *n;    // still refers to old instance
    n2.setVal(200);
    cout << "x: " << y << endl;
    cout << "n2.val: " << *n2.getVal() << endl;
}

template <class T>
Node<T>::Node(T *mVal) {
    val = mVal;
}

template <class T>
T* Node<T>::getVal() {
    return val;
}

template <class T>
void Node<T>::setVal(T newVal) {
    *val = newVal;
}

template <class T>
ostream& operator <<(ostream& outs, Node<T>& n) {
    outs << "NodeVal: " << n;
    return outs;
}
