#include <iostream>

using namespace std;

// Every program starts from the main function
int main() {
    // '<<' is called stream insertion operator
    // cout is a predefined object of ostream class
    char message[] = "Hello you lil kid";
    char name[15];
    cout << message << endl;
    // endl is a predefined object of ostream class
    // cin is a predefined object of istream class
    // '>>' is called stream extraction operator
    cin >> name;
    cout << "My name is " << name <<"! I'm here to learn C++ really fast" << endl;
    return 0;

    // DATA TYPES
    /*
        There are four types of data types in C++:
         - Basic Data Type: Char, Int, Float, Double, etc
         - Derived Data Type: Array, Pointer, etc
         - Enumeration Data Type: Enum
         - User Defined Data Type: Structure
    */

   // OPERATORS
   /*
        There are 7 types of operators. First 5 type of operators are binary operators
         - Arithmetic Operators: + - * /
         - Relational Operators: > < <= >= == !=
         - Logical Operators: && ||!
         - Bitwise Operators: & | << >> ~ ^
         - Assignment Operators: += -= *= /= %=
         - Unary Operators: ++ --
         - Ternary or Conditional Operator: ?:
   */
}