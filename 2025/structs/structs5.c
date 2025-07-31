#include <stdio.h>

/*
 * The `pack` pragma starts aligning the struct members in memory right after the other disabling
 * the padding. It removes the padding bytes. This saves memory but comes at a cost of increased
 * CPU cycles.
 *
 * The other way to enable packing is to `__attribute__((packed))` attribute with struct declaration.
 */
// #pragma pack(1)

typedef struct {
    char ch;
    long int num;
    double num_decimal;
} A;

typedef struct {
    char ch;
    char* ch_ptr; // pointer variables takes 8 bytes
    long int num;
} B;

typedef struct {
    char ch1;
    double n1;
    char ch2;
    int* n_ptr;
} C;

// Struct with packing enabled
// Size with padding: 32 bytes
// Size without padding: 21 bytes
struct __attribute__((packed)) NoPadding {
    char x;
    long int y;
    int a;
    int *a_ptr;
};

int main() {
    printf("%zu\n", sizeof(A));
    printf("%zu\n", sizeof(B));
    printf("%zu\n", sizeof(C));

    printf("%zu\n", sizeof(struct NoPadding));
}