#include <stdio.h>
#include <stdlib.h>

#include "List.h"

struct ListNode_t
{
    void *data;
    ListNode *next;
};

struct List_t
{
    ListNode *head;
    ListNode *last;
    int size;
};

static void terminate(char *m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

List *listCreate(void)
{
    List *l = malloc(sizeof(List));
    if (!l)
        terminate("List can not be created");
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

void listFree(List *l)
{
    ListNode *n = l->head;
    while (n)
    {
        ListNode *next = n->next;
        free(n);
        n = next;
    }
    free(l);
}

int listSize(List *l)
{
    return l->size;
}

static ListNode *createNode(void *data, ListNode *next)
{
    ListNode *n = malloc(sizeof(ListNode));
    if (!n)
        terminate("List node can not be created");
    n->data = data;
    n->next = next;
    return n;
}

void listInsertFirst(List *l, void *data)
{
    l->head = createNode(data, l->head);
    if (!l->last)
        l->last = l->head;
    l->size++;
}

void listInsertLast(List *l, void *data)
{
    ListNode *n = createNode(data, NULL);
    if (l->last)
        l->last->next = n;
    else
        l->head = n;
    l->last = n;
    l->size++;
}

ListNode *listHead(List *l)
{
    return l->head;
}

ListNode *listNext(ListNode *n)
{
    return n->next;
}

void *listGetData(ListNode *n)
{
    return n->data;
}
