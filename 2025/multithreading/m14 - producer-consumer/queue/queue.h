#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_SIZE 5

typedef struct {
    int list[QUEUE_SIZE];
    int front;
    int rear;
    pthread_mutex_t lock;
    pthread_cond_t cv;
} Queue;

Queue* init_queue();

bool is_full(Queue*);

bool is_empty(Queue*);

int enqueue(Queue*, int);

int dequeue(Queue*, int*);

void clear(Queue*);

void purge(Queue*);

#endif //QUEUE_H
