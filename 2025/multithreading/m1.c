#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker()
{
    printf("Hello, World! from Thread\n");
    sleep(2);
    return NULL;
}

int main()
{
    pthread_t tid;

    pthread_create(&tid, NULL, worker, NULL);
    pthread_join(tid, NULL);

    printf("Hello, World! from Main\n");

    return 0;
}