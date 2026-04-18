#include <stdio.h>

void store_arr_item_pointer(const int *arr, int **arr_ptr, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        *(arr_ptr + i) = arr + i;
    }
}

void print_pointer_array(const int **arr, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%p --> %d\n", *(arr + i), **(arr + i));
    }
}

int main() {
    int arr[] = { 20, 59, 19, 73, 37, 0 };
    int *arr_ptr[6];

    store_arr_item_pointer(arr, arr_ptr, 6);
    print_pointer_array(arr_ptr, 6);
}