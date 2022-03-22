//Stack

#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
uint32_t max_stack_size;

// Declare stack properties
// Given in asgn doc
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// Creates a stack size capacity
// Given in asgn doc
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    max_stack_size = 0;
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Deletes stack in memory
// Given in asgn doc
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Checks if stack is empty
//Taken from Lecture 11 Slides
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// Checks whether stack is full
//Taken from Lecture 11 Slides
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

// Returns the number of items in stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//Pushes item to stack
//Taken from Lecture 11 Slides
bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s) == false) {
        s->items[s->top] = x;
        s->top += 1;
        if (s->top > max_stack_size) {
            max_stack_size = s->top;
        }
        return true;
    }
    return false;
}

//Taken from Lecture 11 Slides
bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

//Prints the entire stack
//Demo by Eugene
void stack_print(Stack *s) {

    printf("[");
    for (uint32_t i = 0; i < s->top; i = i + 1) {
        printf("%" PRId64, s->items[i]);
        if (i + 1 != s->top) {
            printf(", ");
        }
    }
    printf("]\n");
}
