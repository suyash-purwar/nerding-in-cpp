/**
 * @file pointers4.cpp
 * @author Suyash Purwar
 * @brief Call by Reference
 * @date 2022-09-12
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/**
 * @brief Call by reference
 */
// Not optimized
// int product(int *n1) {
//     int res = 1;
//     while (*n1 >= 1) {
//         res = res * *n1;
//         *n1 = *n1 - 1;
//     }
//     return res;
// }

// Optimized solution - Using Recursion
// Call by reference
int product(int *n1) {
    if (*n1 != 1) return *n1 * product(&(*n1=*n1-1));
}

int main() {
    int n;
    cout << "Enter the number: ";
    cin >> n;

    cout << product(&n) << endl;
    return 0;
}