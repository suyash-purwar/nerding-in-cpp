/**
 * @file pointers3.cpp
 * @author Suyash Purwar
 * @brief  Pointer Typecasting
 * @date 2022-09-11
 */

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
    /** @brief Commented code not working in my machine */
    // int a = 1025;
    // //   byte1    byte2    byte3   byte4 (Least Significant Byte)
    // // 00000000 00000000 00000100 00000001
    // //   2003     2002     2001    2000
    // int *a0 = &a;
    // // Pointer of type can store 4 bytes
    // // Pointer of type character can store only 1 byte
    // // Storing the int type of pointer in pointer variable of type char is not possile
    // // Pointer Typecasting comes into picture here

    // // Pointer Typecasting
    // // Here only byte4(Least Significant Byte) is stored in the pointer c. Rest are ignored
    // char *c0 = (char*)a0;
    // cout << c0 << endl;
    // cout << *c0 << endl;
    // cout << c0+1 << endl;
    // cout << *(c0+1) << endl;

    /** @brief datatype before pointer variable doesn't matter in some conditions when it comes to Pointer Typecasting */
    // Following are the examples for the same
    
    char a = '!';
    char *a0 = &a;
    cout << a0 << endl;

    bool bool1 = true;
    cout << &bool1 << endl;

    bool *bool1_pointer = (bool*)a0; // Pointer Typecasting
    cout << *bool1_pointer << endl;  // 33 | ASCII Code for '!' is 33 in Decimal | 33 in binary is 100001 which easily fits in one byte
    // Actually all ASCII symbols fit inside 1 byte

    cout << sizeof(bool1) << " " << sizeof(a) << endl;

    int z = 1025;
    int *z0 = &z;
    bool *z1 = (bool*)z0;
    cout << *z1; // 00000001 => 1
    cout << *(z1+1); // 00000100 => 4
    return 0;
}