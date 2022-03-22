//Queue

#include "queue.h"

#include "moves.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t max_queue_size;

//Declares queue properties
//Given in asgn doc
struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

// Creates a queue size capacity
// I referenced the lecture slides and given stack_create structure
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    max_queue_size = 0;
    if (q) {
        q->head = q->tail = 0; //head and tail starts at 0
        q->capacity = capacity;
        q->size = 0;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

// Deletes the queue in memory
// Referenced the stack_delete structure
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        //free the stack
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

// Checks if queue is empty
// Referenced Lecture 11 Slides
bool queue_empty(Queue *q) {
    if (q) {
        return q->head == q->tail;
    }
    return true;
}

//Checks if queue is full
// Referenced Lecture 11 slides
bool queue_full(Queue *q) {
    if (q) {
        return (q->head + 1) % q->capacity == q->tail;
    }
    return true;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

//Enqueues item x, returns true if successful
// Followed Lecture 11 slides
bool enqueue(Queue *q, int64_t x) {
    if (q) {
        if (queue_full(q)) {
            return false;
        }
        q->items[q->head] = x;
        q->head = (q->head + 1) % q->capacity;
        q->size = q->size + 1;
        if (queue_size(q) > max_queue_size) {
            max_queue_size = q->size;
        }
        return true;
    } else {
        return false;
    }
}

// Dequeues an item, sets x pointer to that item, returns true if successful
// Followed Lecture 11 Slides
bool dequeue(Queue *q, int64_t *x) {
    if (q) {
        if (queue_empty(q)) {
            return false;
        }
        *x = q->items[q->tail];
        q->tail = (q->tail + 1) % q->capacity;
        q->size = q->size - 1;
        return true;
    } else {
        return false;
    }
}

// Prints the entire queue, tail to head
// Followed structure of stack_print code
void queue_print(Queue *q) {
    printf("[");
    for (uint32_t i = q->tail; i != q->head; i = (i + 1) % q->capacity) {
        printf("%" PRId64, q->items[i]);
        if (i + 1 != q->head) {
            printf(", ");
        }
    }
    printf("]\n");
}
