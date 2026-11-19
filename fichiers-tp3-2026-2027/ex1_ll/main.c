#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static Node *removeList(Node *first, int key) {

  // A completer

  // ...
  
  return NULL;
}


static Node *inverseList(Node *first) {

  // A completer
  
  // ...
    
  return NULL;
}

static void printList(Node *first) {
    Node *cur = first;
    while (cur) {
        Node *next = cur->next;
        printf("%d->", cur->data);
        cur = next;
    }
    printf("\n");
    return;
}

int main(void) {
    Node *l = createList(5);
    int tmp;
    Node *head = l;
    for (int i = 0; i < 20; i++) {
        head = addList(head, rand()%100);
        if (i == 10)
            tmp = head->data;
    }
    printList(head);
    head = removeList(head, tmp);
    printList(head);
    head = inverseList(head);
    printList(head);
    freeList(head);
    return 0;
}
