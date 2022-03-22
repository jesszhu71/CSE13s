//Path

#include "path.h"

#include "graph.h"
#include "recursion.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Path Structure
struct Path {
    Stack *vertices;
    uint32_t length;
};

// Creates path
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        //Initialize values
        p->vertices = stack_create(VERTICES + 1);
        p->length = 0;
        if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

// Deletes path, no mem leaks
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

// Pushes a vertex to said path
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t previous = 0;
    bool success;
    bool not_empty;
    //Get current top item (will be to get graph_edge_weight)
    not_empty = stack_peek(p->vertices, &previous);
    //Add v to path's stack
    success = stack_push(p->vertices, v);
    // Increments path length (only if there are 2 or more items in stack)
    if (not_empty && success) {
        p->length = p->length + graph_edge_weight(G, previous, v);
    }
    return success;
}

// Removes most recent vertex in path
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x = 0; //*x?
    uint32_t new = 0;
    if (stack_peek(p->vertices, &x)) { // Stack is not empty
        //V is the removed vertex
        stack_pop(p->vertices, v);
        //Current new vertex
        stack_peek(p->vertices, &new);
        p->length = p->length - graph_edge_weight(G, new, *v);
        return true;
    }
    //Stack is empty, can't pop
    return false;
}

// Returns number of vertices in stack
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Returns the length of current path
uint32_t path_length(Path *p) {
    return p->length;
}

// Makes a copy of the src path at dst path
void path_copy(Path *dst, Path *src) {
    //makes copy of stack
    stack_copy(dst->vertices, src->vertices);
    //makes copy of length
    dst->length = src->length;
}

//Prints the path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
}
