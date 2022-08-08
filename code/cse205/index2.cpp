#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Array {
    public:
        int x[10];
        Array() {

        }

        void readElement() {
            cout << "Enter the element of array: " << endl;
            for (int i = 0; i < 10; i++) {
                cin >> x[i];
            }
            cout << endl;
        }

        void displayElementForward() {
            cout << "The element of array are in forwards are: " << endl;
            for (int i = 0; i < 10; i++) {
                cout << x[i] << endl;
            }
            cout << endl;
        }

        void displayElementBackward() {
            cout << "The element of the array in backwards are: " << endl;
            for (int i = 9; i >= 0; i--) {
                cout << x[i] << endl;
            }
            cout << endl;
        }
};

int main() {
    Array arr1;
    arr1.readElement();
    arr1.displayElementForward();
    arr1.displayElementBackward();
    return 0;
}