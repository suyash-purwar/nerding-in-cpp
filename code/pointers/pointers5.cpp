/**
 * @file pointers5.cpp
 * @author Suyash Purwar
 * @brief Pointers and Arrays
 * @date 2022-09-12
 */

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

int main() {
    int a1[5] = {8, 4, 2, 5, 9};
    int *p = a1;
    cout << sizeof(a1) << endl; // size of int * no. of ints = 20
    cout << "Size of the array is " << sizeof(a1)/sizeof(a1+0) << endl;

    cout << a1 << endl; // It prints the address of element at 0 index
    cout << &a1 << endl; // It also prints the address of element at index 0
    cout << a1+1 << endl;  // a1+1 prints the address of element at index 1
    cout << a1+2 << endl; // a1+2 prints the address of element at index 2
    cout << p << endl; // It prints the address of element at 0 index
    cout << *a1 << endl; // Prints the value at 0 index

    cout << a1[1] << endl;
    *(a1+1) = a1[1]*2;  // This is equivalent to a1[1] = a1[1] * 2
    cout << a1[1] << endl;

    cout << &a1[2] << endl; // It prints the address of element at index 2
    cout << (&a1[1] == a1+1) << endl; // 1

    cout << a1[5] << endl; // Garbage Value
    cout << (*(a1+5) == a1[5]) << endl; // 1
    return 0;
}