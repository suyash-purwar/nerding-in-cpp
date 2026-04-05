#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * This is a classic example of Deadlock. A deadlock in an operating system is a state where a set of threads are
 * stuck permanently because each is waiting for a resource held by another, creating a circular dependency.
 *
 * Four Necessary Conditions :
 *  1. Mutual Exclusion: One or more than one resource are non-shareable (Only one thread can use at a time)
 *  2. Hold and Wait: A thread is holding at least one resource and waiting for other resources.
 *  3. No Preemption: A resource cannot be taken from a thread unless the thread releases the resource.
 *  4. Circular Wait: A set of threads are waiting for each other in circular form.
 */

typedef struct {
    int id;
    pthread_mutex_t lock;
} Resource;

Resource r1 = { 1, PTHREAD_MUTEX_INITIALIZER };
Resource r2 = { 2, PTHREAD_MUTEX_INITIALIZER };

void* t1_worker(void* arg) {
    printf("Thread 1: Start\n");

    pthread_mutex_lock(&r1.lock);

    printf("Thread 1: Lock acquired on Resource 1\n");
    sleep(1);

    pthread_mutex_lock(&r2.lock);

    printf("Thread 1: Lock acquired on Resource 2\n");

    pthread_mutex_unlock(&r2.lock);

    printf("Thread 1: Lock released on Resource 2\n");

    pthread_mutex_unlock(&r1.lock);

    printf("Thread 1: Lock released on Resource 1\n");

    printf("Exit\n");

    return NULL;
}

void* t2_worker(void* arg) {
    printf("Thread 2: Start\n");

    pthread_mutex_lock(&r2.lock);

    sleep(1);

    printf("Thread 2: Lock acquired on Resource 2\n");

    pthread_mutex_lock(&r1.lock);

    printf("Thread 2: Lock acquired on Resource 1\n");

    pthread_mutex_unlock(&r1.lock);

    printf("Thread 2: Lock released on Resource 1\n");

    pthread_mutex_unlock(&r2.lock);

    printf("Thread 2: Lock released on Resource 2\n");

    printf("Exit\n");

    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t t_attr;
    int t1_arg = 1, t2_arg = 2;

    pthread_attr_init(&t_attr);
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_JOINABLE);

    if (pthread_create(&t1, &t_attr, t1_worker, &t1_arg)) {
        printf("Failed to create thread 1");
    }

    if (pthread_create(&t2, &t_attr, t2_worker, &t2_arg)) {
        printf("Failed to create thread 2");
    }

    if (pthread_join(t1, NULL)) {
        printf("Failed to join thread 1");
    }

    if (pthread_join(t2, NULL)) {
        printf("Failed to join thread 2");
    }

    return 0;
}