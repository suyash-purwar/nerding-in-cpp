#include<iostream>

using namespace std;

// Todo
// Add checks to see if the numbers entered are in descending order or not

int main() {
    int n1, n2;

    cin >> n1;
    if (n1 >= 20 && n1 < 0) {
        cout << "Invalid Array";
        exit(0);
    }
    int* arr1 = new int(n1);
    for (int i = 0; i < n1; i++) cin >> arr1[i];

    cin >> n2;
    if (n2 >= 20 && n2 < 0) {
        cout << "Invalid Array";
        exit(0);
    }
    int n2InitialSize = n2;
    int* arr2 = new int(n1 + n2);
    for (int j = 0; j < n2; j++) cin >> arr2[j];

    int diff = arr2[0] - arr1[0];
    for (int k = 0; k < n1; k++) {
        for (int m = 1; m <= n2InitialSize; m++) {
            if (diff <= 0 && m == 1) {
                m-=2;
                continue;
            }
            if ((arr2[m] - arr1[k] <= diff) && (arr2[m] - arr1[k] > 0)) {
                diff = arr2[m] - arr1[k];
                if (m == n2InitialSize-1) {
                    arr2[m+1] = arr1[k];
                }
            } else {
                for (int a = n2InitialSize-1; a >= m ; a--) {
                    arr2[a+1] = arr2[a];
                }
                arr2[m] = arr1[k];
                n2InitialSize++;
                break;
            }
        }
        diff = arr2[0] - arr1[k+1];
    }

    for (int h = 0; h < n1+n2; h++) {
        cout << arr2[h] << " ";
    }

    return 0;
}