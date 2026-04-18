#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Detached threads are just like regular threads. The only difference between a Joinable thread and Detachable thread
 * is who owns the responsibility for thread cleanup. When `pthread_join` is called by the caller thread, resources
 * consumed by the child thread are deallocated once it exits. In the case of Detachable threads, resources are
 * reclaimed automatically by the child thread itself once it completes its work.
 *
 * When a thread is detached
 *  1) It's exit status is discarded and cannot be accessed by the caller thread
 *  2) It's resources (stack, TCB) are reclaimed automatically when it finishes
 *  3) No thread can `pthread_join` it
 *
 *  We use detached thread when we don't care about the result produced by the thread.
 *
 *  Use cases
 *  1. Background Housekeeping work: Logging, Metrics reporting, Cache cleanup
 *  2. Event-driven tasks: Accept connection -> Spawn Thread to handle it E2E. Fire and forget situation
 */
void* worker() {
  int result = 0;

  for (int i = 0; i < 1e7; i++) {
    result += i;
  }

  printf("Result: %d\n", result);

  return NULL;
}

int main() {
  pthread_t thread1;
  pthread_attr_t thread1_attr;

  pthread_attr_init(&thread1_attr);
  /**
   * Marking the thread as detached here.
   * Alternatively, a thread can be marked as detached using `pthread_detach(thread1)`
   */
  pthread_attr_setdetachstate(&thread1_attr, PTHREAD_CREATE_DETACHED);

  int thread_creation_status = pthread_create(&thread1, &thread1_attr, worker, NULL);
  if (thread_creation_status) {
    printf("Failed to create detached thread\n");
  }

  printf("Main thread completed\n");

  pthread_exit(0);
}