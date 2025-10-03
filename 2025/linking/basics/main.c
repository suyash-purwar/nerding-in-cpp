#include <stdio.h>

int g_int = 10;
int* g_int_ptr = &g_int;

float f1;
char a;

int main() {
    printf("Hello linking process");

    int a = 3;
    int b = 2;

    int c = sum(a, b);

    printf("%d", c);

    return 0;
}