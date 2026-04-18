#include <stdio.h>
#include <sys/stat.h>

/**
 * `sys/stat.h` header has functions like state, chmod, mkdir, lstat, fstat, among others.
 * The `stat` functions is used to pull information about a file/directory from the OS. This does not open the file
 * to collect this data. It is saved in the OS and it pulls it from there.
 */

int main()
{
    struct stat file_stats;

    if (stat("./files/sample2.txt", &file_stats) == 0)
    {
        printf("File size: %ld\n", file_stats.st_size);
        printf("Last modified: %ld\n", file_stats.st_mtime);
        printf("Mode: %d\n", file_stats.st_mode);
    }

    return 0;
}