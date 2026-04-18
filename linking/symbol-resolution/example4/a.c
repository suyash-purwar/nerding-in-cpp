#include <stdio.h>

int x = 120;
int y = 20;

void some_func();

int main() {
    printf("x = %d, y = %d\n", x, y);

    some_func();

    printf("x = %d, y = %d\n", x, y);

    return 0;
}