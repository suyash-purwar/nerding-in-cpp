/**
 * @file pointers6.cpp
 * @author Suyash Purwar
 * @brief Arrays and Functions
 * @date 2022-09-12
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// Arrays are never passed by value
// C++ prohibits that
// int totalOfElements(int arr[]) {
//     int sizeOfArr = sizeof(arr) / sizeof(arr+0);
//     cout << sizeOfArr << endl;
//     return 0;
// }

int totalOfElements(int *arr, int size) {
    // Here arr holds the address of first element of the array
    // cout << *arr << endl; --> prints 4 (which is the first element in the array)
    // But arr[i] could also be used to access the subsequent elements
    int sum = 1;
    for (int i = 0; i < size; i++) {
        sum += *(arr+i);
    }
    return sum;
}

void doubleTheAmount(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        *(arr+i) = arr[i]*2;
    }
}

int main() {
    int x[4] = {4, 7, 2, 1};
    int size = sizeof(x)/sizeof(x+0);
    cout << totalOfElements(&x[0], size) << endl;
    cout << totalOfElements(x, size) << endl;
    // cout << totalOfElements(&x, size) << endl; // argument of type "int (*)[4]" is incompatible with parameter of type "int *"
    cout << totalOfElements((int*)&x, size) << endl; // This work because of pointer typecasting
    doubleTheAmount(x, size);
    for (int i = 0; i < size; i++) {
        cout << *(x+i) << " ";
    }
    return 0;
}