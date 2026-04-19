#include <stdio.h>

static char FILE_NAME[] = "sum.c";

extern int g_int;

int sum(int a, int b) {
    return a + b;
}

void print_from_other() {
    printf("%d", g_int);
}