#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
    // Code for Jaggered Array
    // Jaggered Array: Jagged arrays are a special type of arrays that can be used to store rows of data of varying lengths to improve performance when working with multi-dimensional arrays.

    int cols, rows;
    int value = 0;
    cout << "Enter the no. of rows: ";
    cin >> rows;
    cout << "Enter the size for every row: ";
    int *sizes = new int[rows];
    int **jaggered_array = new int*[rows];
    // Creation of jaggered array
    // Storing the size of every row in a separate 1D dynamic array to retrieve, output, and delete the elements
    for (int i = 0; i < rows; i++) {
        cin >> sizes[i];
        jaggered_array[i] = new int[sizes[i]];
    }
    // Taking inputs
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < sizes[j]; k++) {
            jaggered_array[j][k] = ++value;
        }
    }
    // Displaying values
    for (int l = 0; l < rows; l++) {
        for (int m = 0; m < sizes[l]; m++) {
            cout << jaggered_array[l][m] << "  ";
        }
        cout << endl;
    }
    // Deleting the values
    for (int d = 0; d < rows; d++) {
        delete []jaggered_array[d];
    }
    delete []jaggered_array;
    return 0;
}