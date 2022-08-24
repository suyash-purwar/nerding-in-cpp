#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Solution {
    public:
        static void insertElement() {
            int size, actualSizeOfArr, anotherElement, location;
            int array[50];
            cout << "Enter the size of the array: ";
            cin >> size;
            if (size > 50) {
                cout << "Size of the array must be less than 50.";
            } else {
                cout << "How many elements do you want to insert into array: ";
                cin >> actualSizeOfArr;
                for (int i = 0; i < size; i++) {
                    if (i < actualSizeOfArr) {
                        cin >> array[i];
                    } else {
                        array[i] = 0;
                    }
                }
                for (int j = 0; j < size; j++) {
                    cout << array[j] << "\t";
                }
            }
            cout << endl << "Enter the number you want to insert: ";
            cin >> anotherElement;
            if (size == actualSizeOfArr) {
                cout << "Insertion is not possible because of Array Overflow..." << endl;
                exit(0);
            }
            anotherElement < size ? (location = size % anotherElement) : (location = anotherElement % size);
            if (size > location) {
                // array[location-1] = anotherElement;
                for (int i = size; location <= i+1; i--) {
                    array[i+1] = array[i];
                }
                if (location == 0) {
                    array[location] = anotherElement;
                } else {
                    array[location-1] = anotherElement;
                }
                cout << "The element " << anotherElement << " is inserted at the location " << location << endl;
            } else {
                cout << "Insertion is not possible because of Array Overflow..." << endl;
            }
            for (int i = 0; i < size; i++) {
                cout << array[i] << " ";
            }
        }
};

int main() {
    Solution solution;
    solution.insertElement();

    return 0;
}