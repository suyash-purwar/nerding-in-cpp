#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#include "din-ph.h"

#define N_PHILOSOPHERS 5
#define LOG_LENGTH 512

void log(const philosopher_t* philosopher, char* log_fmt, ...) {
    char log[LOG_LENGTH];
    va_list args;

    va_start(args, log_fmt);

    vsnprintf(log, LOG_LENGTH, log_fmt, args);

    va_end(args);

    printf("Philosopher %d: %s\n", philosopher->id, log);
}

void philosopher_eat(philosopher_t* philosopher) {
    philosopher->eat_count++;
    log(philosopher, "Eating with spoons %d and %d", philosopher->left_spoon->id, philosopher->right_spoon->id);

    sleep(1);
}

void philosopher_release_spoons(const philosopher_t* philosopher) {
    spoon_t* left_spoon = philosopher->left_spoon;
    spoon_t* right_spoon = philosopher->right_spoon;

    pthread_mutex_lock(&left_spoon->mutex);
    left_spoon->is_used = false;

    pthread_cond_signal(&left_spoon->cv);
    pthread_mutex_unlock(&left_spoon->mutex);

    pthread_mutex_lock(&right_spoon->mutex);
    right_spoon->is_used = false;

    pthread_cond_signal(&right_spoon->cv);
    pthread_mutex_unlock(&right_spoon->mutex);
}

bool philosopher_acquire_spoons(const philosopher_t* philosopher) {
    spoon_t* left_spoon = philosopher->left_spoon;
    spoon_t* right_spoon = philosopher->right_spoon;

    log(philosopher, "Starts");

    pthread_mutex_lock(&left_spoon->mutex);

    while (left_spoon->is_used) {
        log(philosopher, "CV Blocked - Left spoon not available");
        pthread_cond_wait(&left_spoon->cv, &left_spoon->mutex);
        log(philosopher, "CV Unblocked - Left spoon available");
    }

    left_spoon->is_used = true;
    log(philosopher, "Left spoon taken %d", left_spoon->id);

    pthread_mutex_unlock(&left_spoon->mutex);

    pthread_mutex_lock(&right_spoon->mutex);

    if (right_spoon->is_used) {
        log(philosopher, "Right spoon not available");
        pthread_mutex_unlock(&right_spoon->mutex);

        pthread_mutex_lock(&left_spoon->mutex);

        left_spoon->is_used = false;
        pthread_cond_signal(&left_spoon->cv);
        log(philosopher, "Left spoon is put back %d", left_spoon->id);

        pthread_mutex_unlock(&left_spoon->mutex);

        return false;
    }

    right_spoon->is_used = true;
    log(philosopher, "Right spoon taken %d", right_spoon->id);

    pthread_mutex_unlock(&right_spoon->mutex);

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
}

spoon_t* initialize_spoons() {
    spoon_t* spoons = malloc(N_PHILOSOPHERS * sizeof(spoon_t));

    if (spoons == NULL) {
        perror("Failed to allocate memory for spoons");
        return NULL;
    }

    for (int i = 0; i < N_PHILOSOPHERS; i++) {
        spoons[i].id = i;
        spoons[i].is_used = false;
        pthread_cond_init(&spoons[i].cv, NULL);
        pthread_mutex_init(&spoons[i].mutex, NULL);
    }

    return spoons;
}

philosopher_t* initialise_philosophers(spoon_t* spoons) {
    philosopher_t* philosophers = malloc(N_PHILOSOPHERS * sizeof(philosopher_t));

    if (philosophers == NULL || spoons == NULL) {
        perror("Failed to allocate memory for philosophers");
        return NULL;
    }


    for (int i = 0; i < N_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        philosophers[i].eat_count = 0;
        philosophers[i].left_spoon = i == 0 ? &spoons[N_PHILOSOPHERS-1] : &spoons[i-1];
        philosophers[i].right_spoon = &spoons[i];
    }

    return philosophers;
}

void start_philosophers(philosopher_t* philosophers) {
    if (philosophers == NULL)
        return;

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
    spoon_t* spoons = initialize_spoons();
    philosopher_t* philosophers = initialise_philosophers(spoons);

    start_philosophers(philosophers);

    pthread_exit(0);
}