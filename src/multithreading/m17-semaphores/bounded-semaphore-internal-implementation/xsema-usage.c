#include "xsema.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N_THREADS 10
#define PERMIT_COUNTER 2

xsema_t sem;

void* worker(void* arg) {
    const int thread_id = *(int*)arg;

    int iteration = 5;
    while (iteration) {
        printf("Thread %d: Before CS\n", thread_id);

        xsema_wait(&sem);

        printf("Thread %d: Inside CS\n", thread_id);

        xsema_post(&sem);

        printf("Thread %d: After CS\n", thread_id);

        iteration--;
    }

    free(arg);

    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    xsema_init(&sem, PERMIT_COUNTER);

    for (int i = 0; i < N_THREADS; i++) {
        int* arg = malloc(sizeof(int));

        if (arg == NULL) {
            perror("Failed to allocate memory for thread argument.\n");
            exit(-1);
        }

        *arg = i;
        if (pthread_create(&threads[i], &thread_attr, worker, arg)) {
            free(arg);
            printf("Failed to create thread %d\n", i);
        }
    }

    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("Failed the join thread %d\n", i);
        }
    }

    xsema_destroy(&sem);
}