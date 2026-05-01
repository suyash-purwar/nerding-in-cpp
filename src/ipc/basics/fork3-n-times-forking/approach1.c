#include <stdio.h>
#include <unistd.h>

/**
 * Problem statement: Clone the process 4 times.
 *
 * Total number of running processes = 4 + 1 = 5
 * We know, no. of process = 2 ^ (no. of times fork is invoked)
 * There is no exponent which would result in: 2^n = 5
 *
 * The approach to fix this problem is by controlling the forking behaviour. The core idea is to prevent child processes
 * from forking itself. Only parent process will do the forking. The following program creates 5 instances of the
 * process.
 *
 * Core points
 * - Idea is to fork only from the top-level parent process.
 * - Using the `fork` function's return value and nesting to fork n times from the parent process.
 */

int xfork(const int times) {
    if (times <= 0) return 1;

    const int child_process = fork();

    if (child_process > 0)
        return xfork(times - 1);

    if (child_process == 0) {
        return 0;
    }

    return -1;
}


int main() {
    printf("Parent pid: %d\n", getpid());

#if 1
    xfork(4); // Creates 4 new cloned processes. Including parent, total process count is 5.
#else
    // Following is an expanded version of the `xfork` function to understand the approach better
    printf("First fork | Child Process id: %d | Parent Process id: %d\n", getpid(), getppid());
    const int fork_id1 = fork();

    if (fork_id1 != 0) {
        printf("Second fork | Child Process id: %d | Parent Process id: %d\n", fork_id1, getpid());
        const int fork_id2 = fork();

        if (fork_id2 != 0) {
            printf("Third fork | Child Process id: %d | Parent Process id: %d\n", fork_id2, getpid());
            const int fork_id3 = fork();

            if (fork_id3 != 0) {
                printf("Fourth fork | Child Process id: %d | Parent Process id: %d\n", fork_id3, getpid());
                fork();
            }
        }
    }
#endif

    printf("After forking\n");
    sleep(1);

    return 0;
}
