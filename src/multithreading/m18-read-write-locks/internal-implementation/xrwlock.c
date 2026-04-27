#include "xrwlock.h"

xrwlock_t* xrwlock_init(xrwlock_t* xrwlock) {
    xrwlock->reader_count = 0;
    xrwlock->writer_count = 0;
    pthread_mutex_init(&xrwlock->lock, NULL);
    pthread_cond_init(&xrwlock->reader_cv, NULL);
    pthread_cond_init(&xrwlock->writer_cv, NULL);

    return xrwlock;
}

void xrwlock_rd_lock(xrwlock_t* xrwlock) {
    pthread_mutex_lock(&xrwlock->lock);

    while (xrwlock->writer_count != 0) {
        pthread_cond_wait(&xrwlock->reader_cv, &xrwlock->lock);
    }

    xrwlock->reader_count++;

    pthread_mutex_unlock(&xrwlock->lock);
}

void xrwlock_rd_unlock(xrwlock_t* xrwlock) {
    pthread_mutex_lock(&xrwlock->lock);

    xrwlock->reader_count--;

    if (xrwlock->reader_count == 0) {
        pthread_cond_signal(&xrwlock->writer_cv);
        pthread_cond_broadcast(&xrwlock->reader_cv);
    }

    pthread_mutex_unlock(&xrwlock->lock);
}

void xrwlock_rw_lock(xrwlock_t* xrwlock) {
    pthread_mutex_lock(&xrwlock->lock);

    while (xrwlock->reader_count != 0 || xrwlock->writer_count != 0) {
        pthread_cond_wait(&xrwlock->writer_cv, &xrwlock->lock);
    }

    xrwlock->writer_count++;

    pthread_mutex_unlock(&xrwlock->lock);
}

void xrwlock_rw_unlock(xrwlock_t* xrwlock) {
    pthread_mutex_lock(&xrwlock->lock);

    xrwlock->writer_count--;

    if (xrwlock->writer_count == 0) {
        pthread_cond_signal(&xrwlock->writer_cv);
        pthread_cond_broadcast(&xrwlock->reader_cv);
    }

    pthread_mutex_unlock(&xrwlock->lock);
}

void xrwlock_destroy(xrwlock_t* xrwlock) {
    pthread_mutex_destroy(&xrwlock->lock);
    pthread_cond_destroy(&xrwlock->reader_cv);
    pthread_cond_destroy(&xrwlock->writer_cv);
}