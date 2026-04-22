#ifndef XTHREAD_BARRIER_H
#define XTHREAD_BARRIER_H

#include <pthread.h>

typedef struct {
    int barrier_count;
    int counter;
    int generation;
    pthread_mutex_t mutex;
    pthread_cond_t cv;
} xthread_barrier_t;

void xthread_barrier_init(xthread_barrier_t*, int);

void xthread_barrier_wait(xthread_barrier_t*);

#endif //XTHREAD_BARRIER_H
