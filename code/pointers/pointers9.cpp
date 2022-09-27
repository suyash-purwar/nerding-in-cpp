/**
 * @file pointers9.cpp
 * @author Suyash Purwar
 * @brief Pointers and Character Arrays
 * @date 28-09-2022
 */

#include<iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    int a[5] = {3, 1, 9};
    char b[6] = "abcde";
    // Note: Length of char array is 6 because the sixth elemet in the character array is the new line element (\n)
    // So, line 16 is equivalent to char b[6] = "abcde\n"

    cout << a << endl; // Address of the first element of the array will get printed
    cout << b << endl; // abcdef will be printed
    // This is because the 'cout' function handle character arrays differently

    char *p = b;
    cout << sizeof(p) << endl; // Size of pointer variable will be printed which is 8 bytes in the 64 bit systems
    cout << sizeof(*p) << endl; // Size of value which is stored at address will be printed which in this case is 1 byte. Char value occupies in 1 byte
    cout << *p << endl; // First value from the character array will be printed
    cout << *(p+1) << endl;

    // Address of the first element should get printed
    // But 'abcdef' does get printed because 'cout' function works differently in the case of character arrays
    cout << p << endl;

    // Imp. Note: 'cout' prints the values at subsequent memory blocks till the '\n' character is found
    char ch1 = 'x';
    char *ch1_ptr = &ch1;
    cout << ch1_ptr << endl;
    // As mentioned previously, line 37 will not print the address at which x is stored
    // But it will print value stored in ch1
    // Note that it's only one character with no '\n' character
    // So, it will print the value stored in the subsequent memory addressed till the '\n' is found in any of the memory block
    // It will print some random characters and symbols stored in the subsequent memory blocks till it finds '\n'

    char *risky_char = "abcdef"; // YE KABHI NAHI KARNA. CAN LEAD TO ERRORS
    cout << risky_char << endl;
    // It stores 'a' from 'abcdef' and stores it an address which is empty and writable
    // Similar thing happens to all the other characters
    // But there may be a case where, where the compiler tries to store the character in a read-only or prefilled memory block\
    // So, this is not recommended
    // This is a bit complex to wrap your head around. Refer to Love Babbar's video on Pointer Part 2

    return 0;
}