#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * The wait() system call suspends a parent process's execution until one of its child processes terminates or changes
 * state. It is used for process synchronization, ensuring the parent waits for the child to finish, and to reap zombie
 * processes to prevent resource leaks, returning the terminated child's PID and status
 *
 * On `wait` function
 * - When a parent process calls `wait`, it gets blocked until one of its direct child process completes it's work.
 * - Note that it does not wait for all direct child processes to complete its work. Completion of one direct child
 *   process is enough to unblock the parent process and continue its execution.
 * - The exit status of the child process can be accessed using this method.
 * - Exit status is a message from the child process to the parent process on how it ended. It tells you whether the
 *   process exited normally, or was it killed by a signal and by what signal.
 * - It can be used to achieve process synchronisation among parent and child threads.
 *
 * Following is an example of basic thread synchronisation.
 * - Parent process and one child process need to print from 1 to 10 in ascending order. Parent thread prints from 6 to
 *   10 and child thread prints 1 to 5.
 * - Without thread synchronisation, the order of numbers can become wrong.
 * - The following program ensures that child threads prints 1 to 5 first before the parent thread can print 6 to 10
 *   using that wait function.
 * - Child process is made to sleep for a second to consistently the simulate of parent process completing its work
 *   first. It leads to 6 to 10 printing first if the `wait` function is commented out.
 * - `wait` enforces that a child processes finishes it's work
 *
 * What `wait` does internally
 * - When a child process finishes, it doesn't disappear completely. It stays in the system as a "zombie" (holding onto
 *   its PID and exit status) until the parent acknowledges its death. The wait() function is that acknowledgment.
 */

int main() {
    const pid_t id = fork();

    if (id == -1) return -1;

    if (!id) {
        printf("Child Id: %d | Parent Id: %d\n", getpid(), getppid());
        sleep(1); // Simulating slow child process
    } else {
        printf("Parent Id: %d | Parent Id: %d\n", getpid(), getppid());
    }

    if (id > 0) {
        int child_status;
        wait(&child_status);
    }

    if (id) {
        // Parent
        for (int i = 6; i <= 10; i++) {
            printf("%d ", i);
            fflush(stdout);
        }
    } else {
        // Child
        for (int i = 1; i <= 5; i++) {
            printf("%d ", i);
            fflush(stdout);
        }
    }

    if (id)
        printf("\n");

    return 1;
}
