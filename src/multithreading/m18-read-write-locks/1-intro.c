#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * Read/Write Locks
 *
 * Consider this example - There are three thread T1, T2, and T3 working on a shared array.
 * T1 - Does summation of the values in the array
 * T2 - Does the product of all the values
 * T3 - Finds the square of each value and updates it in the array
 *
 * Notice how the thread T1 and T2 are readers, while T3 is the writer. This means that T1 and T2's read operation must
 * not conflict with T3's write operation. The obvious solution is to wrap the critical section of all three threads
 * into a mutex lock.
 *
 * This would mean that at any given point of time only one thread is using the shared array. Though it solves the
 * problem, it is not an optimal approach.
 *
 * Notice, how threads T1 and T2 do not interfere with each other's work. They can work in parallel but due to our
 * mutex it can't. Concurrency can be improved here.
 *
 * This is where Read/Write locks come into the picture. The idea is let all the reader threads take the read lock and
 * access the critical section concurrently. If there is any writer thread in the critical section, block all the
 * writer and reader threads which try to access the mutex.
 *
 * Essentially,
 * Read-Read operations are not conflicting. Thus, they don't need mutual exclusion and thread synchronisation.
 * Read-Write operations are conflicting.
 * Write-Write operations are conflicting.
 *
 * The following example demonstrates how `reader_count` can go upto 3 but `writer_count` remains 1 at max.
 */

#define N_READER_THREADS 3
#define N_WRITER_THREADS 3

pthread_rwlock_t rwlock;
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
        pthread_rwlock_rdlock(&rwlock);

        entering_reader_cs();
        do_cs_work();
        exiting_reader_cs();

        pthread_rwlock_unlock(&rwlock);
    }

    return NULL;
}

void* writer_worker(void* arg) {
    while (1) {
        pthread_rwlock_wrlock(&rwlock);

        entering_writer_cs();
        do_cs_work();
        exiting_writer_cs();

        pthread_rwlock_unlock(&rwlock);
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
    pthread_rwlock_init(&rwlock, NULL);

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
    pthread_rwlock_destroy(&rwlock);

    pthread_exit(0);

    return 0;
}