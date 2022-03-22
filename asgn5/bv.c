// Bit vector ADT
#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Struct for ADT
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Creates the bit vector
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

// Deletes the allocated space for bit vector
void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}

// Returns the length of the bit vector
uint32_t bv_length(BitVector *v) {
    return v->length;
}

// Changes the bit at index i to 1
void bv_set_bit(BitVector *v, uint32_t i) {

    v->vector[i / 8] = v->vector[i / 8] | (1 << (i % 8));
}

// Changes the bit at index i to 0
void bv_clr_bit(BitVector *v, uint32_t i) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t temp = 1;
    temp = ~(temp << position);
    v->vector[location] = v->vector[location] & temp;
}

// XORs the bit at index i with bit
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    bit = bit << position;
    v->vector[location] = v->vector[location] ^ bit;
}

// Gets the bit at index i
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t temp = (1 << position) & v->vector[location];
    temp = temp >> position;
    return temp;
}

// Prints the vector
void bv_print(BitVector *v) {
    printf("[");
    for (uint32_t i = 0; i < v->length; i = i + 1) {
        printf("%d ", bv_get_bit(v, i));
    }
    printf("]\n");
}
