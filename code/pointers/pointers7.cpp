/**
 * @file pointers7.cpp
 * @author Suyash Purwar
 * @brief Operations on Pointers
 * @date 27-09-2022
 */

#include<iostream>

using std::cin;
using std::cout;
using std::endl;

int add(int &a, int *b) {
    return a + *b;
}

void doSomething(int *a, int &b) {
    cout << a << endl;
    cout << b << endl;
    // Variable b points to the memory of address of the first element of the arraay 'arr'
    // cout << *c << endl; // c is not a pointer variable
    cout << *(&b+1) << endl;
    // Here, we accessed the memory address to which points to. Performed arithmetic addition on the address.
    // Since, elements of the array are stored in contigious memory blocks, incrementing the address by one would take us 4 bytes ahead and address of the next element of the array would be retrieved.
    // Using dereferencing operator, value at the next memory block is retrieved
}

int main() {
    int b = 23;
    // &a refers to address of variable 'a'
    int &a = b;
    // Here, address of variable 'a' is equal to address of variable 'b'
    // Hence, both variable 'a' and 'b' point to the same address
    int *c = &b;
    // Variable 'c' is of int pointer type which can store the address of another variable as it's value
    // Here, variable 'c' stores the address of variable 'b'

    // The difference between line 16 and 19 are as follows:
    // Variable 'a' points to the same memory address as variable 'b ' points to. Both 'a' and 'b' point to the same memory address
    // Variable 'c' stores the address of 'b'

    cout << a << endl;
    cout << b << endl;
    cout << &a << endl;
    cout << &b << endl;

    cout << add(a, &a) << endl;

    a = 44; // Changed the value of var 'a'. Value of b should also get updated as both of them point to the same memory address
    cout << b << endl; // Yes, the value of b changes as well

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << &arr << " " << arr << " " << *arr << endl;
    doSomething(arr, *arr);

    return 0;
}