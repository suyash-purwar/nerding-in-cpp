#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * A thread can be cancelled in the middle of its execution in two ways
 *  - Deferred Cancellation (PTHREAD_CANCEL_DEFERRED): Thread gets cancelled at specific safe points. This is default state.
 *  - Asynchronous Cancellation (PTHREAD_CANCEL_ASYNCHRONOUS): Thread gets cancelled at any point.
 *
 * A thread also has it's cancellability which means. There are two types.
 *  - Cancellable (PTHREAD_CANCEL_ENABLE): Thread is cancellable. This is the default state.
 *  - Not Cancellable (PTHREAD_CANCEL_DISABLE): Thread is not cancellable.
 *
 * Why would we need the ability to cancel a thread execution midway?
 *  - Killing an expensive SQL query
 *  - Cancelling any operation that is no longer needed
 *
 * Note how `pthread_setcancelstate` and `pthread_setcanceltype` do not take thread handler as the input. How does it
 * know which thread needs to be targeted? Whichever thread's stack executes the function, the change applies to that
 * thread.
 *
 * Call signature
 *  - `int pthread_setcancelstate(int state, int *oldstate);`
 *  - `int pthread_setcanceltype(int type, int *oldtype);`
 *
 * The previous cancellability state of the thread is returned in the buffer pointed to by `oldstate`.
 *
 * Thread cancellation is done by the `pthread_cancel(pthread_t)` function. Thread cancellation in pthreads is actually
 * implemented using signals internally on Linux.
 *
 * Imp Note:
 *  - The thread's cancellability type determines when a cancellable thread will respond to a cancellation request. If
 *    a cancellation request is received and the thread is so far not cancellable, it is blocked until cancellability
 *    is enabled.
 *  - Briefly disabling cancellability is useful if a thread performs some critical action that must not be interrupted
 *    by a cancellation request.  Beware of disabling cancellability for long periods, or around operations that may
 *    block for long periods, since that will render the thread unresponsive to cancellation requests.
 *
 * Issue of Resource Leakage and Invariants
 * - As asynchronous thread can be cancelled at any point of execution. This leads to the issue of resource leakage,
 *   invariants, and deadlocks
 * - Resource leakage: Thread gets cancelled after malloc and before the memory could be freed. Memory leak
 * - Invariants: Imagine a scenario where a thread is appending a new node to a linked list at head position. It
 *   requires multiple pointer changes. A thread might get cancelled in the middle of these operations causing the
 *   data structured to corrupt.
 * - Deadlocks: Consider a scenario where a thread has take a mutex lock on some resource and gets cancelled. This leads
 *   to lock never getting released. Another thread which requires this resource would be in a deadlock state.
 *
 * It is essential that resources are properly released and invariants are prevented before the thread is cancelled. To
 * solve this problem, POSIX pthread makes use of cleanup handlers.
 *
 * For each thread, Cleanup Handler Stack is maintained where the resource cleanup handlers (function pointers) are
 * pushed as more resources are taken. The items from the stack are invoked and popped when a thread is cancelled  or
 * calls pthread_exit.
 *
 * Call signature:
 * - `pthread_cleanup_push((void* cleanup_handler)(void*), void* arg)`: `cleanup_handler` is called with `arg` as
 *   parameter,
 * - pthread_cleanup_pop(int): It takes off the top item in the stack. There are two modes in this function. If 0 is
 *   passed as input, only the item is popped. If 1 is passed, the top most item is invoked as well.
 *
 * Both these functions are macros.
 *
 * Note: The cleanup handlers are not invoked when thread exits by the virtue of the `return` statement.
 */

#define WORKER_THREADS 5

pthread_t threads[WORKER_THREADS];

void cleanup_thread_arg(void* arg) {
    printf("Invoked cleanup_thread_arg");
    free(arg);
}

void close_thread_file(void* arg) {
    printf("Invoked close_thread_file");
    fclose(arg);
}

void* write_to_file(void* th_id) {
    char file_name[64];
    char file_contents[128];
    const char thread_id = *(char*)th_id;
    int counter = 0;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    pthread_cleanup_push(cleanup_thread_arg, th_id);

    sprintf(file_name, "./files/thread_%d.txt", thread_id);
    FILE* file = fopen(file_name, "w");

    pthread_cleanup_push(close_thread_file, file);

    if (file == NULL) {
        perror("Failed to open the file");
        pthread_exit(NULL);
    }

    while (counter < 75) {
        const int file_content_len = sprintf(file_contents, "%d: This is thread %d\n", counter, thread_id);

        fwrite(file_contents, sizeof(char), file_content_len, file);
        fflush(file);

        counter++;
        sleep(1);
    }

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    return NULL;
}

void cancel_thread(const char thread_id) {
    const char thread_cancel_status = pthread_cancel(threads[thread_id]);

    if (thread_cancel_status) {
        printf("Failed to cancel thread: %d", thread_id);
    }
}


void menu() {
    short int choice = -1;

    while (1) {
        printf("Enter the thread id to cancel [0-%d]: ", WORKER_THREADS - 1);
        scanf("%hd", &choice);

        if (choice < 0 || choice > WORKER_THREADS - 1) {
            printf("Incorrect thread id %d.\n", choice);
            exit(0);
        }

        cancel_thread(choice);
    }
}

int main() {
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < WORKER_THREADS; i++) {
        char* thread_arg = calloc(1, sizeof(char));
        *thread_arg  = i;

        const char thread_create_status = pthread_create(&threads[i], &thread_attr, write_to_file, thread_arg);

        if (thread_create_status) {
            printf("Failed to create thread %d\n", i);
            exit(-1);
        }
    }

    menu();

    return 0;
}