#include<iostream>

using std::cout;
using std::endl;

class A {
    public:
    A() {}
    A(A &a) {
        cout << "Copy Constructor called" << endl;
        this -> prop1 = a.prop1;
        this -> prop2 = a.prop2;
    }
    int prop1;
    char prop2;
};

// Here, it accepts address of an instance of class A
// Variable a is a pointer of type A
void doSomething(A* a) {
    cout << a -> prop1 << endl;
    cout << a -> prop2 << endl;
}

// Here, it is accepting a pointer of A by reference
// A* is the pointer of A which is a datatype
// For the same memory address which stores data of type 'Pointer of  type A', two names are being allocated
// For address of instance of object A, two names are present.
void doSomething(A* &a) {
    cout << a -> prop1 << endl;
    cout << a -> prop2 << endl;
}

// Here, instance of class A is being passed by reference
// For the memory address where the object resides, two names are being allocated
// Same memory address has two names
void doSomething(A &b) {
    cout << b.prop1 << endl;
    cout << b.prop2 << endl;
}

// For this one, copy constructor will be called.
// Instance of class A will be copied in the variable 'b' which is of type A.
// Since, it is getting copied, copy constructor will be called.
void printA(A b) {
    cout << b.prop1 << endl;
    cout << b.prop2 << endl;
}

int main() {
    A *a = new A();
    a -> prop1 = 1;
    a -> prop2 = 'A';

    doSomething(a);
    doSomething(*a);
    printA(*a);

    return 0;
}