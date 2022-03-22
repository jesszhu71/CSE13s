# Assignment 1

This program simulates the Left, Right, and Center.
Left, Right, and Center is a game where there are 2-14 people in a circle.
The game begins and the user must enter a random seed and then the number of players.
Every player starts with $3 dollars and takes turns in a circle to roll a dice (3 times if they have $3+, 2 times if they have $2, 1 time if they have $1, 0 times if they have $0.) There are 4 possibilities each time someone rolls the 6-sided dice once.
	1. LEFT means player gives person to the left $1
	2. RIGHT means player gives person to the right $1
	3. CENTER means player puts $1 into the center pot
	4. PASS means player doesn’t do anything
The game repeats until there is only one person that has $, and that person is the winner which will be printed out, with the amount of money they won.

## Build

	$ clang -Wall -Wextra -Werror -Wpedantic -o lrc lrc.c

## Running

	$ ./lrc

## Cleaning

	$ rm -f lrc lrc.o
