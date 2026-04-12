#include <stdio.h>
#include "../queue.h"

int main() {
    Queue* q1 = init_queue();
    int i1, i2;

    enqueue(q1, 10);
    enqueue(q1, 11);

    printf("%d\n", q1->front);
    printf("%d\n", q1->rear);

    dequeue(q1, &i1);

    printf("%d\n", i1);
    printf("%d\n", q1->front);

    dequeue(q1, &i2);

    printf("%d\n", i2);
    printf("%d\n", q1->front);
    printf("%d\n", q1->rear);

    if (!dequeue(q1, NULL)) {
        printf("Queue is empty\n");
    }

    for (int i = 0; i < QUEUE_SIZE; i++) {
        enqueue(q1, i * 10);
    }

    printf("%d\n", q1->front);
    printf("%d\n", q1->rear);

    if (!enqueue(q1, 100)) {
        printf("Queue is full\n");
    }

    printf("%d\n", q1->front);
    printf("%d\n", q1->rear);

    for (int i = 0; i < QUEUE_SIZE; i++) {
        int j;
        dequeue(q1, &j);
        printf("%d ", j);
    }
    printf("\n");

    printf("%d\n", q1->front);
    printf("%d\n", q1->rear);

    purge(q1);

    return 0;
}