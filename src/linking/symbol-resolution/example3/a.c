#include <stdio.h>

int x;

void some_func();

int main() {
    x = 1234;

    printf("x = %d\n", x);

    some_func();

    printf("x = %d\n", x);
}