#include<iostream>
#include<vector>
#define PI 3.14 // Object-like Macros
#define INSTAGRAM FOLLOWERS // Chain Macros
#define FOLLOWERS 64
// Multin-line Macros
#define ELEMENT 1, \
                2, \
                3
#define ELEMENT2 10, 11, 12
#define AREA(l, b) (l * b) // Function-like Macros
#define AREA_OF_CIRCLE(r) (PI * r * r) // Function-like Macros
#define MIN(a, b) ((a > b) ? a : b) // Function-like Macros

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Macros: A piece of code that is replaced by the value of the macro before compilation of the program.

/**
 * Benefits of using Macros
 * 1.Doesn't occupy memory as the name of the macro gets replaced by the value of it before compilation
 * 2.It is not changeable once it is defined
 */

 /**
  * Types of Macros
  * 1. Object-like Macros
  * 2. Chain Macros
  * 3. Multi-line Macros
  * 4. Function-line Macris
  */

int main() {
    double pi = 3.141;
    cout << PI << endl;

    short int length = 10;
    short int width = 3;
    cout << "Area is: " << AREA(length, width) << endl;
    // From the above program, we can see that whenever the compiler finds AREA(l, b) in the program it replaces it with the macros definition i.e., (l*b). The values passed to the macro template AREA(l, b) will also be replaced by the statement (l*b). Therefore, AREA(10, 5) will be equal to 10*5.

    cout << "I have " << FOLLOWERS << " on Instagram";
    cout << AREA_OF_CIRCLE(7) << endl;
    cout << MIN(12, 34) << endl;

    vector<int> list1 = {ELEMENT, ELEMENT2};
    for (int i = 0; i < list1.size(); i++) {
        cout << list1[i] << " ";
    }
    cout << endl;
    return 0;
}