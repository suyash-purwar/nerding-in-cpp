#include <stdio.h>
#include <math.h>

#define BYTE_SIZE 8
#define MAX_INT_VALUE ((pow(2, sizeof(int) * BYTE_SIZE) / 2) - 1)
#define MAX_LONG_VALUE ((pow(2, sizeof(long) * BYTE_SIZE) / 2) - 1)

int main() {
    int a = MAX_INT_VALUE;
    long b = MAX_LONG_VALUE;

    printf("Maximum value of int: %d\n", a);
    printf("Maximum value of long: %ld\n", b);

    void *ptr = &a;

    // We cannot dereference a void pointer because it does not have type information
    // It does not know how many bytes to read
    // printf("%d", *ptr);

    // We can cast the void pointer to some other data type pointer and then dereference it.
    // For example:
    printf("%d\n", *(int*)ptr);

    // Essentially, we've asked the compiler to read the 4 bytes here

    ptr = &b;
    printf("%ld\n", *(long*)ptr); // Reading 8 bytes
    printf("%d\n", *(int*)ptr); // Reading 4 bytes of 8 byte data
    // The above statement prints -1 as the last 4 bytes are all 1
    // -1 = 11111111 11111111 11111111 11111111

    // A NICE TRICK
    long special_long = 9223372034707292159;
    // Binary representation = 01111111 11111111 11111111 11111111 01111111 11111111 11111111 11111111
    void* special_long_v_ptr = &special_long;

    printf("%ld\n", *(long*)special_long_v_ptr);
    printf("%d\n", *(int*)special_long_v_ptr); // Here I am reading the last 4 bytes only.
    // If you notice the last 4 bytes, they are all 1 except the MSB.
    // Which means the last 4 bytes are representing the maximum value of integer.
    printf("%d\n", *(int*)special_long_v_ptr == MAX_INT_VALUE);

    // Essentially what I've done is read a variable's value partially.
    // It's like reading the value of a variable but only half of it.
    // This partial value is also a value.
}