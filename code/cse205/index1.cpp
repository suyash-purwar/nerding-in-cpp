#include <iostream>

using std::cout;

int main() {
    int a[2] = {1, 2};
    a[5] = 10;
    cout << a[5];
    return 0;
}