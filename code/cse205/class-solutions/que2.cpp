#include <iostream>

using std::endl;
using std::cout;
using std::cin;

class Solution {
    public:
        static void ArrayShiftInsertion() {
            int noOfStudents;
            int heightOfStudents[100];
            cout << "Enter the number of students: ";
            cin >> noOfStudents;
            if (noOfStudents < 2) {
                cout << "Invalid Input" << endl;
                exit(0);
            }
            cout << "Enter the height of students: " << endl;
            for (int i = 0; i < noOfStudents; i++) {
                cin >> heightOfStudents[i];
            }

            int toBeInserted = 0;
            for (int i = 0; i < noOfStudents; i++) {
                if ((heightOfStudents[i] % 2 != 0) && (heightOfStudents[i+1] % 2 != 0)) {
                    toBeInserted = (heightOfStudents[i] + heightOfStudents[i+1]) / 2;
                    for (int j = noOfStudents; j >= i+1; j--) {
                        heightOfStudents[j+1] = heightOfStudents[j];
                    }
                    heightOfStudents[i+1] = toBeInserted;
                    noOfStudents++;
                } else {
                    continue;
                }
            }

            for (int k = 0; k < noOfStudents; k++) {
                cout << heightOfStudents[k] << " ";
            }
        }
};

int main() {
    Solution sol;
    sol.ArrayShiftInsertion();
    return 0;
}