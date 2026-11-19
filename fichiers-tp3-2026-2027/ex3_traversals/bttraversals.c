#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"
#include "List.h"
#include "Dict.h"
#include "bttraversals.h"


static void btInOrderTreeWalk(BTree *tree, BTNode *n, List *l) {
    listInsertLast(l,(void *)btGetData(tree, n));
    if (btHasLeft(tree, n))
        btInOrderTreeWalk(tree, btLeft(tree, n), l);
    
    if (btHasRight(tree, n))
        btInOrderTreeWalk(tree, btRight(tree, n), l);
}

List *btGetPreOrderData(BTree *tree)
{
    
    List *t=listCreate();
    BTNode *n=btRoot(tree);
    btInOrderTreeWalk(tree, n, t);
    return t;
}

List *btGetInOrderData(BTree *tree)
{
    /* A compléter */
    (void)tree;
    return listCreate();
}

List *btGetPostOrderData(BTree *tree)
{
    /* A compléter */
    (void)tree;
    return listCreate();
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
