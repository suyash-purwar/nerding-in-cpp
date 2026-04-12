#include <stdbool.h>
#include <stdlib.h>

#include "queue.h"

Queue* init_queue() {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue -> front = -1;
    queue -> rear = -1;

    return queue;
}

bool is_full(Queue* queue) {
    return queue->rear + 1 == QUEUE_SIZE;
}

bool is_empty(Queue* queue) {
    return queue->rear == queue->front;
}

int enqueue(Queue* queue, int item) {
    if (is_full(queue)) {
        return 0;
    }

    queue->list[++queue->rear] = item;

    return 1;
}

int dequeue(Queue* queue, int* removed_item) {
    if (is_empty(queue)) {
        return 0;
    }

    const int item = queue->list[++queue->front];

    if (removed_item != NULL) {
        *removed_item = item;
    }

    queue->list[queue->front] = 0;

    if (queue->front >= queue->rear) {
        queue->front = queue->rear = -1;
    }

    return 1;
}

void clear(Queue* queue) {
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue->list[i] = 0;
    }

    queue->front = queue->rear = -1;
}

void purge(Queue* queue) {
    free(queue);
}
