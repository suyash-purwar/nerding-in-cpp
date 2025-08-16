#include <stdio.h>

void for_each(void* array, size_t n_size, size_t size, void (*operation)(void* item)) {
    for (size_t i = 0; i < size; i++) {
        void* address = (char*)array + (i * n_size);
        operation(address);
    }
}

void increment(void* item) {
    *(int*)item = *(int*)item + 1;
}

void print_arr(void* item) {
    const int value = *(int*)item;
    printf("%d ", value);
}

int main() {
    int arr[] = { 8, 49, 2, 19 };

    for_each(arr, 4, 4, increment);
    for_each(arr, 4, 4, print_arr);
}