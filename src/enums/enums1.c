#include <stdio.h>
#include <string.h>

enum Class {
    UNKNOWN = -1,
    FIRST,
    SECOND,
    THIRD
};

const char* classNames[] = {
    "First",
    "Second",
    "Third"
};

enum Class print_class(char* className) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(className, classNames[i]) == 0) {
            return i;
        }
    }

    return UNKNOWN;
}

int main() {
    char* className1 = "Second";
    enum Class c1 = print_class(className1);
    printf("%i\n", c1);
    printf("%s\n", classNames[c1]);

    char* className2 = "Suyash";
    enum Class c2 = print_class(className2);
    printf("%i", c2);

    return 0;
}