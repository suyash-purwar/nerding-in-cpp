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

    const int fd = open(NAMED_PIPE, O_RDONLY);

    if (fd == -1) {
        perror("Failed to open fd");
        return -1;
    }

    int sum = 0;
    while (1) {
        srand(time(NULL));
        int n;

        const ssize_t bytes_read = read(fd, &n, sizeof(int));

        if (bytes_read == -1) {
            printf("Failed to read from the named pipe\n");
            return -1;
        }

        if (bytes_read == 0) {
            printf("Reader %d: Writer closed\n", pid);
            printf("Reader %d: Final sum %d\n", pid, sum);
        } else {
            sum += n;
            printf("Reader %d: Read %d\n", pid, n);
            printf("Reader %d: Sum is %d\n", pid, sum);
        }

        sleep(5);
    }

    close(fd);

    return 0;
}