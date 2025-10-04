#include <stdio.h>
#include <stdbool.h>

#include "math.h"
#include "str.h"

int main() {
    const int x = 10, y = 94;

    const int sum = add(x, y);
    const int into = mul(x, y);

    printf("sum = %d\n", sum);
    printf("into = %d\n", into);

    const char* str1 = "I am Android";

    pstr(str1, true);
}