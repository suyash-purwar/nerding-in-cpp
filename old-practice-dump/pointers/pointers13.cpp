#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int *func1(int *a, int *b) {
    int c = *a + *b;
    return &c;
    // Here, we are returning the address of the local variable 'c'
    // Which means outside code can access the local variable
    // But, remember that the local variables are flushed after function execution. They die after function execution.
    // So, address of variable 'c' that we are returning is non-existent after function execution
    // So, cout << add(&f, &g) ==> 0  | This happens because the address is flushed
    // cout << *(add(&, &g)) ==> Segmentation Fault
    // This is a VERY BAD PRACTICE and C++ compiler shows warning about this during execution
}

int &func2(int *a, int *b) {
    int sum = *a + *b;
    return sum;
    // Same fate as func1()   
}

int main() {
    int f = 12;
    int g = 9;
    int *z = func1(&f, &g);
    // cout << *z << endl; // Segmentation Fault (core dumped)
    cout << z << endl; // Returns 0

    int k = func2(&f, &g);
    // cout << k << endl; // Segmentation Fault
    // cout << &k << endl; // Segmentation Fault
    return 0;
}