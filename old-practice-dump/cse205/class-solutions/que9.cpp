#include<iostream>

using namespace std;

int main() {
    int nOfBalls;
    cin >> nOfBalls;
    int* balls = new int(nOfBalls);
    for (int x = 0; x < nOfBalls; x++) {
        cin >> balls[x];
    }
    for (int i = 0; i < nOfBalls-2; i++) {
        if (balls[i] % 2 != 0 &&
            balls[i+1] % 2 != 0 &&
            balls[i+2] % 2 != 0) {
            
            for (int j = i; j < nOfBalls-1; j++) {
                balls[j] = balls[j+1];
            }
            nOfBalls--;
            i--;
        }
    }

    for (int j = 0; j < nOfBalls; j++) {
        cout << balls[j] << " ";
    }
    return 0;
}