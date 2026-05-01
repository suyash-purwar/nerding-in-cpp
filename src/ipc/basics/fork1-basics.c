#include <stdio.h>
#include <unistd.h>

/**
 * The fork system call clones the current process. It starts a parallel line of execution. All the process resources
 * are copied and a new process is created.
 *
 * Fork returns -1 when the cloning fails.
 * In the context of parent process, the returned id is the process id of the child process
 * In the context of child process, the returned id is 0.
 *
 * It can be used to identify whether a process is a child or not.
 */

int main() {
    const int id = fork();

    if (id == 0) {
        printf("Hello World from Child Process\n");
    } else {
        printf("Hello World from Parent Process\n");
        printf("PID of child process: %d\n", id);
    }

    return 0;
}