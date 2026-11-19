#ifndef LIST_H
#define LIST_H

typedef struct ListNode_t ListNode;
typedef struct List_t List;

/* Creates an empty list. */
List *listCreate(void);

/* Frees the list (but not the data of its elements). */
void listFree(List *l);

/* Returns the number of elements of the list. */
int listSize(List *l);

/* Inserts data at the beginning of the list. */
void listInsertFirst(List *l, void *data);

/* Inserts data at the end of the list (in O(1)). */
void listInsertLast(List *l, void *data);

/* Returns the first element of the list (NULL if the list is empty). */
ListNode *listHead(List *l);

/* Returns the element following n (NULL if n is the last element). */
ListNode *listNext(ListNode *n);

/* Returns the data of element n. */
void *listGetData(ListNode *n);

#endif
