#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

/**
 * Named Pipes aka FIFO
 *
 * - As opposed to normal pipes, named pipes lives on the filesystem. This type of pipe exists as a file in the
 *   filesystem.
 * - Like normal pipes, names pipes are also half duplex communication mechanism.
 * - Normal pipes work across processes across same hierarchy, ie, between parent and child processes. Named pipes can
 *   be used between completely unrelated processes. It's free of parent-child relationship and is IPC in true sense.
 * - With normal pipes, file descriptors are shared by forking the process. With named pipes, you have to pass the path
 *   of the file.
 *
 *   Process A        /tmp/my_pipe        Process B
 *   write   ───────>  [ KERNEL ] ───────> read
 *
 * - As opposed to normal pipes, the file descriptors need to be explicitly opened in the case of named pipes.
 * - There's an important condition to opening named pipes:
 *     - Opening the read or write end of a FIFO blocks until the other end is also opened (by another process or
 *     thread).
 *     - An attempt to open named pipe in O_RDONLY mode will block unless there's another process or thread that has
 *     opened the pipe in writer mode (O_WRONLY or equivalent).
 *     - Similarly, an attempt to open named in O_WRONLY model will block unless there's another process or thread that
 *     has opened the pipe in read mode (O_RDONLY or equivalent)
 *
 * Process Synchronisation Mechanism
 * - Named pipes (FIFOs) provide process synchronisation by acting as a blocking, FIDO communication channel, ensuring
 *   that reader and writer processes synchronize their actions. A reading process blocks until a writer opens the pipe,
 *   and a writer blocks until a reader is ready, facilitating ordered communication without requiring manual locking
 *   mechanisms.
 * - The primary synchronisation feature is that open() calls on a Named Pipe (created with mkfifo()) block by default
 *   until both ends (reading and writing) are opened.
 * - If a process attempts to read from an empty pipe, it is blocked until data is written, and conversely, if the
 *   pipe's buffer is full, the writer blocks until space is available. This is same as normal pipe.
 *
 * What about O_RDWR mode:
 *    - Opening the pipe with O_RDWR will not block as the same process can be the reader and writer.
 *    - With this mode, process can write to fd and can consume it later on. It is useless though.
 *
 * Non-Blocking Named Pipe (O_NONBLOCK)
 *    - With this mode, the `open("my_pipe", O_WRONLY | O_NONBLOCK)` call wouldn't block if there are no readers.
 *    - Instead it would fail with exit status ENXIO
 *    - Similarly, it wouldn't block if the call `open("my_pipe", O_RDONLY | O_NONBLOCK)` is made with no writers.
 *
 * The following program indefinitely block unless there's a reader process as well. Here's a simple way to test this:
 * - Run this program
 * - In a different terminal, write `cat pipe3-named-fifo`. This opens the named pipe in reader mode, allowing the
 *   writer to unblock and write.
 * - The command would print "Suyash" as it was written by this program there.
 *
 * One more exercise to check the named pipe opening behaviour:
 * - `mkfifo new-pipe-1`: Create a new pipe in cmd.
 * - `cat new-pipe-1`: Start the reader process on this pipe. It would block as there is no writer.
 * - `echo "Entry into named pipe" > new-pipe-1`: Run in different terminal. This starts a writer process and writes to
 *   the pipe. This unblocks the reader process and the string in printed.
 */

int main() {
    printf("PID: %d\n", getpid());

    if (mkfifo("pipe3-named-fifo", 0777) == -1) {
        if (errno != EEXIST) {
            perror("Failed to create fifo pipe\n");
            return -1;
        }
    }

    int fd;
    if ((fd = open("pipe3-named-fifo", O_WRONLY)) < 0) {
        perror("Failed to open named pipe\n");
        return -1;
    }

    printf("FD is open: %d\n", fd);

    const char* name = "Suyash";
    const ssize_t bytes_len = write(fd, name, strlen(name));

    if (bytes_len == -1 || bytes_len != strlen(name)) {
        perror("Failed to write in the pipe\n");
    }

    return 1;
}
