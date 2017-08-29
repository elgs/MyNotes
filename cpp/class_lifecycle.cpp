#include <iostream>
#include <assert.h>

using namespace std;

class A {
private:
    int refcount = 0;
public:
    string* s;

    A(string a) : s(new string(a)) {
        ++this->refcount;
        cout << "+++++ Constructor invoked. " << *this->s << " at: " << this << endl;
    }

    A(const A& a) {
        if (this != &a) {
            this->s = new string(*a.s);
            this->refcount = 1;
        }
        cout << "Copy constructor invoked. " << *this->s << " at: " << this << endl;
    }

    A& operator=(const A& a) {
        if (this != &a) {
            *this->s = *a.s;
        }
        cout << "Copy assignment operator invoked. " << *this->s << " at: " << this << endl;
        return *this;
    };

    A(A&& a) {
        if (this != &a) {
            this->s = a.s;
            a.s = nullptr;
            this->refcount = 1;
        }
        cout << "Move constructor invoked. " << *this->s << " at: " << this << endl;
    }

    A& operator=(A&& a) {
        if (this != &a) {
            this->s = a.s;
            a.s = nullptr;
        }
        cout << "Move assignment operator invoked. " << *this->s << " at: " << this << endl;
        return *this;
    }

    ~A() {
        --this->refcount;
        cout << "----- Destructor invoked. refcount:" << this->refcount << " at: " << this << endl;
        if (this->refcount <= 0) {
            delete this->s;
            cout << "~~~~~ deleted. " << " at: " << this << endl;
        }
        assert(this->refcount >= 0);
    }

    friend ostream& operator<<(ostream& os, const A& a) {
        cout << a.s;
        return os;
    }
};

void f() {
    A a("hello"); // Constructor invoked.
    A b("world");// Constructor invoked.
    a = b; // Copy assignment operator invoked.
    A c = a; // Copy constructor invoked.
    A d = move(a); // Move constructor invoked.
    d = move(b); // Move assignment operator invoked.
}

int main() {
    cout << "Entering main." << endl;
    f();
    cout << "Exiting main." << endl;
    return 0;
}
