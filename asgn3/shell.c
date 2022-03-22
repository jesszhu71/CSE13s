//Shell Sort

#include "shell.h"

#include "gaps.h"

#include <stdbool.h>
#include <stdint.h>

//extern variables: number of moves and comparisons
uint32_t moves;
uint32_t comparisons;

//Shell Sort
//Follow asgn doc python code
void shell_sort(uint32_t *A, uint32_t n) {
    moves = 0; //reset counter
    comparisons = 0; //reset counter
    for (int g = 0; g < GAPS; g = g + 1) { // for gap in gaps
        uint32_t curr_gap = gaps[g]; // set current gap

        //for value between current gap and length array
        for (uint32_t i = curr_gap; i < n; i = i + 1) {
            uint32_t j = i;
            int64_t temp = *(A + i); //used for the swap
            moves = moves + 1;

            //orders the current items gap spaces apart
            comparisons = comparisons + 1; // comparison made below for while loop
            while ((j >= curr_gap) && (temp < *(A + j - curr_gap))) {
                *(A + j) = *(A + j - curr_gap); //swap
                moves = moves + 1;
                j = j - curr_gap;
                comparisons = comparisons + 1; //check while loop condition
            }

            *(A + j) = temp; //swap
            moves = moves + 1;
        }
    }
}
