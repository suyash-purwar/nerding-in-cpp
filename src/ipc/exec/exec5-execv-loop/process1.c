#include <stdio.h>
#include <unistd.h>

/**
 * The process1.c and process2.c execute each other via execv forming an indefinite loop.
 */

int main() {
    char* const args[] = { "process2", NULL };

    printf("Executing Process 1\n");
    sleep(3);
    printf("Opening Process 2\n");

    execv("/home/vagrant/nerding-in-cpp/src/ipc/exec/exec5-execv-loop/process2", args);

    perror("Failed to execute process2");

    return 0;
}