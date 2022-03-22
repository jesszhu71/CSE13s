//Quick Sort

#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

uint32_t comparisons;
uint32_t moves;
uint32_t max_stack_size;
uint32_t max_queue_size;

//Partition, used for both quick_sort_stack and quick_sort_queue
//Used for spliting array into two
//Returns signed integer j
int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {

    int64_t pivot = *(A + lo + ((hi - lo) / 2)); //pivot point for splitting
    //index values i and j
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i = i + 1;
        comparisons = comparisons + 1;
        while (*(A + i) < pivot) {
            //current item in list is less than pivot point
            i = i + 1;
            comparisons = comparisons + 1;
        }
        j = j - 1;
        comparisons = comparisons + 1;
        while (*(A + j) > pivot) {
            //current item in list is greate than pivot point
            j = j - 1;
            comparisons = comparisons + 1;
        }
        if (i < j) {
            //swap being made
            int64_t temp = *(A + i);
            moves = moves + 1;
            *(A + i) = *(A + j);
            moves = moves + 1;
            *(A + j) = temp;
            moves = moves + 1;
        }
    }
    return j;
}
void quick_sort_stack(uint32_t *A, uint32_t n) {
    moves = 0;
    comparisons = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    //create stack
    Stack *st = stack_create(n);

    stack_push(st, lo);
    stack_push(st, hi);
    while (stack_size(st) != 0) { //while stack is not empty
        bool x;
        bool y;
        x = stack_pop(st, &hi);
        y = stack_pop(st, &lo);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            //lo is less than partition, enqueue lo and partition
            stack_push(st, lo);
            stack_push(st, p);
        }
        if (hi > p + 1) {
            // hi is greater than partition+1, enqueue p+1 and hi
            stack_push(st, p + 1);
            stack_push(st, hi);
        }
    }
    stack_delete(&st); //delete stack, free memory
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    moves = 0;
    comparisons = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    //create queue
    Queue *qu = queue_create(n);
    //put lo and hi in queue
    enqueue(qu, lo);
    enqueue(qu, hi);
    while (queue_size(qu) != 0) { //while queue is not empty
        bool x;
        bool y;
        //remove items from queue => lo and hi
        x = dequeue(qu, &lo);
        y = dequeue(qu, &hi);
        int64_t p = partition(A, lo, hi); //partition
        if (lo < p) {
            //lo is less than partition, enqueue lo and partition
            enqueue(qu, lo);
            enqueue(qu, p);
        }
        if (hi > p + 1) {
            // hi is greater than partition+1, enqueue p+1 and hi
            enqueue(qu, p + 1);
            enqueue(qu, hi);
        }
    }
    queue_delete(&qu); // delete queue, free memory
}
