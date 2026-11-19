#ifndef _LIST_H
#define _LIST_H

typedef struct Node_t {
    int data;
    struct Node_t *next;
} Node;

Node *createList(int data);
Node *addList(Node *first, int data);
void freeList(Node *first);

#endif
