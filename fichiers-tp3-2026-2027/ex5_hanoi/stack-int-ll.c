#include <stdlib.h>
#include <stdio.h>
#include "stack-int.h"

typedef struct Node_t {
  int         data;
  struct Node_t *next;
} Node;

struct Stack_t {
  Node *top;
  int   size;
};

static void terminate(const char *message);
static void stackPrintRec(Node *s);

static void terminate(const char *message) {
  printf("%s\n",message);
  exit(EXIT_FAILURE);
}

Stack *stackCreate() {
  Stack *s = malloc(sizeof(Stack));
  if (!s)
    terminate("Stack can not be created");
  s -> top = NULL;
  s -> size = 0;
  return s;
}

void stackFree(Stack *s) {
  Node *n = s -> top;
  while (n) {
    Node *nNext = n -> next;
    free(n);
    n = nNext;
  }
  free(s);
}

void stackPush(Stack *s, int data) {
  Node *n = malloc(sizeof(Node));
  
  if (!n)
    terminate("Stack node can not be created");

  n -> data = data;
  n -> next = s -> top;
  s -> top = n;
  s -> size++;
}

int stackPop(Stack *s) {
  if (!(s -> top))
    terminate("Stack is empty");

  Node *n = s -> top;
  int data = n -> data;

  s -> top = n -> next;
  s -> size--;

  free(n);

  return data;
}

int stackTop(Stack *s) {
  if (!(s -> top))
    terminate("Stack is empty");

  return s -> top -> data;
}

int stackSize(Stack *s) {
  return s -> size;
}

int stackIsEmpty(Stack *s) {
  return (s -> size) == 0;
}

static void stackPrintRec(Node *n) {
  if (n == NULL)
    return;
  stackPrintRec(n->next);
  printf(" %d", n->data);
}
      
void stackPrint(Stack *s) {
  stackPrintRec(s->top);
}
