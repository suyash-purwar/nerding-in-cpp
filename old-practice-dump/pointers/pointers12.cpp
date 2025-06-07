#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

void update1(int n) {
    n++;
}

void update2(int &n) {
    n++;
}

void printAllValuesThroughRef(int &element, int *size) {
    cout << element << endl;
    for (int i = 0; i < *size; i++) {
        cout << *(&element + i) << "  ";
    }
    cout << endl;
    cout << (&element)[1] << endl; // Prints the 2nd element of the array
    // (&element) returns the address of the first element of the array
    // &element + i => would give the address of the subsequent items of the array
    // We know, that array[i] == *(array + i)
    // So, by that logic, &element + i must be equals to (&element)[i]
}

int main() {
    int a = 5;
    update1(a);
    cout << a << endl;
    update2(a);
    cout << a << endl;

    int arr[5] = {5, 3, 2, 1, 8};
    update2(*arr);
    
    // First element of the array is upgraded
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << "  ";
    }
    cout << endl;

    int *p = arr;
    cout << p[0] << "  " << *(p+1) << "  " << p[2] << endl;
    cout << (p+1 == arr+1) << endl;

    int size = sizeof(arr)/sizeof(*arr);
    printAllValuesThroughRef(*arr, &size);
}
