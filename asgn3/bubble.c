//Bubble sort

#include "bubble.h"

#include "moves.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
uint32_t moves; //extern variable for number of moves
uint32_t comparisons; //extern variable for number of comparisons

//Bubble Sort
//Followed given asgn doc python code
void bubble_sort(uint32_t *A, uint32_t n) {
    moves = 0; //reset counter
    comparisons = 0; //reset counter
    bool swapped = true;

    while (swapped) { //loop runs until no swaps are made
        swapped = false;
        for (uint32_t i = 1; i < n; i = i + 1) {
            comparisons = comparisons + 1; //comparison being made for if statement below
            //if current pair is out of order, then swap
            if (*(A + i) < *(A + i - 1)) {
                //swap is being made
                int64_t temp = *(A + i);
                *(A + i) = *(A + i - 1);
                *(A + i - 1) = temp;
                swapped = true; //swap was made, so will keep looping
                moves = moves + 3; // a swap is three moves
            }
        }
        n = n - 1; //every round of sorting, you check 1 less item from end
    }
}
