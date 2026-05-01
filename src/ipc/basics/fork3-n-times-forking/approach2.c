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
 * - Using the `getpid` function's return value to bifurcate between parent and child process and forking conditionally.
 */


int xfork(const int times) {
    const int parent_pid = getpid();

    for (int i = 0; i < times; i++) {
        if (parent_pid == getpid() && fork() > 0) {}
        else if (parent_pid == 0)
            return 0;
        else
            return -1;
    }

    return 1;
}

int main() {
    printf("Parent pid: %d\n", getpid());

#if 1
    xfork(4); // Creates 4 new cloned processes. Including parent, total process count is 5.
#else
    // const int parent_pid = getpid();
    // int child_process_id;
    //
    // if (getpid() == parent_pid && (child_process_id = fork())) {
    //     printf("First fork => PID: %d | Parent PID: %d\n", child_process_id, getppid());
    // }
    //
    // if (getpid() == parent_pid && (child_process_id = fork())) {
    //     printf("Second fork => PID: %d | Parent PID: %d\n", child_process_id, getppid());
    // }
    //
    // if (getpid() == parent_pid && (child_process_id = fork())) {
    //     printf("Third fork => PID: %d | Parent PID: %d\n", child_process_id, getppid());
    // }
    //
    // if (getpid() == parent_pid && (child_process_id = fork())) {
    //     printf("Fourth fork => PID: %d | Parent PID: %d\n", child_process_id, getppid());
    // }
#endif

    printf("After forking\n");
    sleep(1);

    return 0;
}