#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

/**
 * Problem Statement: Using zero semaphores strictly alternate between two threads. One thread should print odd number
 * and other should print even number upto a certain limit.
 */

typedef struct thread_alternator {
    sem_t sem1;
    sem_t sem2;
    int counter;
    int limit;
} thread_alternator_t;

void* thread_worker1(void* arg) {
    thread_alternator_t* alternator = arg;

    printf("Thread 1: Start\n");

    while (alternator->counter < alternator->limit) {
        sem_wait(&alternator->sem1);

        printf("Thread 1: %d\n", alternator->counter);

        alternator->counter++;

        sem_post(&alternator->sem2);
    }

    return NULL;
}

void* thread_worker2(void* arg) {
    thread_alternator_t* alternator = arg;

    printf("Thread 2: Start\n");

    while (alternator->counter < alternator->limit) {
        sem_wait(&alternator->sem2);

        printf("Thread 2: %d\n", alternator->counter);

        alternator->counter++;

        sem_post(&alternator->sem1);
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    thread_alternator_t thread_alternator;
    thread_alternator.limit = 15;
    thread_alternator.counter = 1;

    sem_init(&thread_alternator.sem1, 0, 1);
    sem_init(&thread_alternator.sem2, 0, 0);

    pthread_attr_t t_attr;
    pthread_attr_init(&t_attr);

    pthread_create(&thread1, &t_attr, thread_worker1, &thread_alternator);
    pthread_create(&thread2, &t_attr, thread_worker2, &thread_alternator);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_attr_destroy(&t_attr);

    return 0;
}