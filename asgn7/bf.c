// BloomFilter ADT

#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// Contructs the bf, given in asgn doc
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

// Deletes the bf, frees memory
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free((*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

// Returns size of bf
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Inserts a word into filter
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Hash using three salts
    uint32_t map_1 = hash(bf->primary, oldspeak) % bv_length(bf->filter);
    uint32_t map_2 = hash(bf->secondary, oldspeak) % bv_length(bf->filter);
    uint32_t map_3 = hash(bf->tertiary, oldspeak) % bv_length(bf->filter);

    // Set bits with obtained hash index for each salt
    bv_set_bit(bf->filter, map_1);
    bv_set_bit(bf->filter, map_2);
    bv_set_bit(bf->filter, map_3);
}

// Returns whether a word is in the bf
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Hash using the three salts
    uint32_t map_1 = hash(bf->primary, oldspeak) % bv_length(bf->filter);
    uint32_t map_2 = hash(bf->secondary, oldspeak) % bv_length(bf->filter);
    uint32_t map_3 = hash(bf->tertiary, oldspeak) % bv_length(bf->filter);

    // Get bit at those hash indices
    uint8_t bit_1 = bv_get_bit(bf->filter, map_1);
    uint8_t bit_2 = bv_get_bit(bf->filter, map_2);
    uint8_t bit_3 = bv_get_bit(bf->filter, map_3);

    // Returns true if all three bits at those indices are set
    if (bit_1 == 1 && bit_2 == 1 && bit_3 == 1) {
        return true;
    } else {
        return false;
    }
}

// Returns current number of items in filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i = i + 1) {
        if (bv_get_bit(bf->filter, i) == 1) {
            count = count + 1;
        }
    }
    return count;
}

// Debugging function, prints out all items in bloom filter
void bf_print(BloomFilter *bf) {
    printf("bloom filter: ");
    bv_print(bf->filter);
}
