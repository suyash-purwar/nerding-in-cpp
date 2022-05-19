#include <iostream>

using namespace std;

// Array

int main() {
    // Size of the array has to be defined during initialization of arrays
    float savings[10] = { 100, 232, 83, 278, 387, 243, 190 };
    savings[7] = 182;

    int arr[3];
    cout << arr[1] << endl; // Return either 0 or garbage value

    cout << savings[7] << endl; // Return 182
    cout << savings[8] << endl; // Returns either 0 or garbage value
    cout << savings[11]; // Return non-sensical value. Maybe garbage value
    return 0;
}