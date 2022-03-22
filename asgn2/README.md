# Assignment 2

For this assignment, I implement a math library for the functions arcsine, arccosine, arctangent, and log. mathlib-test tests tests numbers using both my functions and the math.h library functions and shows the difference between the two. Details about how to run the different tests in mathlib-test are under Running.

## Build

	$ make

## Running

	$ ./mathlib-test -[asctl]

 **COMMAND LINE OPTIONS:**
 - -a: to run all tests
 - -s: to run arcsin tests
 - -c: to run arccos tests
 - -t: to run arctan tests
 - -l: to run log tests

## Cleaning

	$ make clean
