#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
    // Pointers: Variables that store address of other variables

    int a;
    int *p = &a;
    a = 10;

    cout << p << endl; // Prints the address of the variable a
    cout << &a << endl; // & returns the address the variable
    cout << &p << endl; // &p returns the address of the pointer variable
    cout << *p << endl; // *p returns the value stored at the address which is stored in p. Basically returns the value of the variable a

    // Pointer of one datatype can store the address of the variable of only that datatype.
    // Examples are below

    bool isTrue = false;
    bool *boolPointer;
    boolPointer = &isTrue;

    cout << boolPointer << endl << endl;

    double db = 9.2321;
    double *dbPointer = &db;
    double **dbPointerPointer = &dbPointer;
    cout << (dbPointerPointer == &dbPointer) << endl;
    cout << (*dbPointerPointer == &db) << endl;
    cout << (**dbPointerPointer == db) << endl;
    cout << *&db << endl;
    cout << *&*&db <<endl;
    cout << (&*dbPointerPointer == &dbPointer) << endl;
    cout << &*dbPointerPointer << endl;
    cout << &dbPointer << endl;

    return 0;
}