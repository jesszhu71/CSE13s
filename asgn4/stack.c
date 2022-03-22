//Stack

#include "stack.h"

#include "path.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Structure
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// Creates stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        // Initialize stack values
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Free the stack, no mem leaks
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Returns the number of items in stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Returns if stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// Returns if stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

// Pushes x to stack
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s) == false) {
        // Stack is not full, can add
        s->items[s->top] = x;
        s->top = s->top + 1;
        return true;
    }
    //Stack is full, can't add
    return false;
}

// Removes item from stack
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        // Stack is empty, can't pop
        return false;
    }
    //Stack is not empty, can pop
    s->top = s->top - 1;
    *x = s->items[s->top];
    return true;
}

// Peeks the top item in stack
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        //Stack is empty, nothing to point to
        return false;
    }
    // Stack is not empty, point to top item
    *x = s->items[s->top - 1];
    return true;
}

// Makes a copy of the stack from src to dst
void stack_copy(Stack *dst, Stack *src) {
    // Copy the top variable
    dst->top = src->top;
    // Copy capacity variable
    dst->capacity = src->capacity;
    // Copy every single item in stack
    for (uint32_t i = 0; i < src->capacity; i = i + 1) {
        dst->items[i] = src->items[i];
    }
}

//Prints the path way
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
