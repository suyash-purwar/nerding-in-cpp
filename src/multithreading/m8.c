#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADS 4
#define COUNT_LIMIT 1e7

/**
 * Without Thread Synchronization, the critical section (`count++`) would be accessible by all the threads leading to
 * Dirty Writes problem.
 *
 * Mutex stands for Mutual Exclusion. It ensures that at any point of time only thread is able to access the critical
 * section of the thread. It does so by acquiring locks. In a case where thread T1 has acquired the lock and the thread
 * T2 tries to acquire the lock, thread T2 gets blocked and waits for Thread T1 to release it.
 *
 * In this particular example, the thread workload is purely CPU bound. In a scenario such as this, concurrency is
 * helpful only when the system has multiple cores. Had there been a single core, concurrency would only make the
 * performance poorer.
 *
 * A mutex lock can be initialised in two ways:
 *  - `pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER`
 *  - `pthread_mutex_initializer(pthread_mutex_t*, const pthread_mutexattr_t*)`
 *
 * A mutex is taken and release via these two functions
 *  - `pthread_mutex_lock(pthread_mutex_t*)`
 *  - `pthread_mutex_unlock(pthread_mutex_t*)`
 *
 * A mutex is deleted by `pthread_mutex_destroy(pthread_mutex_t*)` function
 *
 * Some points on Mutex:
 *  - If T1 locks a mutex M, only T1 can unlock it.
 *  - T1 cannot unlock an already unlocked mutex. If done, it leads to undefined behaviour.
 *  - If T1 locks a mutex M; T1, T2 will be locked if they try to lock M.
 *  - If T2 and T3 are blocked to acquire a lock on already blocked mutex M, the OS scheduling policy will decide
 *    which thread (T2 or T3) would acquire the lock on M, when M is unlocked by its owner (T1).
 *  - If thread T1 attempts to double lock the mutex M, it will self-deadlock.
 *  - Mutexes must be unlocked in LIFO order.
 *
 * There are two types of Mutex strategies:
 *  - Object-Level Locking: Only one thread can execute a synchronized block or method on a particular instance of an
 *    object at any given time. If you have two different objects (instances) of the same class, two threads can execute
 *    the same code simultaneously, one for each object without blocking each other.
 *  - Code-Level Locking (Class-Level Locking): This mechanism is used to synchronize access across all instances of a
 *    class or a specific block of code regardless of which object is being used. If there is a global resource shared
 *    across all the threads, this method of mutex is used.
 */


static volatile int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* counter() {
    for (int i = 0; i < COUNT_LIMIT; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

pthread_t* create_counter_thread() {
    pthread_t* thread = calloc(1, sizeof(pthread_t));
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

    const int thread_status = pthread_create(thread, &thread_attr, counter, NULL);

    if (thread_status) {
        printf("Failed to create thread");
        return NULL;
    }

    return thread;
}

int main() {
    pthread_t* threads[THREADS];

    for (int i = 0; i < THREADS; i++) {
        threads[i] = create_counter_thread();
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(*threads[i], NULL);
        free(threads[i]);
    }

    printf("Counter is: %d\n", count);

    pthread_mutex_destroy(&lock);
}