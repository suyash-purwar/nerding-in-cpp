#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Following is same as the last example as before but thread cancellation is performed in a Deferred Way. This way, we
 * can define points in the code where any pending thread cancellation request is checked for.
 *
 * It is there, the cleanup handlers are invoked and the cancellation sequence starts. We define these check points
 * using the `pthread_testcancel()` function. There are other cancellation points other than this, like `sleep()`,
 * `read()`, `write()`, etc.
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
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    pthread_cleanup_push(cleanup_thread_arg, th_id);

    sprintf(file_name, "./files/thread_%d.txt", thread_id);
    FILE* file = fopen(file_name, "w");

    pthread_cleanup_push(close_thread_file, file);

    if (file == NULL) {
        perror("Failed to open the file");
        exit(-1);
    }

    while (counter < 50) {
        const int file_content_len = sprintf(file_contents, "%d: This is thread %d\n", counter, thread_id);

        fwrite(file_contents, sizeof(char), file_content_len, file);
        fflush(file);

        counter++;
        sleep(1);
        pthread_testcancel();
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