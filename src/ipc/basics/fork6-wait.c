#include <stdio.h>
#include <unistd.h>

/**
 * Orphan Process
 *
 * - The following code snippet creates an orphan process. The child's parent process terminates before it does.
 * - The orphaned child process gets adopted by the Kernel. PPID (Parent PID) changes to 1 from its original PPID.
 * - PID of 1 is often associated with the `init` or `systemd` process. This process becomes the new parent of the
 *   orphaned process.
 * - In the example, when the child finally finishes after 30 sec, `init` or `systemd` process will immediately reap it.
 *   Meaning it gets removed by the process table and all the resources are relinquished. It never becomes a zombie
 *   process.
 */

int main() {
    if (fork()) {
        printf("Parent completed its work\n");
    } else {
        printf("Child PPID before sleeping: %d\n", getppid());
        printf("Child is sleeping\n");
        sleep(30);
        printf("Child PPID after sleeping: %d\n", getppid()); // PPID becomes 1
        printf("Child completed its work\n");
    }

    return 0;
}