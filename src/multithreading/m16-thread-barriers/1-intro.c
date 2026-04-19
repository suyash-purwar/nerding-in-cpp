#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 3

pthread_barrier_t barrier;

void* worker_fn(void* arg) {
    int thread_n = *(int*)arg;

    printf("Thread %d has reach barrier 1\n", thread_n);

    pthread_barrier_wait(&barrier);

    sleep(3);

    printf("Thread %d has reach barrier 2\n", thread_n);

    pthread_barrier_wait(&barrier);

    free(arg);

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&threads[i], &thread_attr, worker_fn, arg)) {
            printf("Failed to create thread %d\n", i);
            free(arg);
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("Failed to join the thread %d\n", i);
        }
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}