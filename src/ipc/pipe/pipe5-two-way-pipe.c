#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void setup_parent_process_pipes(const int* fd_ptoc, const int* fd_ctop) {
    close(fd_ptoc[0]);
    close(fd_ctop[1]);
}

void close_parent_process_pipes(const int* fd_ptoc, const int* fd_ctop) {
    close(fd_ptoc[1]);
    close(fd_ctop[0]);
}

void setup_child_process_pipes(const int* fd_ptoc, const int* fd_ctop) {
    close(fd_ptoc[1]);
    close(fd_ctop[0]);
}

void close_child_process_pipes(const int* fd_ptoc, const int* fd_ctop) {
    close(fd_ptoc[0]);
    close(fd_ctop[1]);
}

int main() {
    int fd_ptoc[2];
    int fd_ctop[2];

    if (pipe(fd_ptoc) == -1) {
        perror("Failed to create parent to child pipe\n");
        return -1;
    }

    if (pipe(fd_ctop) == -1) {
        perror("Failed to create child to parent pipe\n");
        return -1;
    }

    const int data = 5;
    int result;

    switch (fork()) {
        case -1: {
            perror("Failed to fork\n");
            return -1;
        }
        case 0: {
            // Child Process
            const pid_t child_pid = getpid();
            printf("Parent %d: Started\n", child_pid);

            setup_child_process_pipes(fd_ptoc, fd_ctop);

            int read_data;

            const ssize_t bytes_read = read(fd_ptoc[0], &read_data, sizeof(int));

            if (bytes_read == -1) {
                printf("Child process failed to read from pipe\n");
                close_child_process_pipes(fd_ptoc, fd_ctop);
                return -1;
            }

            printf("Child %d: Read data from pipe - %d\n", child_pid, read_data);

            const int new_data = read_data * 100;

            const ssize_t bytes_written = write(fd_ctop[1], &new_data, sizeof(int));

            if (bytes_written == -1 || bytes_written != sizeof(int)) {
                printf("Child process failed to write to pipe\n");
                close_parent_process_pipes(fd_ptoc, fd_ctop);
                return -1;
            }

            printf("Child %d: Wrote data to pipe - %d\n", child_pid, new_data);

            close_child_process_pipes(fd_ptoc, fd_ctop);
            break;
        }
        default: {
            // Parent Process
            const pid_t parent_pid = getpid();
            printf("Parent %d: Started\n", parent_pid);

            setup_parent_process_pipes(fd_ptoc, fd_ctop);

            const ssize_t bytes_written = write(fd_ptoc[1], &data, sizeof(int));

            if (bytes_written == -1 || bytes_written != sizeof(int)) {
                printf("Parent process failed to write to pipe\n");
                close_parent_process_pipes(fd_ptoc, fd_ctop);
                return -1;
            }

            printf("Parent %d: Wrote data to pipe - %d\n", parent_pid, data);

            const ssize_t bytes_read = read(fd_ctop[0], &result, sizeof(int));

            if (bytes_read == -1) {
                printf("Child process failed to read from pipe\n");
                close_parent_process_pipes(fd_ptoc, fd_ctop);
                return -1;
            }

            printf("Parent  %d: Read data from pipe - %d\n", parent_pid, result);

            wait(NULL);

            close_parent_process_pipes(fd_ptoc, fd_ctop);
            break;
        }
    }

    return 0;
}