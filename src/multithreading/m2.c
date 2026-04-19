#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void* worker(void* arg) {
  printf("Thread %d: Executing\n", *(int*)arg);

  const int thread_id = *(int*)arg;
  void* result = calloc(1, sizeof(double));

  for (int i = 0; i < 1000000; i++) {
    *(double*)result += sin(thread_id) + tan(thread_id);
  }

  printf("Thread %d: Completed\n", thread_id);

  free(arg);
  pthread_exit(result);
}

int main() {
  pthread_t thread[NUM_THREADS];
  void* thread_result[NUM_THREADS];

  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < NUM_THREADS; i++) {
    printf("Thread %d: Creating\n", i);

    void* thread_arg = malloc(sizeof(int));
    *(int*)thread_arg = i;

    const int creation_status = pthread_create(&thread[i], &attr, worker, thread_arg);

    if (creation_status) {
      printf("Thread %d: Unable to create thread\n", i);
    }
  }

  pthread_attr_destroy(&attr);

  for (int i = 0; i < NUM_THREADS; i++) {
    const int join_status = pthread_join(thread[i], &thread_result[i]);

    if (join_status) {
      printf("Thread %d: Unable to join thread\n", i);
    }
  }

  printf("Results from threads:-\n");
  for (int i = 0; i < NUM_THREADS; i++) {
    printf("Thread %d: Result - %f\n", i, *(double*)thread_result[i]);

    free(thread_result[i]);
  }

  return 0;
}
