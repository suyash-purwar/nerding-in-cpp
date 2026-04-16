#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdarg.h>

#include "din-ph.h"

#define N_PHILOSOPHERS 5
#define LOG_LENGTH 500

static philosopher_t philosophers[N_PHILOSOPHERS];
static spoon_t spoons[N_PHILOSOPHERS];

void log(const philosopher_t* philosopher, char* log_fmt, ...) {
    char log[LOG_LENGTH];
    va_list args;

    va_start(args, log_fmt);

    vsnprintf(log, LOG_LENGTH, log_fmt, args);

    va_end(args);

    printf("Philosopher %d: %s\n", philosopher->id, log);
}

static spoon_t* philosopher_get_right_spoon(const philosopher_t* philosopher) {
    const int right_spoon_index = philosopher->id == 0 ? N_PHILOSOPHERS - 1 : philosopher->id - 1;
    return &spoons[right_spoon_index];
}

static spoon_t* philosopher_get_left_spoon(const philosopher_t* philosopher) {
    return &spoons[philosopher->id];
}

static void philosopher_eat(philosopher_t* philosopher) {
    const spoon_t* left_spoon = philosopher_get_left_spoon(philosopher);
    const spoon_t* right_spoon = philosopher_get_right_spoon(philosopher);

    assert(left_spoon->philosopher->id == philosopher->id);
    assert(right_spoon->philosopher->id == philosopher->id);
    assert(left_spoon->is_used == true && right_spoon->is_used == true);

    philosopher->eat_count++;

    log(philosopher, "Eating with spoons %d and %d", left_spoon->id, right_spoon->id);

    sleep(1);
}

static void philosopher_release_spoons(const philosopher_t* philosopher) {
    spoon_t* left_spoon = philosopher_get_left_spoon(philosopher);
    spoon_t* right_spoon = philosopher_get_right_spoon(philosopher);

    pthread_mutex_lock(&left_spoon->mutex);
    left_spoon->philosopher = NULL;
    left_spoon->is_used = false;

    pthread_cond_signal(&left_spoon->cv);
    pthread_mutex_unlock(&left_spoon->mutex);


    pthread_mutex_lock(&right_spoon->mutex);
    right_spoon->philosopher = NULL;
    right_spoon->is_used = false;

    pthread_cond_signal(&right_spoon->cv);
    pthread_mutex_unlock(&right_spoon->mutex);
}

static bool philosopher_acquire_spoons(philosopher_t* philosopher) {
    spoon_t* left_spoon = philosopher_get_left_spoon(philosopher);
    spoon_t* right_spoon = philosopher_get_right_spoon(philosopher);

    log(philosopher, "Starts");

    pthread_mutex_lock(&left_spoon->mutex);
    log(philosopher, "Mutex Lock Acquired on left spoon %d", left_spoon->id);

    while (left_spoon->is_used && left_spoon->philosopher != philosopher) {
        log(philosopher, "CV Blocked - Left spoon not available");
        pthread_cond_wait(&left_spoon->cv, &left_spoon->mutex);
        log(philosopher, "CV Unblocked - Left spoon available");
    }

    left_spoon->is_used = true;
    left_spoon->philosopher = philosopher;
    log(philosopher, "Left spoon taken %d", left_spoon->id);

    pthread_mutex_unlock(&left_spoon->mutex);
    log(philosopher, "Mutex unlocked on left spoon %d", left_spoon->id);

    pthread_mutex_lock(&right_spoon->mutex);
    log(philosopher, "Mutex locked on right spoon %d", right_spoon->id);

    if (right_spoon->is_used) {
        log(philosopher, "Right spoon not available");
        pthread_mutex_unlock(&right_spoon->mutex);
        log(philosopher, "Mutex unlocked on right spoon %d", right_spoon->id);

        pthread_mutex_lock(&left_spoon->mutex);
        log(philosopher, "Mutex locked on left spoon %d", left_spoon->id);

        left_spoon->is_used = false;
        left_spoon->philosopher = NULL;
        pthread_cond_signal(&left_spoon->cv);
        log(philosopher, "Left spoon is put back %d", left_spoon->id);

        pthread_mutex_unlock(&left_spoon->mutex);
        log(philosopher, "Mutex unlocked on left spoon %d", left_spoon->id);

        return false;
    }

    right_spoon->is_used = true;
    right_spoon->philosopher = philosopher;
    log(philosopher, "Right spoon taken %d", right_spoon->id);

    pthread_mutex_unlock(&right_spoon->mutex);
    log(philosopher, "Mutex unlocked on right spoon %d", right_spoon->id);

    return true;
}

void* philosopher_fn(void *arg) {
    philosopher_t* philosopher = arg;

    while (true) {
        if (philosopher_acquire_spoons(philosopher)) {
            log(philosopher, "Both spoon and are taken");

            philosopher_eat(philosopher);
            log(philosopher, "Eats %d times", philosopher->eat_count);

            philosopher_release_spoons(philosopher);
            log(philosopher, "Puts down both spoons");
            sleep(1);
        } else {
            log(philosopher, "Could not eat. Adjacent philosopher is eating.");
            sleep(1);
        }
    }

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
        philosophers[i].id = i;
        philosophers[i].eat_count = 0;

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