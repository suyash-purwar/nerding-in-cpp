#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

class Arr {
    protected:
        int index0;
        int *index0_pointer = &index0;
        int arrowAt = 0;

    public:
        long int size;
        const long int length = size-1;

        Arr(long int s) {
            size = s;
        }

        void push(int element) {
            /**
             * @brief Below line is now not working in the second call of this method
             */
            *(index0_pointer+arrowAt) = element;
            arrowAt++;
        }

        void pop(int element) {
            free(index0_pointer+(--arrowAt));
        }

        void showAll() {
            for (int i = 0; i < size; i++) {
                /**
                 * @brief Not working here
                 */
                cout << *(index0_pointer+i) << "\t";
            }
            cout << endl;
        }

        void showAllWithAddress() {
            for (int i = 0; i < size; i++) {
                cout << index0_pointer+i << " ==> " << *(index0_pointer+i) << endl;
            }
        }
};

int main() {
    Arr arr1(3);
    arr1.push(6);
    arr1.push(2);
    arr1.showAll();

    return 0;
}