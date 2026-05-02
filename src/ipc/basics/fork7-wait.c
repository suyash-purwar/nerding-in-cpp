#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * `wait()` function does not wait for all of it's direct child process to finish before unblocking the parent thread.
 * As soon as one child process completes its work and exits, the parent thread recieves the signal and resumes it's
 * execution.
 *
 * Suppose you want to wait on all child processes to complete. How would you do that?
 * The following example achieves that by calling `wait()` function in a while loop. How?
 *
 * - `wait` function returns -1 when there are no child processes left to be acknowledged. Otherwise, the pid of the
 *   terminated child process is retuned. This becomes our condition in the while loop.
 * - Keep calling `wait()` till the output is greater than 0.
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
    const int status = xfork(2);

    if (status > 0) {
        printf("%d: Waiting for child processes\n", getpid());
        int child_id;
        while ((child_id = wait(NULL)) > 0) {
            printf("%d: Completed\n", child_id);
        }
    } else if (status == 0) {
        printf("%d: Hey\n", getpid());
        sleep(3);
    } else {
        printf("Forking failed");
    }

    return 0;
}