#ifndef _BTREE_H
#define _BTREE_H

typedef struct BTNode_t BTNode;
typedef struct BTree_t BTree;

BTree  *btCreate(void);
void    btFree(BTree *tree);
BTNode *btCreateRoot(BTree *tree, int data);
BTNode *btInsertLeft(BTree *tree, BTNode *n1, int data);
BTNode *btInsertRight(BTree *tree, BTNode *n2, int data);

BTNode *btRoot(BTree *tree);
BTNode *btLeft(BTree *tree, BTNode *n);
BTNode *btRight(BTree *tree, BTNode *n);
BTNode *btParent(BTree *tree, BTNode *n);
int     btGetData(BTree *tree, BTNode *n);
int     btSize(BTree *tree);

int     btIsRoot(BTree *tree, BTNode *n);
int     btIsInternal(BTree *tree, BTNode *n);
int     btIsExternal(BTree *tree, BTNode *n);
int     btHasLeft(BTree *tree, BTNode *n);
int     btHasRight(BTree *tree, BTNode *n);

int     btEqual(BTree *tree1, BTree *tree2);
int     btIsAncestor(BTree *tree, BTNode *n1, BTNode *n2);
void    btSwap(BTree *tree, BTNode *n1, BTNode *n2);
int     btIsUniform(BTree *tree);
#endif
