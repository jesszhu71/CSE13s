//Encode
#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "nibble.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool not_option = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //h selected
            help = true;
            break;
        case 'i':
            //i is selected
            infile = fopen(optarg, "rb");
            if (infile == NULL) {
                fprintf(stderr, "ERROR INFILE\n");
                return 1;
            }
            break;
        case 'o':
            //o is selected
            outfile = fopen(optarg, "wb");
            if (outfile == NULL) {
                fprintf(stderr, "ERROR OUTFILE\n");
                return 1;
            }
            break;
        default:
            // Something not an option selected
            not_option = true;
            break;
        }
    }

    // Prints SYNOPSIS if help or non-option flag selected
    if (help || not_option) {
        printf("SYNOPSIS\n");
        printf("  A Hamming(8, 4) systematic code generator.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./encode [-h] [-i infile] [-o outfile]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -i infile      Input data to encode.\n");
        printf("  -o outfile     Output of encoded data.\n");

        // CLOSE ALL FILES HERE and end
        fclose(infile);
        fclose(outfile);
        if (not_option) {
            return 1;
        }
        return 0;
    }

    // Create Matrix G for encoding
    BitMatrix *G = bm_create(4, 8);

    // Array for reference for creating G
    uint8_t g_values[32] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 0, 1, 1, 1, 1, 0 };

    // set all items in matrix G
    for (uint32_t i = 0; i < 32; i = i + 1) {
        uint32_t row = i / 8;
        uint32_t col = i % 8;
        // If this item in matrix is 1, set the item in matrix
        if (g_values[i] == 1) {
            bm_set_bit(G, row, col);
        }
    }

    // Reads and encodes all characters
    while (true) {
        //Read character from file
        uint8_t read_char = fgetc(infile);
        if (feof(infile)) {
            break;
        }

        // Split character into upper and lower nibble
        uint8_t upper = upper_nibble(read_char);
        uint8_t lower = lower_nibble(read_char);

        // Encode read character
        uint8_t en_up = ham_encode(G, upper);
        uint8_t en_lo = ham_encode(G, lower);

        // Encoded characters into outfile
        fputc(en_lo, outfile);
        fputc(en_up, outfile);
    }

    //Done, close files delete everything

    // File permission stuff
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    fclose(infile);
    fclose(outfile);

    bm_delete(&G);
    return 0;
}
