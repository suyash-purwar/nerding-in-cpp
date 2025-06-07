#include<iostream>

using namespace std;

int main() {
    int prices[8];
    int max = 0, maxAt = -1;
    for (int i = 0; i < 8; i++) {
        cin >> prices[i];
    }
    int min = prices[0];
    for (int j = 0; j < 8; j++) {
        if (prices[j] > max && maxAt < j) {
            max = prices[j];
            maxAt = j;
        }
        if (prices[j] < min) min = prices[j];
    }
    prices[maxAt] = min;
    for (int k = 0; k < 8; k++) {
        cout << prices[k] << " ";
    }
    return 0;
}