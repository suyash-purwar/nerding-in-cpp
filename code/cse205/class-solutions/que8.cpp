#include<iostream>

using namespace std;

int main() {
    int temperatures[8], position, element;
    for (int i = 0; i < 7; i++) {
        cin >> temperatures[i];
    }
    cin >> position;
    cin >> element;
    if (position > 7 || position < 0) {
        cout << "Invalid Position";
        exit(0);
    }
    for (int i = 7; i > position; i--) {
        temperatures[i] = temperatures[i-1];
    }
    temperatures[position] = element;
    for (int j = 0; j < 8; j++) {
        cout << temperatures[j];
        if (j != 7) cout << ",";
    }
    return 0;
}