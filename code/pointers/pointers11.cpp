#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void func1(int *p) {
    p = p + 1;
    // Variable 'p' is a pointer variable which can store the address of other variable
    // Here, in the pointer variable 'p', we are storing p + 1
    // Which means that we are storing next subsequent memory block in p
    // Note that it does not change the value to which address stored in 'p' point to
}

void func2(int *p) {
    *p = *p + 1;
    // Here, the value to which address stored in 'p' gets incremented
}

// Whole array doesn't get passed, instead the address of the first element of the array gets passed
// Below, arr[] is equivalent to arr* which has the address of the first element of the array.
int sum(int arr[], int n) {
    cout << arr << endl;
    // We will get the output 8 but with a warning that says
    // 'sizeof' int arr[] is same as 'sizeof' int *arr which justifies why the output is 8.
    // Size of pointer type variable is 8 bytes.
    cout << "Size is:" << sizeof(arr) << endl; 
    int sum;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int a = 10;
    func1(&a);
    cout << a << endl;
    func2(&a);
    cout << a << endl;

    int arr[5] = {4, 2, 1, 3, 0}; // 10
    cout << sum(arr, 5) << endl;

    return 0;
}