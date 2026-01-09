#include <stdio.h>
#include <pthread.h>

/**
 * Program that reads latter half of the file
 *
 * The `fseek()` function is used to change position the file reading pointer in the file.
 * The `ftell()` function tells the position of file reading pointer from the start of file.
 */

int file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

int main()
{
    FILE *file1 = fopen("./files/sample2.txt", "r");

    int fsize = file_size(file1);
    printf("File size is %d\n", fsize);

    char buffer[256];

    fseek(file1, fsize / 2, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), file1) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file1);

    return 0;
}