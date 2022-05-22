# Assignment 3

Link to assignment instructions [pdf] (https://github.com/jesszhu71/CSE13s/blob/main/asgn3/assignments_asgn3.pdf)

For this assignment, I created 4 difference sorting methods: Bubble sort, Shell Sort, Quicksort (using stack), and Quicksort (using queue).

## Build

	$ make

## Running

	$ ./sorting [-absqQ] [-n length] [-p elements] [-r seed]

 **COMMAND LINE OPTIONS:**
 - -a: Enables all tests
 - -b: Enables Bubble Sort
 - -s: Enables Shell Sort
 - -q: Enables Quicksort that utilizes a stack
 - -Q: Enables Quicksort that utilitzes a queue
 - -r seed: Set the random seed to *seed*. Default seed is 13371453.
 - -n size: Set the array size to *size*. Default size is 100.
 - -p elements: Prints out *elements* number of elements from array. Default number of elements is 100.

## Cleaning

	$ make clean
