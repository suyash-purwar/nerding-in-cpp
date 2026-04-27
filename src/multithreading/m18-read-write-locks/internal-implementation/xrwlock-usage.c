#include "xrwlock.h"
#include <stdio.h>
#include <unistd.h>

#define N_READER_THREADS 3
#define N_WRITER_THREADS 1

xrwlock_t rwlock;
pthread_mutex_t lock;

static int reader_count = 0;
static int writer_count = 0;

void entering_reader_cs() {
    pthread_mutex_lock(&lock);

    reader_count++;

    pthread_mutex_unlock(&lock);
}

void exiting_reader_cs() {
    pthread_mutex_lock(&lock);

    reader_count--;

    pthread_mutex_unlock(&lock);
}

void entering_writer_cs() {
    writer_count++;
}

void exiting_writer_cs() {
    writer_count--;
}

void do_cs_work() {
    pthread_mutex_lock(&lock);

    printf("Readers Count: %d | Writers Count: %d\n", reader_count, writer_count);

    pthread_mutex_unlock(&lock);
}

void* reader_worker(void* arg) {
    while (1) {
        xrwlock_rd_lock(&rwlock);

        entering_reader_cs();
        do_cs_work();
        exiting_reader_cs();

        xrwlock_rd_unlock(&rwlock);
    }
}

void* writer_worker(void* arg) {
    while (1) {
        xrwlock_rw_lock(&rwlock);

        entering_writer_cs();
        do_cs_work();
        exiting_writer_cs();

        xrwlock_rw_unlock(&rwlock);
    }

    return NULL;
}

int main() {
    pthread_t reader_threads[N_READER_THREADS];
    pthread_t writer_threads[N_WRITER_THREADS];

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    pthread_mutex_init(&lock, NULL);
    xrwlock_init(&rwlock);

    for (int i = 0; i < N_READER_THREADS; i++) {
        if (pthread_create(&reader_threads[i], &thread_attr, reader_worker, NULL)) {
            printf("Failed to start reader threads\n");
            return -1;
        }
    }

    for (int j = 0; j < N_WRITER_THREADS; j++) {
        if (pthread_create(&writer_threads[j], &thread_attr, writer_worker, NULL)) {
            printf("Failed to start writer threads\n");
            return -1;
        }
    }

    pthread_attr_destroy(&thread_attr);
    pthread_mutex_destroy(&lock);
    xrwlock_destroy(&rwlock);

    pthread_exit(0);

    return 0;
}