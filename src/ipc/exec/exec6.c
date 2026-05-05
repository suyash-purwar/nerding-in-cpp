#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * - It is often required to extract the results of a process running via `exec` functions.
 * - But, we know that it completely replaces the ongoing program and becomes a different executable.
 * - To help with this problem, a different program can be executed in a child process. It's exit status and return can
 *   be obtained through the `wait` function
 */

int main() {
    switch (fork()) {
        case -1: {
            perror("Failed to fork");
            return -1;
        }
        case 0: {
            const pid_t child_pid = getpid();
            printf("Child %d: Started\n", child_pid);

            char* const args[] = { "ls", "-alh", NULL };

            printf("Child %d: ls starts in the child process\n", child_pid);

            execvp("ls", args);

            perror("Failed to open ls");
            return -1;
        }
        default: {
            const pid_t parent_pid = getpid();

            printf("Parent %d: Started\n", parent_pid);
            printf("Parent %d: Waiting for child process to complete\n", parent_pid);

            int exit_status;
            int return_value;
            wait(&exit_status);

            if (WIFEXITED(exit_status)) {
                return_value = WEXITSTATUS(exit_status);
            }

            printf("Parent %d: Child got %d", parent_pid, return_value);
        }
    }
}