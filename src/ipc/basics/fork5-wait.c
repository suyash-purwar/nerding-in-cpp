#include <stdio.h>
#include <unistd.h>

/**
 * Zombie Process
 *
 * - The following example creates a zombie process.
 * - It's existence can be checked by the `ps aux | grep 'Z+'` command.
 * - The `Z+` in the stat column represents a zombie process.
 *
 * How is a zombie process created?
 * - When a child process completes it's work and exits. It becomes a zombie process if its completion is not
 *   acknowledgement by the parent process using the `wait` function.
 * - When a child process finishes, it doesn't disappear completely. It stays in the system as a "zombie" (holding onto
 *   its PID and exit status) until the parent acknowledges its death. The wait() function is that acknowledgement.
 * - If the child is still running, wait() makes the parent stop and wait until the child finishes.
 * - It grabs the child's exit status (whether it finished successfully or crashed).
 * - Once wait() is called, the kernel finally removes the child process from the process table entirely.
 * - If the parent process fails to do so, the child process remains in the process table as a zombie.
 * - A process table is a core operating system data structure that tracks all active processes, using one entry (a
 *   Process Control Block or PCB) per process to manage its state, identification, and resources. It maps Process IDs
 *   (PIDs) to their corresponding PCB, storing critical data such as process state, CPU registers, memory management
 *   information, and scheduling details.
 *
 * Why is it needed to clean up the child process from Process table?
 * - Prevent PID Exhaustion: If a program creates thousands of children without wait(), the system will fill up with
 *  zombies and eventually won't be able to start any new processes.
 * - Synchronization: It ensures the parent doesn't move on until the child's task (like saving a file) is actually
 *   done.
 */

int main() {

    if (fork()) {
        printf("Parent is sleeping\n");
        sleep(30);
    } else {
        printf("Child completes it's work and exits");
    }

    return 0;
}