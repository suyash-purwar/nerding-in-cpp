#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
    // Pointers: Variables that store address of other variables

    int z;
    int *p = &z;
    z = 10;

    cout << p << endl; // Prints the address of the variable a
    cout << &z << endl; // & returns the address the variable
    cout << &p << endl; // &p returns the address of the pointer variable
    cout << *p << endl; // *p returns the variable stored at the address which is stored in p. Basically returns the value of the variable a

    // Pointer of one datatype can store the address of the variable of only that datatype.
    // Examples are below

    bool isTrue = false;
    bool *boolPointer;
    boolPointer = &isTrue;

    cout << boolPointer << endl << endl;

    double a = 9.2321;
    double *b = &a;
    double **c = &b;
    cout << (c == &b) << endl;
    cout << (*c == &a) << endl;
    cout << (**c == a) << endl;
    cout << *&a << endl;
    cout << *&*&a <<endl;
    cout << (&*c == &b) << endl;
    cout << &*c << endl;
    cout << (&*b == &a ) << endl;
    cout << &b << endl;

    /**
     * @brief Void Pointer
     * @brief These tyepes of pointers can store addresses of any type of variables.
     * @brief *vp1 is not allowed
     * @brief Pointer arithmetic is not allowed in for Void Pointers
     */

    char c1 = 'A';
    void *vp1 = &c1;
    cout << endl << vp1 << endl;
    // cout << *vp1 << endl;
    // cout << vp1 + 1 << endl;

    return 0;
}