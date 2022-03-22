// Bit Vector ADT

#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Copied from asgn5

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Constructs a vector
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    if (v) {
        v->length = length;
        int val = length / 8;
        if (length % 8 != 0) {
            val = val + 1;
        }
        v->vector = (uint8_t *) calloc(val, sizeof(uint8_t));
        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

// Deletes the vector in memory
void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

// Returns length of vector
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// Sets the bit at index i to 1
void bv_set_bit(BitVector *bv, uint32_t i) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t temp = 1 << position;
    bv->vector[location] = bv->vector[location] | temp;
}

// Sets teh bit at index i to 0
void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t temp = ~(1 << position);
    bv->vector[location] = bv->vector[location] & temp;
}

// Returns the bit at index i
uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t temp = (1 << position) & bv->vector[location];
    temp = temp >> position;
    return temp;
}

// Prints the BitVector
void bv_print(BitVector *bv) {
    printf("[");
    for (uint32_t i = 0; i < bv->length; i = i + 1) {
        printf("%d ", bv_get_bit(bv, i));
    }
    printf("]\n");
}
