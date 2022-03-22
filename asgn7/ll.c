// Linked List

#include "ll.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks; // Number of seeks performed.
uint64_t links; // Number of links traversed.

struct LinkedList {
    uint32_t length;
    Node *head; // head sentinel node
    Node *tail; // tail sentinel node
    bool mtf;
};

// Constructs the ll
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->mtf = mtf;
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
    }
    return ll;
}

// Deletes the ll in memory
void ll_delete(LinkedList **ll) {
    Node *temp = (*ll)->head->next;
    while (temp != NULL) {
        temp = (*ll)->head->next;
        node_delete(&(*ll)->head);
        (*ll)->head = temp;
    }
    free(*ll);
    *ll = NULL;
}

// Returns length of ll
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// Finds the node corresponding to oldspeak if it exists
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks = seeks + 1;
    Node *curr;
    curr = ll->head->next;
    for (uint32_t i = 0; i < ll->length; i = i + 1) {
        // Does word exist?
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            // Move to front?
            if (ll->mtf) {
                // Remove found node from curr position
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;

                // Move node to front
                curr->next = ll->head->next;
                curr->prev = ll->head;
                ll->head->next->prev = curr;
                ll->head->next = curr;
            }
            return curr;
        } else {
            // Word not found yet, move to next node
            curr = curr->next;
            links = links + 1;
        }
    }
    return NULL;
}

// Insert word and newspeak into the ll
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // Check if word already in the ll
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *new = node_create(oldspeak, newspeak);
        new->next = ll->head->next;
        new->prev = ll->head;
        ll->head->next->prev = new;
        ll->head->next = new;
        ll->length = ll->length + 1;
    }
}

// Prints the ll
void ll_print(LinkedList *ll) {
    Node *curr = ll->head->next;
    for (uint32_t i = 0; i < ll->length; i = i + 1) {
        node_print(curr);
        curr = curr->next;
    }
}
