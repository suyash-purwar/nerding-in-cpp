#include <stdio.h>
#include <stdbool.h>

#include "str.h"

void pstr(const char* str, const bool newline) {
    printf("%s", str);

    if (newline == true) {
        printf("\n");
    }
}