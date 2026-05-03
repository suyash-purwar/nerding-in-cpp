#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_LEN 64

/**
 * Pipes are one of the IPC mechanism through which two process can unidirectionally communicate with each other.
 * On the two ends of a pipe, we have a reader and writer process. One end of the pipe is for reading the data and other
 * is for writing it.
 *
 * A pipe creates two file descriptors - one for reading, and one for writing.
 * The kernel maintains an internal buffer for the pipe, which acts as a data channel between processes.
 *
 * Call signature
 * - `pipe(int fds[2])`: Opens the two file descriptor
 * - fds[0] is the read file descriptor
 * - fds[1] is the write file descriptor
 *
 * This internal buffer size is limited. If this memory is filled up by the writing process, further writes will be
 * blocked until data is read from the pipe.
 *
 * Pipe's buffer size is kernel-dependent and configurable via `fcntl` function.
 * Older kernels limited pipe buffer size to 4 KB. Modern kernels generally have 64 KB size. It can be expanded upto
 * the max supported capacity.
 * The max supported pipe buffer size can be checked via this command: `cat proc/sys/fd/pipe-max-size`.
 *
 * Program Flow
 * - At line 33, two file descriptors are ready to be used. So far, there is only one process which has read and write
 *   descriptors ready.
 * - At line 40, the `fork` function is invoked and a child process is born with same resources and memory of parent
 *   process. Child process gets a copy of the file descriptors present in the parent process.
 * - We have 4 file descriptors, pointing to 2 underlying shared kernel objects, belonging to 1 pipe.
 * - After `fork()`, the pipe can now be visualized as:
 *
 *                 read   <---- ---------- <---- write
 *    Parent                       pipe                      Child
 *                 write  ----> ---------- ----> read
 *
 * - Here, both parent and child inherit copies of the pipe’s file descriptors. This means both processes can read and
 *   write, which is usually not desired. With this setup, parent can write and read its own message which is pointless.
 *
 * - This brings us to the most important considerations when using a pipe — closing pipe file descriptors.
 * - Closing pipe file descriptors not only releases resources back to the kernel but more importantly, closing a pipe
 *   fd specifies intent.
 *
 * - To establish a clear communication direction:
 *     - The writer closes its read end
 *     - The reader closes its write end
 *
 * - Suppose, we want Parent to be writer process and Child to be the reader process.
 * - For Parent, we will close the reader file descriptor
 * - For Child 2, we will close the writer file descriptor
 * - Now, the pipe can be visualized as follows:
 *
 *                             ----------
 *    Parent    write  ---->      pipe       ----> read    Child
 *                             ----------
 *
 * - Note that this is crucial not just for resource cleanup, but for correctness:
 *     - read() returns 0 (EOF) only when all write ends are closed
 *     - if any process still has the write end open, readers will block indefinitely
 *     - By closing these descriptors, you ensure that the reference count for the write-end drops to zero the moment
 *       the actual writer is finished. This is the only way the reader’s while(read(...) > 0) loop will ever gracefully
 *       terminate.
 *
 * - Following is walkthrough of problem with read and write fds open on both sides:
 * - The read() system call is designed to block if the pipe is empty but writers still exist.
 *    - The Problem: If the child is reading and the parent is writing, but the child also still has its own copy of
 *      the write-end open, the read() call will never return 0 (EOF).
 *    - The Result: The child will hang forever, waiting for "itself" to write something, even after the parent has
 *      finished and exited.
 * - Conversely, if a process attempts to write() to a pipe that has no active readers:
 *    - The kernel determines there is no "consumer" for this data.
 *    - It sends a SIGPIPE signal to the writer and sets errno to EPIPE.
 *    - Without closing the unused read-end in the writer process, the kernel thinks a reader could still exist, and the
 *      writer might continue wasting cycles pumping data into a void.
 *
 * Atomic Write Limit (PIPE_BUF) in Pipes
 *
 * - On Linux, this is 4096 bytes. Writes of this size or smaller are guaranteed to be atomic, meaning they won't be
 *   interleaved with data from other processes.
 * - As long as your message is smaller than or equal to this limit, the kernel treats it as a single, solid block of
 *   data.
 * - The Interleaving Problem
 *    - Scenario A: Small Writes (Atomic)
 *       - Process A writes: "HELLO" (5 bytes)
 *       - Process B writes: "WORLD" (5 bytes)
 *       - Result: The reader will always see either "HELLOWORLD" or "WORLDHELLO". The words stay intact.
 *    - Scenario B: Large Writes (Non-Atomic)
 *       - Process A tries to write a massive 10,000-byte buffer.
 *       - Process B tries to write a massive 10,000-byte buffer.
 *       - Result (Interleaving): Because the writes exceed 4096 bytes, the kernel might grab the first 4KB from
 *         Process A, then swap to Process B and grab 4KB of its data, then go back to A.
 *       - The reader receives a "garbled" mess of mixed data that is useless because the individual messages have been
 *         sliced and woven together.
 */

int main() {
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        printf("Failed to create pipe\n");
        return -1;
    }

    switch (fork()) {
        case -1: {
            printf("Failed to fork\n");
            return -1;
        }
        case 0: {
            // Child Process
            const pid_t child_pid = getpid();
            printf("Child %d: Started\n", child_pid);
            close(pipe_fds[1]);

            char buffer[BUFFER_LEN];

            ssize_t len;
            while ((len = read(pipe_fds[0], buffer, BUFFER_LEN)) > 0) {
                if (len == -1) {
                    printf("Failed to read from pipe\n");
                    return -1;
                }
            }

            close(pipe_fds[0]);

            printf("Child %d: %s\n", child_pid, buffer);

            return 0;
        }
        default: {
            // Parent Process
            const pid_t parent_pid = getpid();
            printf("Parent %d: Started\n", parent_pid);
            close(pipe_fds[0]);

            const char string[BUFFER_LEN] = "Hello from other process\n";

            const ssize_t len = write(pipe_fds[1], string, strlen(string));

            /*
             * Uncomment `sleep` and run the following to check for new File Descriptors in child and parent process
             * cd /proc
             * ls -l <child_pid or parent_pid>/fd
             */
            // sleep(120);

            close(pipe_fds[1]);

            if (len == -1) {
                printf("Failed to write to pipe\n");
                return -1;
            }

            if (len != strlen(string)) {
                printf("Failed to write complete string\n");
                return -1;
            }

            printf("Parent %d: Wrote to pipe\n", parent_pid);

            wait(NULL);

            return 0;
        }
    }

    return 0;
}