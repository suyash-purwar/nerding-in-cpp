#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
    /**
     * Whenever a program starts, it comes with two types of memories
     * 1) Stack - It is smaller in size in comparison to Heap memory. All the compile time variables like 'int a = 10' or 'int arr[12]' utilizes this memory space.
     * 2) Heap - It is bigger in size than Stack memory and is used to create runtime variable sized arrays. 'int a = 10' or 'int arr[12]' could be made to get stored in this memory using the 'new' keyword.
     */

    // Here, variable sized arrays are being created without the usage of Heap memory.
    // This method is not recommended as it could lead to problems.
    // Some of the compilers do not even support this functionality and may show warnings
    // The reason behind why this is not recommended is as follows
    // As mentioned earlier, every program comes with it's own memory of some size
    // And suppose at the runtime, user creates the array which cannot be accomodated in the stack... this could lead to program crash
    // int arr[n] --> Here size of the array is not defined at the compile time. So, programs starts with some stack memory
    // Now, suppose user enters the array size which cannot be accomodated in the stack memory, then the program crashes
    // This is the reason why this is considered a bad practice

    // int n;
    // cin >> n;
    // int arr[n];  // BAD PRACTICE
    // for (int i = 0; i < n; i++) {
    //     cin >> arr[i];
    // }
    // for (int j = 0; j < n; j++) {
    //     cout << arr[j] << "\t";
    // }
    // cout << endl;

    // Since stack memory is small, we could utilise Heap memory which has ample space to accomodate even large size of arrays
    // We can use the 'new' keyword to start using the Heap memory
    // When we create memory through Stack memory, it is called Static Memory Allocation
    // When we creare memroy through Heap memory, it is called Dynamic Memory Allocation

    // In heap memory, variable name is not needed to create memory. We use poiters.
    // General format of creating variables through Heap Memory
    // datatype *variable_name = new datatype
    // Ex: char *ch = new char; <-- This whole line consume 8 bytes (left) + 1 bytes (right) = 9 bytes
    // Note that here ch is a pointer type variable which occupies 8 bytes in the Stack memory and 1 byte of space in allocated in the Heap memory
    // 'new char' allocated 1 byte in the heap memory and returns the address of that location
    // 'char *ch' is a pointer type variable. So, it stores that address in it.
    // Ex: int *i = new int; .<-- This whole line consumes 8 bytes (left) + 4 bytes (right) = 12 bytes

    int *i = new int; // Take 12 bits
    char *c1 = new char; // Takes 9 bits

    // How to create arrays in Heap memory
    int *array1 = new int[10]; // 8 bytes (left) + 4 bytes * 10 (right) = 48 bytes
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    int *arrayN = new int[n]; // GOOD PRACTICE
    for (int i = 0; i < n; i++) {
        cin >> *(arrayN+i);
    }
    for (int i = 0; i < n; i++) {
        cout << *(arrayN + i) << "\t";
    }
    cout << endl;

    /******************************/
    // Variable i occupies memory from the stack
    // Variable i is created inside the braces and is freed from stack memory once the end brace is reached
    // So, it's all good
    while (true) {
        // i created in the stack memory
        int i = 5;
        // i deleted from the stack memory
    }

    // num is created in the stack memory. So, it'll be created and freed from but 'new int' allocates 4 bytes in the heap memory again and again till the space in heap memory is filled. Program crashes once the space is filled
    while(true) {
        int *num = new int;
    }

    // Deallocation of Heap Memory
    // In heap, we have to explicitly free the memory. Stack frees the space when the execition moves out of lexicals scope.
    // Stack frees the space by itself.
    // We use the 'delete' keyword for that
    // Note: Always remember to clean the heap memory after it's usage

    // Delete 
    int *b = new int;
    delete b;

    int *arr = new int[5];
    delete []arr; // Deleting the whole array from the heap

    return 0;
}