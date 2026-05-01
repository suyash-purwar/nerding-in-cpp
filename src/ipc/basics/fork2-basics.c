#include <stdio.h>
#include <unistd.h>

/**
 * The following two calls to the fork() will create three cloned child processes. In total, there will be four processes
 * including the parent process. Because of this "After forking" is printed four times.
 *
 * No. of processes running = 2 ^ (no. of times fork is called)
 */

int main() {
    printf("Before forking\n");

    fork();
    fork();

    printf("After forking\n");

    return -1;
}