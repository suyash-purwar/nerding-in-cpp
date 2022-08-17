#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Array {
    public:
        int maxsize = 10;
        int x[10];
        
        Array() {
            // No initalization needed
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
                exit(0);
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
                exit(0);
            } else {
                for (int i = index; maxsize > index; index++) {
                    x[index] = x[index+1];
                }
                x[maxsize-1] = 0;
                cout << "Deletion successful!" << endl;
            }
        }

        int* mergeArray(int arr1[5], int arr2[3], int* c) {
            int lengthOfArr1 = 5, lengthOfArr2 = 3;
            for (int i = 0; i < lengthOfArr1; i++) {
                c[i] = arr1[i];
            }
            for (int j = 0; j < lengthOfArr2; lengthOfArr1++, j++) {
                c[lengthOfArr1] = arr2[j];
            }
            cout << "Merge completed" << endl;
            return c;
        }
};

int main() {
    Array arr1;
    arr1.readElement();
    arr1.displayElementForward();
    arr1.displayElementBackward();
    arr1.insertElement();
    arr1.deleteElement();
    int array1[5] = {2, 34, 2, 4, 79};
    int array2[3] = {34, 56, 34};
    int n_arr[8];
    int* newArray = arr1.mergeArray(array1, array2, n_arr);
    for (int i = 0; i < 8; i++) {
        cout << newArray[i] << endl;
    }
    return 0;
}
