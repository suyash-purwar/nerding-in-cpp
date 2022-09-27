// There are two types of Header Files
// 1. System Header Files: It comes with the compiler
#include <iostream>
// 2. User defined header files: It is written by the programmer
#include "header.h" // --> For this to work, header.h should be there in the file system

using std::cout;
using std::cin;
using std::endl;

// Scope Resolution Operator(::) - Allows to access the variable from the global scope
int c = 23;

int main() {
    int a = 23, b = 45, c = a + b;
    cout << c << endl; // Accesses the local variable c (68)
    cout << ::c << endl;// Accesses the global scope variable (23)
    
    if (true) {
        int c = 0;
        cout << c << endl; // 0
        cout << ::c << endl; // Accesses the global scope variable (23)
    }

    cout << "A code to learn the workings of header files" << endl;
    return 0;
}

// Typecasting

// By default a decimal literal is of double type. 34.4 is double by default
// If you want it to have a type of float, it should be written as 34.4f or 34.4F

// Adding 'f' after the decimal literal in the below example is redundant because the keyword float makes it a type of float
float f1 = 34.4;

// Use 'l' or 'L' to make it a type of 'long double'