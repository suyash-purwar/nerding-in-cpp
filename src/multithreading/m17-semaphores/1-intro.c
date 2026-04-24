#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define N_THREADS 5

/**
 * Semaphore allow N number of threads to access the critical section at a time. A semaphore can be used with threads
 * as well as with processes.
 *
 * `sem_init(&sem_t sem, int pshared, unsigned int value)`: Initialises the semaphore
 *
 * - The `pshared` argument determines if the semaphore is being used for threads or processes. 0 is for threads and any
 *    other value is for processes.
 * - `value` determines how many threads are allowed to access critical section at a time. It can only be positive.
 * - Binary Semaphore works like a Mutex. There is one difference though. A mutex lock can be only be unlocked by the
 * same thread which took it. In contrast, a binary semaphore can be unlocked by a different thread.
 */

sem_t semaphore;

void* worker(void* arg) {
    const int thread_n = *(int*)arg;

    int counter = 0;
    while (counter < 3) {
        printf("Thread %d: Started\n", thread_n);

        sem_wait(&semaphore);

        printf("Thread %d: In critical section\n", thread_n);
        sleep(5);

        sem_post(&semaphore);

        printf("Thread %d: Exited CS\n", thread_n);

        counter++;
    }

    free(arg);

    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    sem_init(&semaphore, 0, 2);

    for (int i = 0; i < N_THREADS; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;

        if (pthread_create(&threads[i], &thread_attr, worker, arg)) {
            printf("Failed to create thread %d\n", i);
            free(arg);
        }
    }

    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("Failed to join thread %d\n", i);
        }
    }

    pthread_attr_destroy(&thread_attr);
    sem_destroy(&semaphore);

    return 0;
}