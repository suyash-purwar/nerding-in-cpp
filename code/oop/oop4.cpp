#include<iostream>
// #pragma pack(1)

using std::cin;
using std::cout;
using std::endl;

/**
 * int - 4 bytes
 * short int - 2 bytes
 * char - 1 bytes
 * double - 8 bytes
 */

/** 
 * My system is of 64 bytes and each cpu cycle reads 4 bytes from the memory and the writes in the memory are done accordingly to increase data captured per cycle.
 */

/**
 * Instance of this class would consume 4 bytes of memory
 * Memory consumption by the instance of an object or structure depends on the size of the data members (properties), sequence of the declaration of data members.
 */

class A {
    int a;
};

/**
 * It may seem that this would contain 1 + 4 + 1 = 6 bytes but this would consume 12 bytes.
 * Learn the concept of Structure Padding to better understand the behavious. Below is the summary.
 * I have a cpu cycle of 4 bytes. This means my system would read and write 4 bytes in one go from the memory
 * When it comes to write, it would write 4 bytes at a time.
 * Even though 'char a' actually consumes only 4 bytes but since my system writes 4 bytes at a time, it would append three more bytes. So, in total it become 4 byte.
 * 'int b' consumes 4 bytes. So, it would completely fills the 4 bytes written in one cycle. Therefore, there are padding bytes here.
 * 'char c' would again consume 4 bytes.
 * Hence, total memory consumption is 4 + 4 + 4 = 12 bytes
 */
class B {
    char a;
    int b;
    char c;
};

/**
 * Now, the instance of the below written class should also consume 12 bytes.
 * Nope, it contains 8 bytes only!
 * 'char a' writes 4 bytes. 1 byte of actual data + 3 padding bytes
 * Now, if you look closely, 'char b' which also consumes 1 byte, can be accomodated in the 3 padding bytes of the 'char a'.
 * So, it gets accomodated there only. Therefore, there are 2 bytes of actual data and 2 padding bytes.
 * 'int b' consumes 4 bytes, it no longer can be accomodated in the 2 padding bytes. So, it takes 4 bytes of next cpu cycle.
 * Hence, total memory consumption is 4 + 4 = 8 bytes
 */

/**
 * Through the example of class B and class C, it is evident that the sequence of data member declaration plays an important role in the memory consumption.
 * To reduce memory usage, data members should be declaraed either in the increasing or decreasing order of the memory consumption of each data member.
 * class C and B has same data members but defined in different order.
 * class B follows no sequence and in-total consumption is of 12 bytes
 * class C defines the data members in increading order of memory consumption by data members.
 */
class C {
    char a;
    char c;
    int b;
};

/**
 * In first cpu cycle,
 * 4 bytes get occupied by 'double d'.
 * Since, 'double d' consumes 8 bytes, the next set of 4 bytes would get stored in the next cpu cycle.
 * Two cpu cycles are completely filed, third one will start
 * Summation of memory consumed 'short int', 'char b', and 'char c' is 4 bytes. So, all three will be stored in the third cpu cycle
 * Hence, total memory consumption should be 4 + 4 + 4 = 12 bytes
 * But it is 16 bytes! I don't know why :(
 */

class D {
    double d;
    short int a;
    char b;
    char c;
};

/**
 * Padding increases the performance of the program but uses more memory memory.
 * Better usage of memory can be traded with relatively poor performance by disabling Padding.
 * When Padding is disabled, data members are stored right next to each other with no padding bytes which saves the memory.
 * When this is done, it is called Packing or Greedy.
 * Remember, Packing has impact on the performance.
 * To disable padding, write '#pragma pack(1)'.
 */

/**
 * Class E has no data members. So, it should occupy no space in the memory.
 * But it does.
 * Empty class with no properties and methods occupy 1 byte of memory.
 * Compiler does this to signify the presence of the class
 */
class E {

};

int main() {
    A a;
    B b;
    C c;
    D d;
    E e;

    cout << "Size of A: " << sizeof(a) << endl;
    cout << "Size of B: " << sizeof(b) << endl;
    cout << "Size of C: " << sizeof(c) << endl;
    cout << "Size of D: " << sizeof(d) << endl;
    cout << "Size of E: " << sizeof(e) << endl;

    return 0;
}