#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "din-ph.h"

#define N_PHILOSOPHERS 5

static philosopher_t philosophers[N_PHILOSOPHERS];
static spoon_t spoons[N_PHILOSOPHERS];


static spoon_t* philosopher_get_right_spoon(const philosopher_t* philosopher) {
    const int right_spoon_index = philosopher->id == N_PHILOSOPHERS - 1 ? N_PHILOSOPHERS - 1 : philosopher->id;
    return &spoons[right_spoon_index];
}

static spoon_t* philosopher_get_left_spoon(const philosopher_t* philosopher) {
    return &spoons[philosopher->id];
}

static void philosopher_eat(const philosopher_t* philosopher) {
    const spoon_t* left_spoon = philosopher_get_left_spoon(philosopher);
    const spoon_t* right_spoon = philosopher_get_right_spoon(philosopher);

    assert(left_spoon->philosopher->id == philosopher->id);
    assert(right_spoon->philosopher->id == philosopher->id);
    assert(left_spoon->is_used == right_spoon->is_used == true);

    printf("Philosopher %d is eating with Spoons %d and %d", philosopher->id, left_spoon->id, right_spoon->id);

    sleep(1);
}

static void philosopher_release_spoons(philosopher_t* philosopher) {

}

static void philosopher_acquire_spoons(philosopher_t* philosopher) {

}

void* philosopher_fn(void *arg) {
    philosopher_t* philosopher = arg;
    return NULL;
}

void initialize_spoons() {
    for (int i = 0; i < N_PHILOSOPHERS; i++) {
        spoons[i].id = i;
        spoons[i].is_used = false;
        spoons[i].philosopher = NULL;
        pthread_cond_init(&spoons[i].cv, NULL);
        pthread_mutex_init(&spoons[i].mutex, NULL);
    }
}

void initialise_philosophers() {
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);

    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < N_PHILOSOPHERS; i++) {
        if (pthread_create(&philosophers[i].thread_handle, &thread_attr, philosopher_fn, &philosophers[i])) {
            printf("Failed to create philosopher thread %d\n", i);
            pthread_exit(0);
        }
    }
}

int main() {
    initialize_spoons();
    initialise_philosophers();

    pthread_exit(0);
}