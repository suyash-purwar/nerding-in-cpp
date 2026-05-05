#include <stdio.h>
#include <unistd.h>

/**
 * `execl()`
 *
 * - This function belongs to an `exec` class of functions.
 * - When `execl()` is called, the new program replaces the current process image with a new program. The newer program
 *   has the same process PID.
 * - Note it does not create a new process, it overlays the current one.
 * - The "l" in `execl` stands for list. It means that you must provide arguments as comma separated list. The argument
 *   list must end with NULL.
 * - Note how the first argument is `ll` as well. It is there for a reason.
 * - In the execl function, you pass the program name (conventionally as the second argument) because it becomes argv[0]
 *   in the new process. While the first argument of execl tells the operating system which executable file to load, the
 *   second argument tells the program what it should call itself.
 * - In C, main(int argc, char *argv[]) expects argv[0] to be the name used to invoke the program. If you skip this and
 *   start with actual data arguments, the program will misinterpret your first data argument as its own name.
 *
 *   The `exec` family of functions are are as follows:
 *   - `execl`
 *   - `execlp`
 *   - `execle`
 *   - `execv`
 *   - `execvp`
 *   - `execvpe`
 */

int main() {
    printf("My Program\n");

    const int status = execl("/usr/bin/ls", "ls", "-al", NULL);

    if (status == -1) {
        perror("execl did not start\n");
    }

    printf("This should never execute\n");

    return 0;
}