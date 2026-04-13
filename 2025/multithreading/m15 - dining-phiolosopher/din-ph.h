#ifndef DIN_PH_H
#define DIN_PH_H

#define _GNU_SOURCE
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    int id;
    pthread_t thread_handle;
    int eat_count;
} philosopher_t;

typedef struct {
    int id;
    bool is_used;
    philosopher_t* philosopher;
    pthread_cond_t cv;
    pthread_mutex_t mutex;
} spoon_t;

static spoon_t* philosopher_get_right_spoon(const philosopher_t*);

static spoon_t* philosopher_get_left_spoon(const philosopher_t*);

static void philosopher_eat(const philosopher_t*);

static void philosopher_release_spoons(philosopher_t*);

static void philosopher_acquire_spoons(philosopher_t*);

#endif
