#include <stdio.h>
#include <unistd.h>

/**
 * `execv`
 *
 * - It takes the arguments as a list rather than comma-separated arguments.
 */

int main() {
    const char* args[] = { "ls", "-alh", NULL };
    const int status = execv("/usr/bin/ls", args);

    if (status == -1) {
        perror("execv did not start");
    }

    printf("This should never print\n");

    return 0;
}
