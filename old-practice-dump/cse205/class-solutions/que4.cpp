#include<iostream>

using namespace std;

int main() {
    int size, number;
    int array[50];

    cin >> size;
    if (size <= 50 && size >= 10) {
        for (int i = 0; i < size; i++) {
            cin >> array[i];
        }
    } else {
        cout << -1;
        exit(0);
    }

    cin >> number;

    for (int j = 0; j < size; j++) {
        if (number == array[j]) {
            cout << j+1;
            exit(0);
        } else {
            if (j == size-1) {
                cout << -1;
                exit(0);
            }
        }
    }
    return 0;
}