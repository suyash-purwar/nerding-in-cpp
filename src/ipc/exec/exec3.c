#include <stdio.h>
#include <unistd.h>

/**
 * `execvp`
 *
 * - The "p" in "execvp" stands for path.
 * - Notice how the full path of `ls` executable is not provided. It is because `execvp` function searches through the
 *   system's PATH variable.
 */

int main() {
    char* const args[] = { "ls", "-alh", NULL };
    const int status = execvp("ls", args);

    if (status == -1) {
        perror("execvp did not start");
    }

    printf("This should never print\n");

    return 0;
}