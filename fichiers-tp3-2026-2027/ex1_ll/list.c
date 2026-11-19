#include <stdlib.h>
#include "list.h"

Node *createList(int data) {
    Node *toReturn = (Node *) malloc(sizeof(Node));
    toReturn->data = data;
    toReturn->next = NULL;
    return toReturn;
}

Node *addList(Node *first, int data) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->data = data;
    new->next = first;
    return new;
}

void freeList(Node *first) {
    Node *cur = first;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    return;
}
