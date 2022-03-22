// Helper functions, given in asgn5 doc

#include "nibble.h"

#include <inttypes.h>

// Returns the lower nibble of 8 bit number
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Returns the upper nibble of 8 bit number
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Returns the upper and lower nibble put back into 8 bits
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}
