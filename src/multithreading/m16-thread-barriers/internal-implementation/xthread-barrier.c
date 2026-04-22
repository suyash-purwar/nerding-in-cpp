#include "xthread_barrier.h"

void xthread_barrier_init(xthread_barrier_t* barrier, const int barrier_count) {
    barrier->barrier_count = barrier_count;
    barrier->counter = 0;
    barrier->generation = 0;

    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cv, NULL);
}

void xthread_barrier_wait(xthread_barrier_t* barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->counter++;

    if (barrier->counter == barrier->barrier_count) {
        barrier->counter = 0;
        barrier->generation++;
        pthread_cond_broadcast(&barrier->cv);
    } else {
        const int last_generation = barrier->generation;
        while (last_generation == barrier->generation) {
            pthread_cond_wait(&barrier->cv, &barrier->mutex);
        }
    }

    pthread_mutex_unlock(&barrier->mutex);
}

void xthread_barrier_destroy(xthread_barrier_t* barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cv);
}