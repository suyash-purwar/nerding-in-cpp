#include <stdio.h>
#include <unistd.h>

int main() {
    char* const args[] = { "process1", NULL };

    printf("Executing Process 2\n");
    sleep(3);
    printf("Opening Process 1\n");

    execv("/home/vagrant/nerding-in-cpp/src/ipc/exec/exec5-execv-loop/process1", args);

    perror("Failed to execute process1./");

    return 0;
}