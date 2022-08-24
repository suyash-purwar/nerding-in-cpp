#include<iostream>

using namespace std;

int main() {
    char rainbow[] = {'V', 'I', 'B', 'G', 'Y', 'O', 'R'};
    char color;
    cin >> color;

    if (color >= 'A' && color <= 'Z') {
        for (int i = 0; i < 7; i++) {
            if (rainbow[i] == color) {
                for (int j = i; j < 7; j++) {
                    rainbow[j] = rainbow[j+1];
                }
                break;
            } else {
                if (i == 6) {
                    cout << "Color not available 2";
                    exit(0);
                }
            }
        }
        rainbow[6] = 0;
    } else {
        cout << "Color not available";
        exit(0);
    }

    for (int i = 0; i < 7; i++) {
        if (rainbow[i] != 0) {
            cout << rainbow[i];
        }
    }

    return 0;
}