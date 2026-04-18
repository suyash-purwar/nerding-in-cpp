#include "din-ph.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define LOG_LENGTH 512
#define PHILOSOPHER_COUNT 5

void log(const philosopher_t* philosopher, char* log_fmt, ...) {
    char log[LOG_LENGTH];
    va_list args;

    va_start(args, log_fmt);

    vsnprintf(log, LOG_LENGTH, log_fmt, args);

    va_end(args);

    printf("Philosopher %d: %s\n", philosopher->id, log);
}

void* philosopher_fn(void* arg) {
    philosopher_t* philosopher = arg;
    log(philosopher, "Starts");

    while (true) {
        pthread_mutex_lock(&philosopher->left_spoon->mutex);
        log(philosopher, "Left spoon acquired");

        /**
         * This sleep increases the chances of deadlock happening. It can happen without it as well
         * but might require a few retries and the program to run for a while.
         */
        sleep(1);

        pthread_mutex_lock(&philosopher->right_spoon->mutex);
        log(philosopher, "Right spoon acquired");

        philosopher->eat_count++;
        log(philosopher, "Eats %d times", philosopher->eat_count);

        pthread_mutex_unlock(&philosopher->right_spoon->mutex);
        log(philosopher, "Right spoon released");

        pthread_mutex_unlock(&philosopher->left_spoon->mutex);
        log(philosopher, "Left spoon released");

        sleep(1);
    }

    return NULL;
}

spoon_t* initialise_spoons() {
    spoon_t* spoons = malloc(PHILOSOPHER_COUNT * sizeof(spoon_t));

    if (spoons == NULL) {
        perror("Failed to allocate memory for spoons");
        return NULL;
    }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        spoons[i].id = i;
        pthread_mutex_init(&spoons[i].mutex, NULL);
    }

    return spoons;
}

philosopher_t* initialise_philosophers(spoon_t* spoons) {
    philosopher_t* philosophers = malloc(PHILOSOPHER_COUNT * sizeof(philosopher_t));

    if (philosophers == NULL || spoons == NULL) {
        perror("Failed to allocate memory for philosophers");
        return NULL;
    }

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        philosophers[i].id = i;
        philosophers[i].eat_count = 0;
        philosophers[i].left_spoon = i == 0 ? &spoons[PHILOSOPHER_COUNT-1] : &spoons[i-1];
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

    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        pthread_create(&philosophers[i].thread, &thread_attr, philosopher_fn, &philosophers[i]);
    }
}

int main() {
    spoon_t* spoons = initialise_spoons();
    philosopher_t* philosophers = initialise_philosophers(spoons);
    start_philosophers(philosophers);

    pthread_exit(0);
}