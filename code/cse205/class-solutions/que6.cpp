#include <iostream>

using namespace std;

int main() {
    int sizeOfArr;
    cin >> sizeOfArr;
    int arr[10];
    for (int i = 0; sizeOfArr > i; i++) {
        cin >> arr[i];
    }
    int max = -1;
    int maxAt = -1;
    for (int j = 0; sizeOfArr > j; j++) {
        if (arr[j] >= max && j > maxAt) {
            max = arr[j];
            maxAt = j;
        }
    }

    cout << maxAt;
}