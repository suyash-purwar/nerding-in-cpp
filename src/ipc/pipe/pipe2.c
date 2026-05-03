#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

/**
 * The following program splits the array into two parts. The child and parent process parallely compute the sum of the
 * two parts. Sum from the child process is sent to the parent process and the sum is printed.
 */

int main() {
    const int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int pipe_fds[2];

    if (pipe(pipe_fds) == -1) {
        printf("Failed to create pipe\n");
        return -1;
    }

    switch (fork()) {
        case -1: {
            printf("Failed to create child process\n");
            return -1;
        }
        case 0: {
            // Child Process
            close(pipe_fds[0]);

            int second_half_sum = 0;
            for (int i = sizeof(array)/sizeof(int) / 2; i < sizeof(array)/sizeof(int); i++) {
                second_half_sum += array[i];
            }

            const ssize_t bytes_len = write(pipe_fds[1], &second_half_sum, sizeof(int));

            if (bytes_len == -1 || bytes_len != sizeof(int)) {
                printf("Failed to write to pipe\n");
                return -1;
            }

            close(pipe_fds[1]);

            break;
        }
        default: {
            // Parent Process
            close(pipe_fds[1]);

            int first_half_sum = 0;
            for (int i = 0; i < sizeof(array)/sizeof(int) / 2; i++) {
                first_half_sum += array[i];
            }

            int second_half_sum;
            ssize_t bytes_len;

            while ((bytes_len = read(pipe_fds[0], &second_half_sum, sizeof(int))) > 0) {
                if (bytes_len == -1) {
                    printf("Failed to read from pipe\n");
                    return -1;
                }
            }

            int child_status;
            wait(&child_status);

            const int sum = first_half_sum + second_half_sum;

            printf("%d: Sum is %d\n", getpid(), sum);

            close(pipe_fds[0]);

            break;
        }
    }

    return 1;
}