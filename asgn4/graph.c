//Graph

#include "graph.h"

#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Graph structure
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// Creates graph
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    assert(G);
    if (G) {
        // initialize structure values
        G->vertices = vertices;
        G->undirected = undirected;
        // Makes everything in visited false, matrix 0
        for (int i = 0; i < VERTICES; i = i + 1) {
            G->visited[i] = false;
            for (int j = 0; j < VERTICES; j = j + 1) {
                G->matrix[i][j] = 0;
            }
        }
    }
    return G;
}

//Deletes the graph, no memleaks
void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
        return;
    }
}

// Returns the number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

//Adds edge to matrix
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((i < G->vertices) && (j < G->vertices)) {
        //vertex i and j are in bounds
        G->matrix[i][j] = k;
        if (G->undirected) {
            //undirected
            G->matrix[j][i] = k;
        }
        return true;
    }
    //vertex i and j are not in bounds
    return false;
}

// Graph has an edge at i, j
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    // Are i, j in bounds and non-zero?
    if ((i < G->vertices) && (j < G->vertices) && (G->matrix[i][j] != 0)) {
        // Yes, thus has edge
        return true;
    }
    // No, thus no edge
    return false;
}

// Returns the weight at i, j
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (graph_has_edge(G, i, j)) {
        //edge exists
        return G->matrix[i][j];
    }
    //edge doesn't exist
    return 0;
}

// vertex v has been visited
bool graph_visited(Graph *G, uint32_t v) {
    // Is v in bounds?
    if (v >= G->vertices) {
        //Nope, return false always
        return false;
    }
    //Yes, return the bool value in visited array
    return G->visited[v];
}

// Marks the graph visited at vertex v
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        // v is in bounds, mark visited at v true
        G->visited[v] = true;
    }
    return;
}

// Marks the graph not visited at vertex v
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        //v is in bounds, mark visited at v false
        G->visited[v] = false;
    }
    return;
}

//Prints graph
void graph_print(Graph *G) {
    for (int i = 0; i < VERTICES; i = i + 1) {
        printf("|");
        for (int j = 0; j < VERTICES; j = j + 1) {
            printf("%2" PRIu32, G->matrix[i][j]);
        }
        printf("|\n");
    }
    return;
}
