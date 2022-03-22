// Node ADT

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Strdup alternative
char *copy(char *str) {
    return strcpy((char *) malloc(strlen(str) + 1), str);
}

// Constructs a node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n && oldspeak != NULL) {
        // node exists, oldspeak exists
        n->oldspeak = copy(oldspeak);
        n->newspeak = NULL;
        // if newspeak exists too
        if (newspeak != NULL) {
            n->newspeak = copy(newspeak);
        }
        n->next = NULL;
        n->prev = NULL;
    } else if (n && oldspeak == NULL) {
        // (sentinel node) node exists, oldspeak doesn't exists
        n->oldspeak = NULL;
        n->newspeak = NULL;
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

// Deletes the node in memory
void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
        free(*n);
        *n = NULL;
    }
    return;
}

// Prints the node
void node_print(Node *n) {
    // if node n contains oldspeak and newspeak
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else {
        // node only contains oldspeak
        printf("%s\n", n->oldspeak);
    }
}
