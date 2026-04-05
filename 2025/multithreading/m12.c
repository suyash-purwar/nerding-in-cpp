#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * There are two threads - Summation Thread and Swap Ends Thread.
 * Summation Thread is responsible for doing the summation of items present in the list.
 * Swap Ends Thread is responsible for swapping the first and last values of the list.
 *
 * Summation Thread is the reader of shared data while Swap Ends Thread is the writer. Without thread synchronization,
 * the sum would become corrupt. Swapping numbers in the array required three steps. Swap Ends can preempt after 2 steps
 * leading to incorrect list state. Summation Thread will read this incorrect state for summation and produce a wrong
 * number.
 *
 * A Mutex Lock solves this problem.
 */

typedef struct {
    int list[5];
    pthread_mutex_t lock;
} SpecialArray;

void* summation_worker(void* arg) {
    SpecialArray* sa = arg;
    short int i = 0;

    while (i < 10000) {
        int sum = 0;

        pthread_mutex_lock(&sa -> lock);
        for (int j = 0; j < 5; j++) {
            sum += sa -> list[j];
        }
        pthread_mutex_unlock(&sa -> lock);

        if (sum != 150) {
            printf("%d ", sum);
        }

        i++;
    }

    return NULL;
}

void* swap_ends_worker(void* arg) {
    SpecialArray* sa = arg;
    short int i = 0;

    while (i < 10000) {
        pthread_mutex_lock(&sa -> lock);
        const int temp = sa -> list[0];
        sa -> list[0] = sa -> list[4];
        sa -> list[4] = temp;
        pthread_mutex_unlock(&sa -> lock);

        i++;
    }

    return NULL;
}

int main() {
    SpecialArray sa = { {10, 20, 30, 40, 50}, PTHREAD_MUTEX_INITIALIZER };

    pthread_t summation_thread;
    pthread_t swap_ends_thread;
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    if (pthread_create(&swap_ends_thread, &thread_attr, swap_ends_worker, &sa)) {
        printf("Failed to create swap_ends thread");
        exit(-1);
    }

    if (pthread_create(&summation_thread, &thread_attr, summation_worker, &sa)) {
        printf("Failed to create summation thread");
        exit(-1);
    }

    if (pthread_join(swap_ends_thread, NULL)) {
        printf("Failed to join swap_ends thread");
        exit(-1);
    }

    if (pthread_join(summation_thread, NULL)) {
        printf("Failed to join summation thread");
        exit(-1);
    }

    return 0;
}