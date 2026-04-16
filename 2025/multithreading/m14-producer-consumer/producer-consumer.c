#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>

#include  "queue/queue.h"

/**
 * Condition Variables allows us to have finer control over taking the decision on when and which competing thread to
 * block or resume. It allows a thread to get itself blocked or resumed when certain conditions are met.
 *
 * How is it different from a Mutex?
 *  - Mutex cannot implement condition-based blocking and resumption of threads
 *  - Mutex only says - execute if you have access or wait. It's either a Yes or No.
 *  - Using Mutexes we can't implement this logic - If a queue is empty, wait until it has some element in it.
 *
 * A mutex is generally used in conjunction with condition variables.
 *
 * Condition Variables are not used for Mutual Exclusion, they are used for coordination among the threads.
 * Using CV, a thread can block itself (pthread_cond_wait()) and can signal a blocked thread to resume it's work
 * (pthread_cond_signal()).
 *
 * Say we have two threads A and B.
 * When thread A invokes `pthread_cond_wait()`, the thread gets blocked and the acquired mutex lock is released
 * internally. This mutex lock is not available for another thread. Now, thread B takes the mutex lock and invokes
 * `pthread_cond_signal`, this tells thread A to come to "Ready" state (execution is not resumed yet). When thread B
 * releases the mutex, thread A resumes it's and mutex ownership goes back to thread A. A controlled transfer of mutex
 * ownership is happening here.
 */

#define PRODUCER_COUNT 2
#define CONSUMER_COUNT 2
#define THREAD_NAME_LEN 16

char* get_thread_name(char* thread_name) {
    sleep(0.5);
    const pthread_t thread = pthread_self();
    pthread_getname_np(thread, thread_name, THREAD_NAME_LEN);

    return thread_name;
}

void set_thread_name(const pthread_t thread, const char* thread_name_fmt, ...) {
    va_list args;
    va_start(args, thread_name_fmt);

    char thread_name[THREAD_NAME_LEN];
    vsnprintf(thread_name, THREAD_NAME_LEN, thread_name_fmt, args);
    va_end(args);

    pthread_setname_np(thread, thread_name);
}

void write_to_queue(Queue* queue) {
    char thread_name[THREAD_NAME_LEN];
    get_thread_name(thread_name);

    short int i = 0;

    while (i < QUEUE_SIZE) {
        const int added_item = rand();
        enqueue(queue, added_item);
        printf("%s: Added item %d\n", thread_name, added_item);
        i++;
    }
}

void clear_queue(Queue* queue) {
    char thread_name[THREAD_NAME_LEN];
    get_thread_name(thread_name);

    short int i = 0;
    int removed_item;

    while (i < QUEUE_SIZE) {
        dequeue(queue, &removed_item);
        printf("%s: Removed item %d\n", thread_name, removed_item);
        i++;
    }
}

void* producer_worker(void* arg) {
    char thread_name[THREAD_NAME_LEN];
    get_thread_name(thread_name);

    printf("%s: Started\n", thread_name);

    Queue* queue = arg;

    pthread_mutex_lock(&queue->lock);

    printf("%s: Mutex locked\n", thread_name);

    while (is_full(queue)) {
        printf("%s: CV Locked\n", thread_name);
        pthread_cond_wait(&queue->cv, &queue->lock);
    }

    printf("%s: CV Unlocked\n", thread_name);

    write_to_queue(queue);

    // pthread_cond_broadcast(&queue->cv);
    pthread_cond_signal(&queue->cv);

    // printf("%s: Broadcasted\n", thread_name);
    printf("%s: Signal\n", thread_name);

    pthread_mutex_unlock(&queue->lock);

    printf("%s: Mutex Unlocked\n", thread_name);

    return NULL;
}

void* consumer_worker(void* arg) {
    char thread_name[THREAD_NAME_LEN];
    get_thread_name(thread_name);

    printf("%s: Started\n", thread_name);

    Queue* queue = arg;

    pthread_mutex_lock(&queue->lock);

    printf("%s: Mutex locked\n", thread_name);

    while (is_empty(queue)) {
        printf("%s: CV Locked\n", thread_name);
        pthread_cond_wait(&queue->cv, &queue->lock);
    }

    printf("%s: CV Unlocked\n", thread_name);

    clear_queue(queue);

    pthread_cond_broadcast(&queue->cv);
    printf("%s: Broadcasted\n", thread_name);

    pthread_mutex_unlock(&queue->lock);

    printf("%s: Mutex Unlocked\n", thread_name);

    return NULL;
}

int main() {
    Queue* queue = init_queue();

    pthread_t producers[PRODUCER_COUNT];
    pthread_t consumers[CONSUMER_COUNT];

    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        if (pthread_create(&consumers[i], &thread_attr, consumer_worker, queue)) {
            printf("Failed to create consumer thread %d.\n", i);
            exit(-1);
        }

        set_thread_name(consumers[i], "Consumer %d", i);
    }

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        if (pthread_create(&producers[i], &thread_attr, producer_worker, queue)) {
            printf("Failed to create producer thread %d.\n", i);
            exit(-1);
        }

        set_thread_name(producers[i], "Producer %d", i);
    }

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        if (pthread_join(producers[i], NULL)) {
            printf("Failed to join producer thread %d.\n", i);
            exit(-1);
        }
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        if (pthread_join(consumers[i], NULL)) {
            printf("Failed to join consumer thread %d.\n", i);
            exit(-1);
        }
    }

    printf("Joined\n");

    free(queue);

    return 0;
}