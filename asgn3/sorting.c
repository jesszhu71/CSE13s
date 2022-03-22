//Sorting

#include "bubble.h"
#include "moves.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

typedef enum SORTS {
    BUBBLE,
    SHELL,
    STACK,
    QUEUE,
} SORTS;

//Extern variables
uint32_t moves;
uint32_t comparisons;
uint32_t max_stack_size;
uint32_t max_queue_size;

//Names used for printing later
const char *names[] = { "Bubble Sort", "Shell Sort", "Quick Sort (Stack)", "Quick Sort (Queue)" };

int main(int argc, char **argv) {
    int opt = 0;
    char *string_beg; //pointer for strtoul later
    unsigned long seed = 13371453; //default seed
    uint32_t size = 100; //default size
    uint32_t elements = 100; //default elements
    Set sorts = set_empty();
    //Set with all the function names
    void (*sorts_funcs[4])(uint32_t *, uint32_t)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            // all sorting functions chosen
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, STACK);
            sorts = set_insert(sorts, QUEUE);
            break;
        case 'b':
            // bubble is chosen
            sorts = set_insert(sorts, BUBBLE);
            break;
        case 's':
            //shell is chosen
            sorts = set_insert(sorts, SHELL);
            break;
        case 'q':
            //quicksort stack is chosen
            sorts = set_insert(sorts, STACK);
            break;
        case 'Q':
            //quicksort queue is chosen
            sorts = set_insert(sorts, QUEUE);
            break;
        case 'r':
            //set seed
            seed = strtoul(optarg, &string_beg, 10);
            break;
        case 'n':
            //set set size of array
            size = strtoul(optarg, &string_beg, 10);
            break;
        case 'p':
            // set number of items to print
            elements = strtoul(optarg, &string_beg, 10);
            break;

        default: break;
        }
    }
    bool print = false; // is there going to be anything printed? used for displaying error message
    for (SORTS i = BUBBLE; i <= QUEUE; i = i + 1) {
        if (set_member(sorts, i)) { // if item is in one of our sorts
            print = true; // yes something is being printed
            srandom(seed); // set seed

            // the list that is going to be sorted
            uint32_t random_list[size];
            for (uint32_t i = 0; i < size; i = i + 1) {
                // filling the list with random values
                uint32_t a = random();
                random_list[i] = a;
            }

            printf("%s\n", names[i]); // prints the selected sort
            moves = 0; // reset current count for number of moves
            comparisons = 0; //reset current count for number of comparisons
            sorts_funcs[i](random_list, size); // run the sort with the corresponding function
            //Checks if there is a need to prints max_stack_size or max_queue_size
            if (i == BUBBLE) {
                // current sort is bubble
                printf("%u elements, %d moves, %d compares\n", size, moves, comparisons);
            } else if (i == SHELL) {
                // current sort is shell
                printf("%u elements, %d moves, %d compares\n", size, moves, comparisons);
            } else if (i == STACK) {
                // current sort is quicksort stack
                printf("%u elements, %d moves, %d compares\n", size, moves, comparisons);
                printf("Max stack size: %d\n", max_stack_size);
            } else if (i == QUEUE) {
                //current sort is quicksort queue
                printf("%u elements, %d moves, %d compares\n", size, moves, comparisons);
                printf("Max queue size: %d\n", max_queue_size);
            } else {
                //shouldn't ever reach here
                printf("There is a problem because the code shouldn't reach here\n");
            }
            //If there are more elements to print than elements in array
            if (size < elements) {
                elements = size;
            }
            //prints specified amount of item from sorted array
            for (uint32_t i = 0; i < elements; i = i + 1) {
                printf("%13" PRIu32, random_list[i]);
                if (i % 5 == 4) {
                    printf("\n");
                }
            }
        }
    }

    //No inputs were given, prints all options
    if (print == false) {
        printf("Select at least one sort to perform.\n");
        printf("SYNOPSIS\n");
        printf("    A collection of comparison-based sorting algorithms.\n");
        printf("\n");
        printf("USAGE\n");
        printf("    ./sorting [-absqQ] [-n length] [-p elements] [-r seed]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("    -a                 Enable all sorts.\n");
        printf("    -b                 Enable Bubble Sorts.\n");
        printf("    -s                 Enables Shell Sorts.\n");
        printf("    -q                 Enable Quick Sort (Stack).\n");
        printf("    -Q                 Enable Quick Sort (Queue).\n");
        printf("    -n length          Specify number of array elements\n");
        printf("    -p elements        Specify number of elements to print\n");
        printf("    -r seed            Specify random seed.\n");
        return 1; //return error
    }
    return 0; //return success
}
