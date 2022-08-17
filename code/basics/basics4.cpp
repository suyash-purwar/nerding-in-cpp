// There are two types of Header Files
// 1. System Header Files: It comes with the compiler
#include <iostream>
// 2. User defined header files: It is written by the programmer
#include "header.h" // --> For this to work, header.h should be there in the file system

using std::cout;
using std::cin;
using std::endl;

int main() {
    cout << "A code to learn the workings of header files" << endl;

    return 0;
}