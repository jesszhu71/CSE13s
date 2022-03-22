//Main
#include "graph.h"
#include "path.h"
#include "recursion.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
#define BLOCK   1024

//Extern variable
uint32_t rec_calls;

//DFS, recursion function that goes through all paths
void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, bool verbose, char *cities[], FILE *outfile) {
    rec_calls = rec_calls + 1; //increment the rec calls

    // Mark current vertex as visited, add to path
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    uint32_t x = 0; // Placeholder for pop functions

    //All locations have been visited, now need connect path to start
    if (graph_has_edge(G, v, 0) && path_vertices(curr) == graph_vertices(G)) {
        //Add start to end of path
        path_push_vertex(curr, 0, G);
        //Is current path shorter?
        if (path_length(curr) < path_length(shortest) || path_vertices(shortest) == 0) {
            // Since shorter, copy current path into shortest path
            path_copy(shortest, curr);
            // Verbose print
            if (verbose) {
                path_print(shortest, outfile, cities);
            }
        }
        //Pop off the START_VERTEX from
        path_pop_vertex(curr, &x, G);
    }

    //Check all possible adjacent vertices
    for (uint32_t w = 0; w < graph_vertices(G); w = w + 1) {
        //vertex viable?: exists, and visited, current path shorter or shortest path DNE
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)
            && (path_length(curr) < path_length(shortest) || path_vertices(shortest) == 0)) {
            // recursive call with next vertex
            dfs(G, w, curr, shortest, verbose, cities, outfile);
        }
    }

    //Pop off and remove the current vertex
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &x, G);
    return;
}

void end(Graph *G, Path *curr, Path *shortest, char *cities[], uint32_t num_cities, FILE *infile,
    FILE *outfile) {
    // Delete paths
    graph_delete(&G);
    // Delete graphs
    path_delete(&curr);
    path_delete(&shortest);
    // Delete cities
    for (uint32_t i = 0; i < num_cities; i = i + 1) {
        free(cities[i]);
    }
    // Close files
    fclose(infile);
    fclose(outfile);
    return;
}

int main(int argc, char **argv) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool help = false;
    bool verbose = false;
    bool undirected = false;
    bool not_option = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //h is selected
            help = true;
            break;
        case 'v':
            //v is selected
            verbose = true;
            break;
        case 'u':
            // u is selected
            undirected = true;
            break;
        case 'i':
            //i is selected
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return 1;
            }
            break;

        case 'o':
            // o is selected
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error: failed to outfile.\n");
                return 1;
            }
            break;
        default: not_option = true; break;
        }
    }

    //Help is needed
    if (help || not_option) {
        //Help text
        printf("SYNOPSIS\n");
        printf("  Traveling Salesman Problem using DFS.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -u             Use undirected graph.\n");
        printf("  -v             Enable verbose printing.\n");
        printf("  -h             Program usage and help.\n");
        printf("  -i infile      Input containing graph (default: stdin)\n");
        printf("  -o outfile     Output of computed graph (default: stdout)\n");

        fclose(infile);
        fclose(outfile);

        //A wrong option was selected
        if (not_option) {
            return 1;
        }
        return 0;
    }

    //READING FILE/STDIN INPUT:
    char buffer[1024]; //For reading the file
    uint32_t num_cities = 100; // Total number of cities given
    //NOTE: default 100 because if unchanged, then it will be an error

    // Get number of cities, read first line of file
    fscanf(infile, "%d\n", &num_cities);

    //Create graph and paths and array for cities
    Path *curr = path_create();
    Path *shortest = path_create();
    Graph *G = graph_create(num_cities, undirected);
    char *cities[num_cities];

    //Validate number of cities
    if (num_cities >= VERTICES || num_cities < 0) {
        printf("Error: malformed number of vertices.\n");
        end(G, curr, shortest, cities, 0, infile, outfile);
        return 1;
    }

    //Intake names of cities
    char *city_error;
    for (uint32_t i = 0; i < num_cities; i = i + 1) {
        city_error = fgets(buffer, BLOCK, infile);
        //Check for malformed city name
        if (!city_error) {
            printf("Error malformed city name.\n");
            // Close and delete everything, error exit
            end(G, curr, shortest, cities, i, infile, outfile);
            return 1;
        }
        //Remove the \n at end of name and make copy for list
        char *dup = strndup(buffer, strlen(buffer) - 1);
        cities[i] = dup;
    }

    //Adding each ijk to graph
    //Structure follows Eugene's demo
    uint32_t i, j, k;
    int c; // number of inputted numbers, should be three if legitimate
    while ((c = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != EOF) {
        //Error edge, not three inputs or edge not able to add, close and delete everything
        if (c != 3 || !graph_add_edge(G, i, j, k)) {
            printf("Error: malformed edge.\n");
            end(G, curr, shortest, cities, num_cities, infile, outfile);
            return 1;
        }
    }

    //Prepare for recursion
    uint32_t v = START_VERTEX;
    rec_calls = 0;

    //Call dfs for path finding recursion
    dfs(G, v, curr, shortest, verbose, cities, outfile);

    //Can't go anywhere if num cities is 0 or 1
    if (num_cities == 0 || num_cities == 1) {
        fprintf(outfile, "There's nowhere to go.\n");

        //Error, free memory and exit
        end(G, curr, shortest, cities, num_cities, infile, outfile);
        return 1;
    }

    //Shortest path printing
    if (path_vertices(shortest) != 0) {
        //Yes shortest path found
        path_print(shortest, outfile, cities);
    } else {
        //No shortest path found
        fprintf(outfile, "Hamiltonian path not found.\n");
    }
    // Print out total recursive calls
    fprintf(outfile, "Total recursive calls: %d\n", rec_calls);

    //Success, clear memory and exit
    end(G, curr, shortest, cities, num_cities, infile, outfile);
    return 0;
}
