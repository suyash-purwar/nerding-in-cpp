#include <stdio.h>

#define hey "HEY\n"

#define print printf

#define area_of_triangle(base, height) (0.5 * base * height)

#define min(x, y) (x > y ? x : y)

/**
 * "#" is called Stringizing operator
 * It is used with macros
 * Whatever value is received as the parameter
 * It gets converted to a string
 */
#define string_op(x) print(#x)

#define find_max(arr, len) ({                  \
    long long max = arr[0];                    \
    for (size_t i = 1; i < len; i++) {         \
        if (arr[i] > max) {                    \
            printf("%ld", max);                \
            max = arr[i];                      \
        }                                      \
    }                                          \
    max;                                       \
})

int main() {
    printf(hey);
    print(hey);

    /**
     * Functional Macros work like generics.
     * In the following statements, different data types are used
     * with same function.
     */
    int area1 = area_of_triangle(40, 90);
    float area2 = area_of_triangle(3.2, 1.1);

    printf("%d\n", area1);
    printf("%f\n", area2);

    int min1 = min(3, 4);
    printf("min1: %d\n", min1);

    int min2 = min(min(5, 6), min(0, 1));
    printf("min2: %d\n", min2);

    /**
     * Text replacement for above statement
     * => min((5 > 6 ? 5 : 6) > (0 > 1 ? 0 : 1))
     * => ((5 > 6 ? 5 : 6) > (0 > 1 ? 0 : 1) ? (5 > 6 ? 5: 6) : (0 > 1 ? 0 : 1))
     *
     * Above is the expanded expression for line 29.
     */

    string_op(hello world\n);

    const int arr[] = {30, 3, 0, -2, 31};
    int max = find_max(arr, 5);

    print("%d\n", max);

    return 0;
}