#ifndef XSEMA_H
#define XSEMA_H

#include <pthread.h>

typedef struct _xsema_t {
    int max_counter;
    int counter;
    pthread_mutex_t mutex;
    pthread_cond_t cv;
} xsema_t;

xsema_t* xsema_init(xsema_t*, unsigned int);

void xsema_wait(xsema_t*);

void xsema_post(xsema_t*);

int xsema_getvalue(xsema_t*);

void xsema_destroy(xsema_t*);

#endif //XSEMA_H
