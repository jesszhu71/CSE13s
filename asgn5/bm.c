//Bit matrix ADT

#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Taken from asgn5 doc
struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Creates the matrix, calls the bit vector ADT
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows * cols);
        if (!m->vector) {
            free(m);
            m = NULL;
        }
    }
    return m;
}

// Deletes allocated memory for this ADT
void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector);
        free((*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}

// Returns number of rows
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

// Returns number of columns
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// Changes the bit at r, c 1
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * (m->cols) + c);
}

// Changes the bit at r, c 0
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * (m->cols) + c);
}

// Gets the bit at r, c
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * (m->cols) + c);
}

// Turns a byte stored in an uint8 to a bit matrix
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i = i + 1) {
        if (byte & (1 << i)) {
            bm_set_bit(m, 0, i);
        } else {
            bm_clr_bit(m, 0, i);
        }
    }
    return m;
}

// Turns a matrix into a uint8
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t val = 0;
    for (uint32_t i = 0; i < m->cols; i = i + 1) {
        uint8_t bit = bm_get_bit(m, 0, i) << i;
        val = val | bit;
    }
    return val;
}

// Performs matrix multiplication on matrix A and B
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *product = bm_create(A->rows, B->cols);
    for (uint32_t i = 0; i < A->rows; i = i + 1) {
        for (uint32_t j = 0; j < B->cols; j = j + 1) {
            uint8_t c = 0;
            for (uint32_t k = 0; k < A->cols; k = k + 1) {
                c = c ^ ((bm_get_bit(A, i, k) & bm_get_bit(B, k, j)));
            }
            if (c) {
                bm_set_bit(product, i, j);
            }
        }
    }
    return product;
}

// Prints the matrix
void bm_print(BitMatrix *m) {
    printf("[");
    for (uint32_t i = 0; i < m->rows; i = i + 1) {
        for (uint32_t j = 0; j < m->cols; j = j + 1) {
            printf("%2" PRIu8, bm_get_bit(m, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}
