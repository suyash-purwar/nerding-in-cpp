#include <iostream>

using namespace std;

int main() {
    int sizeOfArray;
    cin >> sizeOfArray;
    int array[30];
    if (sizeOfArray > 2 && sizeOfArray < 30) {
        for (int i = 0; i < sizeOfArray; i++) {
            cin >> array[i];
        }
    } else {
        cout << "Invalid Input";
        exit(0);
    }

    for (int j = 0; j < sizeOfArray-1; j++) {
        if (array[j] == array[j+1]) {
            for (int k = j; k < sizeOfArray; k++) {
                array[k] = array[k+1];
            }
            j--;
            sizeOfArray--;
        }
    }

    for (int i = 0; i < sizeOfArray; i++) {
        cout << array[i] << " ";
    }
}