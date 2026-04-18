#ifndef DIN_PH_H
#define DIN_PH_H

#define _GNU_SOURCE
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    int id;
    bool is_used;
    pthread_cond_t cv;
    pthread_mutex_t mutex;
} spoon_t;

typedef struct {
    int id;
    int eat_count;
    pthread_t thread_handle;
    spoon_t* left_spoon;
    spoon_t* right_spoon;
} philosopher_t;

#endif
