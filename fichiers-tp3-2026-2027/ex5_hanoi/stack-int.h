#ifndef _STACK_H
#define _STACK_H

typedef struct Stack_t Stack;

Stack *stackCreate(void);
void   stackFree(Stack *);
void   stackPush(Stack *, int);
int    stackPop(Stack *);
int    stackTop(Stack *);
int    stackSize(Stack *);
int    stackIsEmpty(Stack *);
void   stackPrint(Stack *);

#endif
