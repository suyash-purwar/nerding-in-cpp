#include "xsema.h"

#include <stdio.h>

xsema_t* xsema_init(xsema_t* xsema, const unsigned int max_counter) {
    xsema->max_counter = max_counter;
    xsema->counter = max_counter;

    pthread_mutex_init(&xsema->mutex, NULL);
    pthread_cond_init(&xsema->cv, NULL);

    return xsema;
}

void xsema_wait(xsema_t* xsema) {
    pthread_mutex_lock(&xsema->mutex);

    while (xsema->counter == 0) {
        pthread_cond_wait(&xsema->cv, &xsema->mutex);
    }

    xsema->counter--;

    pthread_mutex_unlock(&xsema->mutex);
}

void xsema_post(xsema_t* xsema) {
    pthread_mutex_lock(&xsema->mutex);

    if (xsema->counter < xsema->max_counter) {
        xsema->counter++;
        pthread_cond_signal(&xsema->cv);
    }

    pthread_mutex_unlock(&xsema->mutex);
}

int xsema_getvalue(xsema_t* xsema) {
    return xsema->counter;
}

void xsema_destroy(xsema_t* xsema) {
    pthread_mutex_destroy(&xsema->mutex);
    pthread_cond_destroy(&xsema->cv);
}