#ifndef DIN_PH_H
#define DIN_PH_H

#include <pthread.h>

typedef struct {
    int id;
    pthread_mutex_t mutex;
} spoon_t;

typedef struct {
    int id;
    int eat_count;
    pthread_t thread;
    spoon_t* left_spoon;
    spoon_t* right_spoon;
} philosopher_t;

#endif //DIN_PH_H
