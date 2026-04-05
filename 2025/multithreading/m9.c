#include <stdio.h>
#include <pthread.h>

/**
 * Example of Self-Deadlock
 */

static int resource = 10;
pthread_mutex_t lock;

void* worker() {
    pthread_mutex_lock(&lock);
    printf("First lock acquired\n");
    pthread_mutex_lock(&lock);
    printf("Never executed because of deadlock");

    resource = resource * 10;

    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t thread1;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1, NULL, worker, NULL);

    pthread_join(thread1, NULL);

    printf("Resource: %d\n", resource);
}
