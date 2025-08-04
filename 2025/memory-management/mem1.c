#include <stdio.h>
#include <stdlib.h>

char* fill_lowercase(char *str, size_t length) {
    if (length > 26) {
        length = 26;
    }

    for (int i = 0; i < length; i++) {
        str[i] = 'a' + i;
    }

    str[length] = '\0';

    return str;
}

char* string_malloc(const size_t size) {
    char* str = (char*)malloc(size);

    if (str == NULL) {
        printf("%s\n", "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++) {
        str[i] = '\0';
    }

    return str;
}

int main() {
    char *str1 = string_malloc(23);
    char *str2 = string_malloc(26);
    char *str3 = string_malloc(40);

    fill_lowercase(str1, 23);
    fill_lowercase(str2, 26);
    fill_lowercase(str3, 40);

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);

    free(str1);
    free(str2);
    free(str3);

    return 0;
}