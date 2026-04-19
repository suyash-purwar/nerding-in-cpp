#include <stdio.h>
#include <stdint.h>

int64_t add(int64_t a, int64_t b) {
    return a + b;
}

int64_t sub(int64_t a, int64_t b) {
    return a - b;
}

int main_alt() {
    return 0;
};

int main() {
    const char* string = "static";

    printf("%p\n", string);
    printf("%p\n", main);

    int64_t (*func_ptr)(int64_t, int64_t) = &add;
    printf("3 + 5 = %ld\n", func_ptr(3, 5));
    func_ptr = &sub;
    printf("3 - 5 = %ld\n", func_ptr(3, 5));
}