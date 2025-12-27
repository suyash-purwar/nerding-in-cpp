#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker1()
{
    printf("Thread1 worker\n");
    sleep(2);
    return NULL;
}

void* worker2(void* arg) {
    char* str = (char*)arg;

    while (1) {
        printf("%s\n", str);
        sleep(1);
    }
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, worker1, NULL);
    pthread_join(tid1, NULL);

    static char* string = "Thread2 worker";
    pthread_create(&tid2, NULL, worker2, (void*)string);

    printf("Main thread\n");

    sleep(10);

    return 0;
}