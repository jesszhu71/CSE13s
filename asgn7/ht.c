// Hash Table ADT
#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// Constructs the ht
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

// Deletes the ht in memory
void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->lists) {
        for (uint32_t i = 0; i < (*ht)->size; i = i + 1) {
            if ((*ht)->lists[i]) {
                ll_delete(&(*ht)->lists[i]);
            }
        }
        free((*ht)->lists);
        (*ht)->lists = NULL;
        free(*ht);
        *ht = NULL;
    }
    return;
}

// Returns the size of ht
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Looks up a word in the ht, returns the node if found
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // Check if the list is initialized, then lookup in ll
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (!ht->lists[index]) {
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak);
}

// Inserts a word and its newspeak into ht
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Check if linked list is initialized, then insert in ll
    uint32_t ht_index = hash(ht->salt, oldspeak) % ht->size;
    if (!ht->lists[ht_index]) {
        ht->lists[ht_index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[ht_index], oldspeak, newspeak);
}

// Counts the number of linked lists in ht
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i = i + 1) {
        if (ht->lists[i] != NULL) {
            count = count + 1;
        }
    }
    return count;
}

// Prints the ht
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i = i + 1) {
        if (ht->lists[i] != NULL) {
            ll_print(ht->lists[i]);
        }
    }
}
