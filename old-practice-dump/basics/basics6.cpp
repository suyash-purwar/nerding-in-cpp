#include<iostream>

using namespace std;

/**
 * Inline Functions
 * 
 * -> They work quite similarly to macros
 * -> Inline functions have a constraint that there body can have 1 statement only.
 * -> They can sometimes, at max, contain 3 statements. More than 3 result in an error.
 * -> Function call of inline function gets replaced with the statement written in the function body
 * -> This improves the performance as it eliminates the need of pushing another function onto execution stack
 */

inline int min(int &a, int &b) {
    return (a > b) ? b : a; 
}

int main() {
    int a = 10; int b = 4;
    cout << min(a, b) << endl;    
    return 0;
}