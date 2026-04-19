#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N_THREADS 8

int dice_results[N_THREADS];
int status[N_THREADS] = { 0 };

pthread_barrier_t barrier;

void* roll_dice(void* arg) {
    const int thread_n = *(int*)arg;

    while (1) {
        dice_results[thread_n] = rand() % 6 + 1;

        pthread_barrier_wait(&barrier);
        pthread_barrier_wait(&barrier);

        if (status[thread_n]) {
            printf("Thread %d got %d: Won\n", thread_n, dice_results[thread_n]);
        } else {
            printf("Thread %d got %d: Lost\n", thread_n, dice_results[thread_n]);
        }
    }
}

int main() {
    pthread_t threads[N_THREADS];
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    pthread_barrier_init(&barrier, NULL, N_THREADS+1);

    int max = -1, round = 0;

    for (int i = 0; i < N_THREADS; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&threads[i], &thread_attr, roll_dice, arg)) {
            printf("Failed to create thread %d\n", i);
            free(arg);
        }
    }

    while (1) {
        printf("======= ROUND %d ======= \n", round);

        max = -1;
        memset(status, 0, sizeof(status));

        pthread_barrier_wait(&barrier);

        for (int i = 0; i < N_THREADS; i++) {
            if (dice_results[i] > max) max = dice_results[i];
        }

        for (int i = 0; i < N_THREADS; i++) {
            if (dice_results[i] == max) status[i] = 1;
        }

        round++;

        pthread_barrier_wait(&barrier);

        sleep(3);
    }

    return 0;
}