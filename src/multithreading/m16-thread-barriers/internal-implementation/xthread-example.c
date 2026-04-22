#include "xthread_barrier.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define N_THREADS 6

xthread_barrier_t barrier;

void* worker_fn(void* arg) {
    const int thread_n = *(int*)arg;

    printf("Thread %d waiting at barrier 1\n", thread_n);

    xthread_barrier_wait(&barrier);

    printf("Thread %d passed barrier 1\n", thread_n);

    sleep(2);

    printf("Thread %d waiting at barrier 2\n", thread_n);

    xthread_barrier_wait(&barrier);

    printf("Thread %d passed barrier 2\n", thread_n);

    free(arg);

    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    xthread_barrier_init(&barrier, 3);

    for (int i = 0; i < N_THREADS; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&threads[i], &thread_attr, worker_fn, arg)) {
            printf("Failed to create thread %d\n", i);
            free(arg);
        }
    }

    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("Failed to join thread %d\n", i);
        }
    }

    return 0;
}