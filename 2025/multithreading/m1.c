#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker1()
{
    printf("Thread1 worker\n");
    sleep(2);
    return NULL;
}

void* worker2(void* arg) {
    char* str = (char*)arg;

    while (1) {
        printf("%s\n", str);
        sleep(1);
    }
}

/**
 * Here, we have not specified whether a thread is joinable or detachable. It is recommended to explicitly define
 * a thread as joinable or detachable based on the expected behaviour as some implementations might have a different
 * default.
 *
 * A joinable thread can be made detachable through `pthread_detachable` function.
 */
int main()
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, worker1, NULL);

    /**
     * `pthread_join` function blocks the main thread untile the called thread terminates or calls pthread_exit
     * This function frees up the resources used by the thread. If this function is not called for joinable thread,
     * the thread after completing it's work becomes a zombie thread. The difference between joinable and detachable
     * thread is that detachable thread automatically frees up the resource after completing it's work whereas a
     * joinable thread doesn't
     */
    pthread_join(tid1, NULL);

    static char* string = "Thread2 worker";
    pthread_create(&tid2, NULL, worker2, (void*)string);
    /**
     * `pthread_join` is never called for thread 2 and it becomes a zombie thread. It's resources are deallocated when
     * the main thread terminates.
     */

    printf("Main thread\n");

    sleep(10);

    return 0;
}
