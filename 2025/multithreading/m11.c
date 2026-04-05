#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int resource = 100;

void release_lock() {
    pthread_mutex_unlock(&lock);
}

void* worker(void* arg) {
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    int thread_id = *(int*)arg;

    printf("Thread %d worker triggered\n", thread_id);

    pthread_mutex_lock(&lock);
    pthread_cleanup_push(release_lock, NULL);

    printf("Thread %d mutex triggered\n", thread_id);

    resource = resource + sin(resource);

    sleep(1); // Cancel Point 1

    pthread_testcancel(); // Cancel Point 2

    pthread_cleanup_pop(1);

    printf("Unlocked\n");

    return NULL;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    int thread1_arg = 1;
    int thread2_arg = 2;

    void* thread_1_retval;
    void* thread_2_retval;

    pthread_create(&thread1, NULL, worker, &thread1_arg);
    pthread_create(&thread2, NULL, worker, &thread2_arg); // Gets deadlocked

    pthread_cancel(thread1);

    pthread_join(thread1, &thread_1_retval);

    if (thread_1_retval == PTHREAD_CANCELED) {
        printf("Thread 1 is cancelled without releasing the lock\n");
    }

    pthread_join(thread2, &thread_2_retval);

    printf("Thread 2 is never joined as it starves for the mutex to unlock\n");

    return 0;
}