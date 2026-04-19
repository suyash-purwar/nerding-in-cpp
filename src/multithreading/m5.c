#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int level;
  pthread_t* caller_thread;
} RecursiveThreadArg;

void* recursive_worker(void* arg) {
  RecursiveThreadArg* arguments = arg;

  // TODO: Receive base condition via callback
  if (arguments -> level <= 0) {
    pthread_exit(NULL);
  }

  pthread_t thread;
  pthread_attr_t thread_attr;

  pthread_attr_init(&thread_attr);
  pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);

  RecursiveThreadArg* child_thread_args = malloc(sizeof(RecursiveThreadArg));
  child_thread_args -> level = arguments -> level - 1;
  child_thread_args -> caller_thread = &thread;

  if (
    pthread_create(&thread, &thread_attr, recursive_worker, child_thread_args)
  ) {
    printf("Failed to create recursive thread at depth %d\n", arguments -> level);
    exit(-1);
  }

  /**
   * Some dummy processing that will be extracted out
   * Recursive Worker will just be the orchestrator
   */
  double result = 0;
  for (int i = 1; i <= arguments -> level * 1e6; i++) {
    result += i + sin(i);
  }

  if (
    pthread_join(thread, NULL)
  ) {
    printf("Failed to join recursive thread at depth %d\n", arguments -> level);
    exit(-1);
  }

  printf("Result from Level %d: %f\n", arguments -> level, result);

  free(child_thread_args);
}

int main() {
  pthread_t recursive_thread;
  pthread_attr_t recursive_thread_attr;
  RecursiveThreadArg* recursive_thread_arg = malloc(sizeof(RecursiveThreadArg));

  recursive_thread_arg -> level = 5;
  recursive_thread_arg -> caller_thread = NULL;

  pthread_attr_init(&recursive_thread_attr);
  pthread_attr_setdetachstate(&recursive_thread_attr, PTHREAD_CREATE_JOINABLE);

  if (
    pthread_create(&recursive_thread, &recursive_thread_attr, recursive_worker, recursive_thread_arg)
  ) {
    printf("Failed to create recursive thread\n");
    exit(-1);
  }

  if (
    pthread_join(recursive_thread, NULL)
  ) {
    printf("Failed to join recursive thread\n");
    exit(-1);
  }

  free(recursive_thread_arg);

  return 0;
}