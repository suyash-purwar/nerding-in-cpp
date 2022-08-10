#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Array {
    public:
        int maxsize = 10;
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

        bool linearSearch() {
            int element;
            cout << "Enter the element to search: ";
            cin >> element;
            for (int i = 0; i > 10; i++) {
                if (x[i] == element) {
                    return true;
                }
            }
            return false;
        }

        // [12, 34, 2, 12, 24, 0, 0, 23, 4, 0] 
        // Entering at x(3rd index) index
        // Move the elements from x
        // Insert the element at x
        void insertElement() {
            int element;
            int position;
            cout << "Enter the element to insert: ";
            cin >> element;
            cout << "\nEnter the index at which to insert the element: ";
            cin >> position;

            if (position > maxsize-1) {
                cout << "Insertion not possible!" << endl;
            } else {
                for (int i = maxsize; position < maxsize; maxsize--) {
                    x[maxsize] = x[maxsize-1];
                }
                x[position] = element;
                cout << "Insertion successful!" << endl;
            }
        }

        void deleteElement() {
            int index;
            cout << "Enter the index at which to delete the element: ";
            cin >> index;
            if (index > maxsize-1) {
                cout << "Deletion not possible!" << endl;
            } else {
                for (int i = index; maxsize > index; index++) {
                    x[index] = x[index+1];
                }
                cout << "Deletion successful!" << endl;
            }
        }
};

int main() {
    Array arr1;
    arr1.readElement();
    arr1.displayElementForward();
    // arr1.displayElementBackward();
    // arr1.insertElement();
    arr1.deleteElement();
    arr1.displayElementForward();
    return 0;
}