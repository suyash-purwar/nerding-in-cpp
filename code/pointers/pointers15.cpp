#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    int fixed_arr[5] = {2, 4, 3, 1, 9};
    int *n = new int;
    *n = 10;
    cout << *n << endl;
    cout << n << endl;
    cout << &n << endl;

    int *arr = new int[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = fixed_arr[i];
    }
    for (int j = 0; j < 5; j++) {
        cout << arr[j] << "  ";
    }
    cout << endl;

    cout << *arr << endl;
    cout << *(arr+1) << endl;
    cout << *(arr+2) << endl;

    // Creating 2D Arrays
    int x, y;
    int value = 0;
    // cin >> x >> y;
    x = y = 4;
    int **twoDarr = new int*[x];
    for (int i = 0; i < x; i++) {
        twoDarr[i] = new int[y];
    }
    // Allocating values in 2d array
    for (int j = 0; j < x; j++) {
        for (int k = 0; k < y; k++) {
            twoDarr[j][k] = ++value;
        }
    }
    // Printing the allocated values<
    for (int m = 0; m < x; m++) {
        for (int n = 0; n < y; n++) {
            cout << twoDarr[m][n] << "  ";
        }
        cout << endl;
    }

    cout << *twoDarr << endl; // Prints the address of the first row/array
    cout << **twoDarr << endl; // Prints the first value of the first row/array
    cout << *(*(twoDarr + 1) + 2) << endl; // Prints the 3rd element of the 2nd row
    cout << *(*(twoDarr + --x) + --y) << endl; // Prints the last element of the last row

    cout << twoDarr[1][1] << endl; // This works but this same line on line number 62 wouldn't work as we delete the array from the heap below
    // Deletion of the 2D array
    for (int g = 0; g < x; g++) {
        delete []twoDarr[g]; // Delete all the subarrays
    }
    delete []twoDarr; // Deletes the outer array
    cout << twoDarr[1][1] << endl; // Segmentation Fault | Now that array is deleted from the head, this error will be raised by the compiler


    // Make sure you understand the memory representation of 2d array
}