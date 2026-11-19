#ifndef BTTRAVERSALS_H
#define BTTRAVERSALS_H

#include "BTree.h"
#include "List.h"

/* Returns a new list containing the data stored at the nodes of tree, in the
 * order of a preorder traversal (root, left subtree, right subtree). The
 * data are not copied. Returns an empty list if tree is empty. */
List *btGetPreOrderData(BTree *tree);

/* Returns a new list containing the data stored at the nodes of tree, in the
 * order of an inorder traversal (left subtree, root, right subtree). The
 * data are not copied. Returns an empty list if tree is empty. */
List *btGetInOrderData(BTree *tree);

/* Returns a new list containing the data stored at the nodes of tree, in the
 * order of a postorder traversal (left subtree, right subtree, root). The
 * data are not copied. Returns an empty list if tree is empty. */
List *btGetPostOrderData(BTree *tree);

/* Returns a new tree whose preorder and inorder traversals are given by the
 * lists of strings pre and in respectively. Both lists are assumed to contain
 * the same strings, all distinct, and to be the two traversals of the same
 * tree. The data stored at each node is a pointer to the corresponding string
 * of one of the two lists (strings are not copied). pre and in are not
 * modified. Returns an empty tree if the lists are empty. */
BTree *btFromTraversals(List *pre, List *in);

#endif
