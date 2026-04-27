#ifndef XRWLOCK_H
#define XRWLOCK_H

#include <pthread.h>

typedef struct {
    unsigned int reader_count;
    unsigned int writer_count;
    pthread_mutex_t lock;
    pthread_cond_t reader_cv;
    pthread_cond_t writer_cv;
} xrwlock_t;

xrwlock_t* xrwlock_init(xrwlock_t*);

void xrwlock_rw_lock(xrwlock_t*);

void xrwlock_rd_lock(xrwlock_t*);

void xrwlock_rw_unlock(xrwlock_t*);

void xrwlock_rd_unlock(xrwlock_t*);

// unsigned int xrwlock_get_rw_count(xrwlock_t*);
//
// unsigned int xrwlock_get_rd_count(xrwlock_t*);

void xrwlock_destroy(xrwlock_t*);

#endif //XRWLOCK_H
