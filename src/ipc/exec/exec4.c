#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

/**
 * `execvpe`
 *
 * - Signature: `int execvpe(const char *file, char *const argv[], char *const envp[]);`
 * - The "e" in "execvpe" stands for environment.
 * - envp[]: A NULL-terminated array of strings of the form key=value, representing the environment for the new process.
 * - To use it on Linux, you must define #define _GNU_SOURCE before including <unistd.h>
 */

int main() {
    char* const args[] = { "ls", "-alh", NULL };
    char* const envs[] = { "USER=guest", "API_KEY=zhliefew", NULL };

    const int status = execvpe("ls", args, envs);

    if (status == -1) {
        perror("execvp did not start");
    }

    printf("This should never print\n");

    return 0;
}