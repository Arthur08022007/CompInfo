#ifndef _BTREE_H
#define _BTREE_H

/* Binary tree whose nodes store data of type void *. The data are never
 * copied nor freed by the functions below. */

typedef struct BTNode_t BTNode;
typedef struct BTree_t BTree;

/* Creates an empty tree. */
BTree *btCreate(void);

/* Frees the tree and all its nodes (but not their data). */
void btFree(BTree *tree);

/* Frees the left and right subtrees of node n (but not their data). n
 * becomes a leaf. */
void btFreeChildrenSubtrees(BTree *tree, BTNode *n);

/* Creates the root of an empty tree, with the given data, and returns it. */
BTNode *btCreateRoot(BTree *tree, void *data);

/* Creates a left child of node n1 (which must not have one), with the given
 * data, and returns it. */
BTNode *btInsertLeft(BTree *tree, BTNode *n1, void *data);

/* Creates a right child of node n2 (which must not have one), with the given
 * data, and returns it. */
BTNode *btInsertRight(BTree *tree, BTNode *n2, void *data);

/* Returns the root of the tree (NULL if the tree is empty). */
BTNode *btRoot(BTree *tree);

/* Returns the left child of n (NULL if n has no left child). */
BTNode *btLeft(BTree *tree, BTNode *n);

/* Returns the right child of n (NULL if n has no right child). */
BTNode *btRight(BTree *tree, BTNode *n);

/* Returns the parent of n (NULL if n is the root). */
BTNode *btParent(BTree *tree, BTNode *n);

/* Returns the data stored at node n. */
void *btGetData(BTree *tree, BTNode *n);

/* Replaces the data stored at node n by data. */
void btSetData(BTree *tree, BTNode *n, void *data);

/* Returns 1 if n is the root of the tree, 0 otherwise. */
int btIsRoot(BTree *tree, BTNode *n);

/* Returns 1 if n is an internal node (it has at least one child), 0
 * otherwise. */
int btIsInternal(BTree *tree, BTNode *n);

/* Returns 1 if n is an external node, i.e. a leaf (it has no child), 0
 * otherwise. */
int btIsExternal(BTree *tree, BTNode *n);

/* Returns 1 if n has a left child, 0 otherwise. */
int btHasLeft(BTree *tree, BTNode *n);

/* Returns 1 if n has a right child, 0 otherwise. */
int btHasRight(BTree *tree, BTNode *n);

/* Returns 1 if the two trees have the same structure and the same data
 * pointers at corresponding nodes (the pointers are compared, not the
 * pointed values), 0 otherwise. */
int btEqual(BTree *tree1, BTree *tree2);

#endif
