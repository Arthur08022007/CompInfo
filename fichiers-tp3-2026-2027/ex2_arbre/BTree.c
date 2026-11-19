#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

struct BTNode_t {
  BTNode *parent;
  BTNode *left;
  BTNode *right;
  int data;
};
  
struct BTree_t {
  BTNode *root;
  int size;
};

static void terminate(char *m);
static void FreeNodesRec(BTNode *n);
static BTNode *createNode(int data);

static void terminate(char *m) {
  printf("%s\n",m);
  exit(EXIT_FAILURE);
}
    
BTree  *btCreate(void) {
  BTree *tree = malloc(sizeof(BTree));
  if (!tree)
    terminate("Tree can not be created");
  tree->root = NULL;
  tree->size = 0;
  return tree;
}

static void FreeNodesRec(BTNode *n) {
  if (!n)
    return;
  FreeNodesRec(n->left);
  FreeNodesRec(n->right);
  free(n);
}

void btFree(BTree *tree) {
  FreeNodesRec(tree->root);
  free(tree);    
}

static BTNode *createNode(int data) {
  BTNode *n = malloc(sizeof(BTNode));
  if (!n)
    terminate("Node can not be created");
  n->data   = data;
  n->left   = NULL;
  n->right  = NULL;
  n->parent = NULL;
  return n;
}

BTNode *btCreateRoot(BTree *tree, int data) {
  BTNode *root = createNode(data);
  tree->root = root;
  tree->size = 1;
  return root;
}

BTNode *btInsertLeft(BTree *tree, BTNode *n, int data) {
  BTNode *nleft = createNode(data);
  n->left = nleft;
  nleft->parent = n;
  tree->size++;
  return nleft;
}

BTNode *btInsertRight(BTree *tree, BTNode *n, int data) {
  BTNode *nright = createNode(data);
  n->right = nright;
  nright->parent = n;
  tree->size++;
  return nright;
}

BTNode *btRoot(BTree *tree) {
  return tree->root;
}

BTNode *btLeft(BTree *tree, BTNode *n) {
  (void)(tree);
  return n->left;
}

BTNode *btRight(BTree *tree, BTNode *n) {
  (void)(tree);
  return n->right;
}

BTNode *btParent(BTree *tree, BTNode *n) {
  (void)(tree);
  return n->parent;
}

int btGetData(BTree *tree, BTNode *n) {
  (void)(tree);
  return n->data;
}

int btSize(BTree *tree) {
  return tree->size;
}

int btIsRoot(BTree *tree, BTNode *n) {
  (void)(tree);
  return (n->parent==NULL);
}

int btIsInternal(BTree *tree, BTNode *n) {
  (void)(tree);
  return (n->left!=NULL || n->right!=NULL);
}

int btIsExternal(BTree *tree, BTNode *n) {
  (void)(tree);
  return (n->left==NULL && n->right==NULL);
}

int btHasLeft(BTree *tree, BTNode *n) {
  (void)(tree);
  return (n->left!=NULL);
}

int btHasRight(BTree *tree, BTNode *n) {
  (void)(tree);
  return (n->right!=NULL);
}

static int btEqual_rec(BTNode *n1, BTNode *n2);

static int btEqual_rec(BTNode *n1, BTNode *n2) {
  if (n1 == NULL && n2 == NULL)
    return 1;
  else if (n1 != NULL && n2 != NULL) {
    if (n1->data != n2->data)
      return 0;
    if (!btEqual_rec(n1->left, n2->left))
      return 0;
    if (!btEqual_rec(n1->right, n2->right))
      return 0;
    return 1;
  } else
    return 0;  
}

int btEqual(BTree *tree1, BTree *tree2) {
  return btEqual_rec(tree1->root, tree2->root);
}

// Les fonctions ci-dessous sont a completer

int btIsAncestor(BTree *tree, BTNode *n1, BTNode *n2) {
  // A completer

  // ...
  
  return 0;
}

void btSwap(BTree *tree, BTNode *n1, BTNode *n2) {
  // A completer

  // ...
}

int btIsUniform(BTree *tree) {
  // A completer

  // ...
  return 0;
}

