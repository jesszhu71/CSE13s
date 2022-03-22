//Jessie Zhu
//Spring 2021

#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// THIS WAS GIVEN TO US IN THE DOC
// Returns position of player to the left.
// pos: position of current player.
// players: number of players in the game.
static inline uint8_t left(uint8_t position, uint8_t players) {
    return ((position + players - 1) % players);
}

// THIS WAS GIVEN TO US IN THE DOC
//Returns position of player to the right
//pos: Position of current player
//players: number of players in the game.
static inline uint8_t right(uint8_t position, uint8_t players) {
    return ((position + 1) % players);
}

//Returns a number between 0-5, for the sides of a dice
static inline uint8_t roll() {
    return random() % 6;
}

//Dice faces, from the pdf
typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

int main(void) {
    //i, for loop variable
    //curr, the current player's index (0 through number of players-1)
    //num_players, total number of players
    //active_players, total people who still have money in the game, active players
    //center, center pot of money
    //seed, seed number entered
    //seed_u, unsigned seed number
    int i, curr, num_players, active_players, center;
    int64_t seed;

    // Random Seed, player enters seed number, check if number is negative
    printf("Random seed: ");
    scanf("%ld", &seed); // Reads number inputed
    if (seed < 1) { // Random seed error statement
        printf("Pseudorandom seed must be non-negative (%ld).\n", seed);
        return 1;
    }
    uint32_t seed_u
        = seed; // Convert int64_t to uint32_t (SOMETHING SOMEONE MENTIONED IN A PIAZZA POST)
    srandom(seed_u); // Set seed

    // Number of players, limited to 2-14 players
    printf("How many players? ");
    scanf("%d", &num_players); // Reads number inputed
    if (num_players <= 1 || num_players > 14) { // Number of players error statement
        printf("Number of players must be from 1 to 14.\n");
        return 1;
    }
    int money[num_players]; // money, the bank for all players

    for (i = 0; i < num_players; i = i + 1) { // Each player starts with $3
        money[i] = 3;
    }

    active_players = num_players; // All players are active at beginning of game
    curr = 0; // Index of current player
    center = 0; // Center pot money starts empty

    // While loop keeps the game going, until there is only 1 person with money left
    while (active_players > 1) {
        if (money[curr] >= 3) { // Player has $3+
            printf("%s rolls...", philosophers[curr]);
            for (int turn = 0; turn < 3; turn = turn + 1) { // Roll 3 times
                // THIS PART REPEATS 3X BELOW, so I only commented this chuck (MARKED * and **)

                // This chuck of code handles rolling once. Four cases: LEFT, RIGHT, CENTER, PASS.
                uint8_t side = die[roll()]; // Dice is rolled, stored in variable side

                if (side == LEFT) {
                    //Rolled side is left
                    uint8_t left_player = left(curr, num_players); // Gets player to the left
                    money[curr] = money[curr] - 1; // Decrement current player's $
                    money[left_player] = money[left_player] + 1; //Increments left player's $

                    // If left player has $1 after gaining $1, they have returned as an active player
                    if (money[left_player] == 1) {
                        active_players = active_players + 1;
                    }
                    printf(" gives $1 to %s", philosophers[left_player]);
                } else if (side == RIGHT) {
                    // Side rolled is RIGHT
                    uint8_t right_player = right(curr, num_players); // Gets player to the right
                    money[curr] = money[curr] - 1; //Decrements current player's $
                    money[right_player] = money[right_player] + 1; //Increments right player's $

                    // if right player has $1 after gaining $1, they have returned as an active player
                    if (money[right_player] == 1) {
                        active_players = active_players + 1;
                    }
                    printf(" gives $1 to %s", philosophers[right_player]);

                } else if (side == CENTER) {
                    // Side rolled is CENTER
                    money[curr] = money[curr] - 1; // Decrements current player's $
                    center = center + 1; // Increments pot's money
                    printf(" puts $1 in the pot");
                } else {
                    // Side rolled is PASS, nothing happens
                    printf(" gets a pass");
                }
            }

            // After turn, if current player has 0 dollars, then decrement active player counter
            if (money[curr] == 0) {
                active_players = active_players - 1;
            }
            printf("\n");
            // END OF REPEAT CHUNK

        } else if (money[curr] == 2) { // Player has $2
            printf("%s rolls...", philosophers[curr]);
            for (int turn = 0; turn < 2; turn = turn + 1) { //Roll 2 times

                // *REPEAT FROM ABOVE
                uint8_t side = die[roll()];
                if (side == LEFT) {
                    uint8_t left_player = left(curr, num_players);
                    money[curr] = money[curr] - 1;
                    money[left_player] = money[left_player] + 1;
                    if (money[left_player] == 1) {
                        active_players = active_players + 1;
                    }
                    printf(" gives $1 to %s", philosophers[left_player]);
                } else if (side == RIGHT) {
                    uint8_t right_player = right(curr, num_players);
                    money[curr] = money[curr] - 1;
                    money[right_player] = money[right_player] + 1;
                    if (money[right_player] == 1) {
                        active_players = active_players + 1;
                    }
                    printf(" gives $1 to %s", philosophers[right_player]);
                } else if (side == CENTER) {
                    money[curr] = money[curr] - 1;
                    center = center + 1;
                    printf(" puts $1 in the pot");
                } else {
                    printf(" gets a pass");
                }
            }
            if (money[curr] == 0) {
                active_players = active_players - 1;
            }
            printf("\n");
            // *END OF REPEAT*

        } else if (money[curr] == 1) {
            printf("%s rolls...", philosophers[curr]);

            // **REPEAT FROM ABOVE**
            uint8_t side = die[roll()];
            if (side == LEFT) {
                uint8_t left_player = left(curr, num_players);
                money[curr] = money[curr] - 1;
                money[left_player] = money[left_player] + 1;
                if (money[left_player] == 1) {
                    active_players = active_players + 1;
                }
                printf(" gives $1 to %s", philosophers[left_player]);
            } else if (side == RIGHT) {
                uint8_t right_player = right(curr, num_players);
                money[curr] = money[curr] - 1;
                money[right_player] = money[right_player] + 1;
                if (money[right_player] == 1) {
                    active_players = active_players + 1;
                }
                printf(" gives $1 to %s", philosophers[right_player]);
            } else if (side == CENTER) {
                money[curr] = money[curr] - 1;
                center = center + 1;
                printf(" puts $1 in the pot");
            } else {
                printf(" gets a pass");
            }
            if (money[curr] == 0) {
                active_players = active_players - 1;
            }

            printf("\n");
            // **END OF REPEAT**
        }

        curr = (curr + 1) % num_players; //Next player's index
    }

    // Winner, diplays winner name, $ won
    for (i = 0; i < num_players; i = i + 1) { // Checks each player's balance for winner
        if (money[i] > 0) { // current player is winner if the balance is not 0
            printf("%s wins the $%d pot with $%d left in the bank!", philosophers[i], center,
                money[i]);
            printf("\n");
            break;
        }
    }
    return 0;
}
