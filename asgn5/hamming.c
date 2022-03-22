//Hamming Code module

#include "hamming.h"

#include "bm.h"
#include "bv.h"
#include "nibble.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

// Encodes the message and returns the encoded message
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    // Turn the message into matrix and multiplying it
    BitMatrix *msg_matrix = bm_from_data(msg, 4);
    BitMatrix *new_msg = bm_multiply(msg_matrix, G);
    uint8_t ret = bm_to_data(new_msg);
    bm_delete(&msg_matrix);
    bm_delete(&new_msg);
    return ret;
}

// Checks for errors and corrects the errors
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    // Lookup table for checking error
    int lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };

    // Turn the message into matrix and multiply it and turn back to uint8
    BitMatrix *code_matrix = bm_from_data(code, 8);
    BitMatrix *error_matrix = bm_multiply(code_matrix, Ht);
    uint8_t error = bm_to_data(error_matrix);
    bm_delete(&error_matrix);

    // Address the error
    if (error == 0 || lookup[error] == HAM_ERR) {
        bm_delete(&code_matrix);
        // No corrections to be made, either perfect or can't be corrected
        *msg = lower_nibble(code);
        if (error == 0) {
            // Perfect, no error
            return HAM_OK;
        }
        // Too many errors, can't be corrected
        return HAM_ERR;
    } else {
        // Corrections need to be made
        int err_index = lookup[error]; // What index is my error at?
        uint8_t b_val = bm_get_bit(code_matrix, 0, err_index);

        // Set or clear bit?
        if (b_val == 1) {
            // bit at error is currently 1, make 0
            bm_clr_bit(code_matrix, 0, err_index);
        } else {
            //bit at error is currently 0, make 1
            bm_set_bit(code_matrix, 0, err_index);
        }

        *msg = lower_nibble(bm_to_data(code_matrix));
        bm_delete(&code_matrix);
        return HAM_CORRECT;
    }
}
