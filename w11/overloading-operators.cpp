#include <iostream>
using namespace std;

class A {
    public:
        friend bool operator==(const A& lhs, const A& rhs);
        A(int val = 0): val_(val) {};
        friend ostream& operator<<(ostream& outs, const A& a);
        ~A() {
            cout << "Destroying: A(" << val_ << ")" << endl;
        }
    private:
        int val_;
};

void makeAndBreak(int n);

int main() {
   A a1(12);
   A a2 = A(13); // Note the various syntaxes
   A a3(12);

   cout << "a1: " << a1 << endl;
   cout << "a2: " << a2 << endl;
   cout << "a3:  " << a3 << endl;
   cout << "a1 == a2: " << (a1 == a2) << endl;
   cout << "a1 == a3: " << (a1 == a3) << endl;

   // Making and breaking
   makeAndBreak(666);
   makeAndBreak(333);
   makeAndBreak(111);
   makeAndBreak(999);
}

void makeAndBreak(int n) {
    A a1(n); // Make an A instance

    cout << "Made: " << a1 << endl;

    return; // Unmake
}

// NOTE: "friend" doesn't need to be repeated here and no namespace provided.
bool operator==(const A& lhs, const A& rhs) {
    return lhs.val_ == rhs.val_;
}

ostream& operator<<(ostream& outs, const A& a) {
    outs << a.val_;
    return outs;
}
