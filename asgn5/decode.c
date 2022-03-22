//Decode

#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "nibble.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

//Extern vars:

double processed;
double uncorrected;
double corrected;

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool not_option = false;
    bool v = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'h':
            // h is selected
            help = true;
            break;
        case 'i':
            // i  is selected
            infile = fopen(optarg, "rb");
            if (infile == NULL) {
                fprintf(stderr, "ERROR INFILE\n");
                return 1;
            }
            break;
        case 'o':
            // o is selected
            outfile = fopen(optarg, "wb");
            if (outfile == NULL) {
                fprintf(stderr, "ERROR OUTFILE\n");
                return 1;
            }
            break;
        case 'v':
            // v is selected
            v = true;
            break;
        default:
            // Something not an option was selected
            not_option = true;
            break;
        }
    }

    // Will print the SYNOPSIS
    if (help || not_option) {
        printf("SYNOPSIS\n");
        printf("  A Hamming(8, 4) systematic code decoder.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -v             Print statistics of decoding to stderr.\n");
        printf("  -i infile      Input data to encode.\n");
        printf("  -o outfile     Output of encoded data.\n");

        // Close all files here
        fclose(infile);
        fclose(outfile);
        if (not_option) {
            return 1;
        }
        return 0;
    }

    // Creates decoding matrix H
    BitMatrix *H = bm_create(8, 4);

    // Array to help create matrix H
    uint8_t h_values[32] = { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 1 };

    // Puts a sets an item in matrix wherever it should be 1
    for (uint32_t i = 0; i < 32; i = i + 1) {
        uint32_t row = i / 4;
        uint32_t col = i % 4;
        if (h_values[i] == 1) {
            bm_set_bit(H, row, col);
        }
    }

    // Stats trackers
    processed = 0;
    corrected = 0;
    uncorrected = 0;

    // Infinite loop for reading and decoding the input file
    while (true) {
        //Read upper and lower character from file

        uint8_t lower_char = fgetc(infile);
        uint8_t upper_char = fgetc(infile);

        //Stops reading when end of file is reached
        if (feof(infile)) {
            break;
        }

        uint8_t upper = 0;
        uint8_t lower = 0;

        // Decodes upper character and lower character
        HAM_STATUS status_up = ham_decode(H, upper_char, &upper);
        HAM_STATUS status_lo = ham_decode(H, lower_char, &lower);

        // PUT STATS HERE, catch statuses in above code
        processed = processed + 2;

        //Check hamming decode status for upper nibble.
        if (status_up == HAM_ERR) {
            uncorrected = uncorrected + 1;
        } else if (status_up == HAM_CORRECT) {
            corrected = corrected + 1;
        }

        // Check hamming decode status for lower nibble
        if (status_lo == HAM_ERR) {
            uncorrected = uncorrected + 1;
        } else if (status_lo == HAM_CORRECT) {
            corrected = corrected + 1;
        }

        // Print recovered character into output
        fputc(pack_byte(upper, lower), outfile);
    }

    // PRINT STATISTICS TO STDERR HERE!
    double rate = uncorrected / processed;
    if (v) {
        fprintf(stderr, "Total bytes processed: %.0f\n", processed);
        fprintf(stderr, "Uncorrected errors: %.0f\n", uncorrected);
        fprintf(stderr, "Corrected errors: %.0f\n", corrected);
        fprintf(stderr, "Error rate: %8.6f\n", rate);
    }

    // Close and delete everything

    // File permission stuff
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    fclose(infile);
    fclose(outfile);

    bm_delete(&H);
    return 0;
}
