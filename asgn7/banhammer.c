// Main, banhammer

#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "ht:f:ms"
#define WORD    "([a-zA-Z0-9_]+(-|'))+[a-zA-Z0-9_]+|[a-zA-Z0-9_]+"

// Extern vars
uint64_t seeks;
uint64_t links;

int main(int argc, char **argv) {
    seeks = 0;
    links = 0;

    int opt = 0;
    bool h = false;
    uint32_t t_size = 10000;
    uint32_t f_size = 1024 * 1024; // 2^20 = 2^10 * 2^10 neg numbers?
    bool mtf = false;
    bool s = false;
    char *string_pointer;
    bool not_option = false;
    int64_t num = 0; // used for making sure input is not negative
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            // h is selected
            h = true;
            break;
        case 't':
            // t is selected
            num = strtoul(optarg, &string_pointer, 10);
            if (num < 0) {
                printf("Failed to create hash table.\n");
                return 1;
            }
            t_size = (uint32_t) num;
            break;
        case 'f':
            // f is selected
            num = strtoul(optarg, &string_pointer, 10);
            if (num < 0) {
                printf("Failed to create Bloom filter.\n");
                return 1;
            }
            f_size = (uint32_t) num;
            break;
        case 'm':
            // m is selected
            mtf = true;
            break;
        case 's':
            // s is selected
            s = true;
            break;
        default:
            // something other than valid options selected
            not_option = true;
            break;
        }
    }

    // Synopsis, for help or bad option selected
    if (not_option || h) {
        printf("SYNOPSIS\n");
        printf("  A word filtering program for the GPRSC.\n");
        printf("  Filters out and reports bad words parsed from stdin.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -s             Pint program statistics.\n");
        printf("  -t size        Specify hash table size (default: 10000).\n");
        printf("  -f size        Specify Bloom filter size (default: 2^20).\n");
        if (not_option) {
            return 1;
        }
        return 0;
    }

    // Initialize bloom filter and hash table
    BloomFilter *bloom = bf_create(f_size);
    HashTable *hash = ht_create(t_size, mtf);

    // Read in backspeak and add to filter and hashtable
    FILE *bad = fopen("badspeak.txt", "r");
    char old[4096];
    while (fscanf(bad, "%s\n", old) != EOF) {
        //  add badpeak to filter and hash table
        bf_insert(bloom, old);
        ht_insert(hash, old, NULL);
    }
    fclose(bad);

    // Read in oldspeak and new speak pairs, add to bloom filter and hashtable
    FILE *new_old = fopen("newspeak.txt", "r");
    char new[4096]; // reading buffer
    while (fscanf(new_old, "%s %s\n", old, new) != EOF) {
        // add oldspeak to filter
        bf_insert(bloom, old);
        // add old/newspeak to table
        ht_insert(hash, old, new);
    }
    fclose(new_old);

    // Regex parsing!
    regex_t pattern;
    if (regcomp(&pattern, WORD, REG_EXTENDED)) { // compile the regex pattern
        fprintf(stderr, "Failed to compile regex.\n");
        // delete bf and ht here too!
        return 1;
    }

    char *match = NULL;
    bool tc = false;
    bool rs = false;
    LinkedList *badspeak = ll_create(mtf); // holds list of badspeak words
    LinkedList *oldspeak = ll_create(mtf); // holds list of oldspeak words

    // Let the parsing begin!
    while ((match = next_word(stdin, &pattern)) != NULL) {
        // make lower case
        for (uint32_t i = 0; i < strlen(match); i = i + 1) {
            match[i] = tolower(match[i]);
        }
        // check if hit
        if (bf_probe(bloom, match)) {
            Node *looked_up = ht_lookup(hash, match);
            if (looked_up != NULL && looked_up->oldspeak != NULL && looked_up->newspeak == NULL) {
                // thoughtcrime
                tc = true;
                ll_insert(badspeak, looked_up->oldspeak, NULL);
            } else if (looked_up != NULL && looked_up->oldspeak != NULL
                       && looked_up->newspeak != NULL) {
                // Rightspeak
                rs = true;
                ll_insert(oldspeak, looked_up->oldspeak, looked_up->newspeak);

            } // otherwise false positive;
        }
    }

    // End message stuff, either message or stats
    if (!s) {
        if (tc && rs) {
            // mixspeak, both thoughtcrime and rightspeak
            printf("%s", mixspeak_message);
            ll_print(badspeak);
            ll_print(oldspeak);
        } else if (tc && !rs) {
            // badspeak, only thoughtcrime
            printf("%s", badspeak_message);
            ll_print(badspeak);
        } else if (!tc && rs) {
            printf("%s", goodspeak_message);
            ll_print(oldspeak);
        } // otherwise no crime commited

    } else {
        // print stats message
        double average_seek = (double) links / (double) seeks;
        double hash_load = 100 * (double) ht_count(hash) / (double) ht_size(hash);
        double bloom_load = 100 * (double) bf_count(bloom) / (double) bf_size(bloom);
        fprintf(stdout, "Seeks: %lu\n", seeks);
        fprintf(stdout, "Average seek length: %.6f\n", average_seek);
        fprintf(stdout, "Hash table load: %.6f%%\n", hash_load);
        fprintf(stdout, "Bloom filter load: %.6f%%\n", bloom_load);
    }

    // delete/free/clear everything
    clear_words();
    regfree(&pattern);

    ll_delete(&badspeak);
    ll_delete(&oldspeak);

    ht_delete(&hash);
    bf_delete(&bloom);

    return 0;
}
