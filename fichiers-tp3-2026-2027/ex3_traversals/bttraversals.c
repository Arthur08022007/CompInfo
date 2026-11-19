#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"
#include "List.h"
#include "Dict.h"
#include "bttraversals.h"


static void btInOrderTreeWalk(BTree *tree, BTNode *n, List *l) {
    
    if (btHasLeft(tree, n))
        btInOrderTreeWalk(tree, btLeft(tree, n), l);
    listInsertLast(l,(void *)btGetData(tree, n));
    if (btHasRight(tree, n))
        btInOrderTreeWalk(tree, btRight(tree, n), l);
}

static void btPreOrderTreeWalk(BTree *tree, BTNode *n, List *l) {
    listInsertLast(l,(void *)btGetData(tree, n));
    if (btHasLeft(tree, n))
        btPreOrderTreeWalk(tree, btLeft(tree, n), l);
    if (btHasRight(tree, n))
        btPreOrderTreeWalk(tree, btRight(tree, n), l);
}

static void btPostOrderTreeWalk(BTree *tree, BTNode *n, List *l) {
    if (btHasLeft(tree, n))
        btPostOrderTreeWalk(tree, btLeft(tree, n), l);
    if (btHasRight(tree, n))
        btPostOrderTreeWalk(tree, btRight(tree, n), l);
    listInsertLast(l,(void *)btGetData(tree, n));
}

List *btGetPreOrderData(BTree *tree)
{
    
    List *t=listCreate();
    BTNode *n=btRoot(tree);
    btPreOrderTreeWalk(tree, n, t);
    return t;
}

List *btGetInOrderData(BTree *tree)
{
    List *t=listCreate();
    BTNode *n=btRoot(tree);
    btInOrderTreeWalk(tree, n, t);
    return t;
}

List *btGetPostOrderData(BTree *tree)
{
    List *t=listCreate();
    BTNode *n=btRoot(tree);
    btPostOrderTreeWalk(tree, n, t);
    return t;
}

// Complexité de btFromTraversals: O(...)

// Remplacez les "..." par la complexité de btFromTraversals en fonction de n,
// le nombre de noeuds dans l'arbre. Ne modifiez rien d'autre sur la ligne 
// que les "...".


BTree *btFromTraversals(List *pre, List *in)
{
    (void)pre;
    (void)in;
    
    return btCreate();
}
