/**
 * @file pointers8.cpp
 * @author Suyash Purwar
 * @brief Pointers and Array
 * @date 27-09-2022
 */
#include <iostream>

using namespace std;

void passArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        cout << *(array+i) << "\t";
    }
    cout << endl;
}

void dma() {
    int size; int array;
    cout << "Enter the size of the array: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        cin >> *((&array)+i);
    }

    cout << "Elements are: " << endl;
    for (int i = 0; i < size; i++) {
        cout << *(&array+i) << "\t";
    }
    cout << endl;
}

int main() {
    int a[5] = {3, 2, 4, 9, 7};
    cout << sizeof(a) << endl; // Gives the size of the whole array
    cout << sizeof(*a) << endl; // Gives the size of one element of array
    cout << sizeof(*(a+0)) << endl; // Gives the size of one element of array
    int *p = a+2; // (a+2) returns the address of first element which is of 8 bytes as pointer type variable is of 8 bytes
    cout << sizeof(p) << endl;
    cout << sizeof(*p) << endl;
    cout << sizeof(&p) << endl;

    int size = sizeof(a) / sizeof(*a);
    cout << "Size of the array is " << size << endl;
    passArray(a, size);
    // dma(); // Not working as expected

    int i = 3;
    cout << i[a] << endl; // IMPORTANT

    return 0;
}