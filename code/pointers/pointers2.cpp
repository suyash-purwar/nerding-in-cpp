/**
 * @file pointers2.cpp
 * @author Suyash Purwar
 * @brief Pointer Arithmetic
 * @date 2022-09-11
 */

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

/**
 * In Pointer Artihmetic, only addition and substraction is allowed 
 */

/**
 * int type variable takes 4 bytes
 * long int type variables also takes 4 bytes
 * long long int type variables takes 8 bytes
 * short int type variable takes 2 bytes
 * char type variable takes 1 bytes
 */

int main() {
    int num1 = 69;
    int *num1_pointer = &num1;

    cout << num1_pointer << endl;
    /**
     * In the below case, incrementing an address by 1, compiler returns the next adjacent address which is 4 bytes ahead in the case of integer type variables.
     * Suppose, if the address is 2002, after incrementation of 1, it'll be 2006
     * From 2002 to 2005, one integer value is stored
     * From 2006, another integer can be stores
     * So, you can see it jumps by 4 bytes so that it can capture the next value stored in the next set of bytes
     * *(num1_pointer+1) --> Garbage Value | This is because there is no value in the next 4 set of bytes from 2006 to 2009
     * *(num1_pointer+2) = 96 --> Like this we access bits from address 2010 to 2013 and assign a value to it
     */

    cout << *(num1_pointer) << endl;
    cout << num1_pointer+1 << endl;
    cout << *(num1_pointer+1) << endl;
    cout << num1_pointer + 2 << endl;
    *(num1_pointer+2) = 12;
    cout << *(num1_pointer+2) << endl;
    
    short int num2 = 90;
    short int *num2_pointer = &num2;
    cout << num2_pointer << endl;
    cout << num2_pointer+1 << endl; // We will see jump of 2 bytes here since short int is of 2 bytes

    bool bool1 = true;
    bool *bool1_pointer = &bool1;
    cout << sizeof(bool1) << endl; // 1 byte
    cout << bool1_pointer << endl; // 1
    cout << bool1_pointer+1 << endl;
    *(bool1_pointer+1) = !bool1_pointer;
    cout << *(bool1_pointer+1) << endl; // 0
    cout << (*(bool1_pointer) || *(bool1_pointer+1)) << endl;

    cout << (sizeof(long int) == sizeof(int)) << endl; // 1
    cout << sizeof(long long int) << endl; // 8 uytes

    // An integer value needs 4 bytes to store the number
    // int a = 1025
    //         byte 4   byte 3   byte 2   byte 1
    // 1025 = 00000000 00000000 00000100 00000001
    //          2003    2002      2001     2000
    // cout << &a  --> 2000 is returned. The address of least significant byte is returned
    // int* p = &a;
    // cout << *p --> Start looking for 4 bytes starting from 2000

    return 0;
}