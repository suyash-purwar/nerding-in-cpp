#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

#define NAMED_PIPE "pipe4-named-fifo"

int main() {
    const int pid = getpid();

    if (mkfifo(NAMED_PIPE, 0777) == -1) {
        if (errno != EEXIST) {
            perror("Failed to create the named pipe");
            return -1;
        }
    }

    const int fd = open(NAMED_PIPE, O_WRONLY);

    if (fd == -1) {
        perror("Failed to open fd");
        return -1;
    }

    while (1) {
        srand(time(NULL));
        const int n = rand() % 100;

        const ssize_t bytes_written = write(fd, &n, sizeof(int));

        if (bytes_written == -1 || bytes_written != sizeof(int)) {
            printf("Failed to write to the named pipe\n");
            return -1;
        }

        printf("Writer %d: Written %d\n", pid, n);

        sleep(5);
    }

    close(fd);

    return 0;
}