#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

struct BTNode_t
{
    BTNode *parent;
    BTNode *left;
    BTNode *right;
    void *data;
};

struct BTree_t
{
    BTNode *root;
};

static void terminate(char *m);
static void FreeNodesRec(BTNode *n);
static BTNode *createNode(void *data);

static void terminate(char *m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

BTree *btCreate(void)
{
    BTree *tree = malloc(sizeof(BTree));
    if (!tree)
        terminate("Tree can not be created");
    tree->root = NULL;
    return tree;
}

static void FreeNodesRec(BTNode *n)
{
    if (!n)
        return;
    FreeNodesRec(n->left);
    FreeNodesRec(n->right);
    free(n);
}

void btFree(BTree *tree)
{
    FreeNodesRec(tree->root);
    free(tree);
}

void btFreeChildrenSubtrees(BTree *tree, BTNode *n)
{
    (void)(tree);
    if (!n)
        return;
    FreeNodesRec(n->left);
    FreeNodesRec(n->right);
    n->left = NULL;
    n->right = NULL;
}

static BTNode *createNode(void *data)
{
    BTNode *n = malloc(sizeof(BTNode));
    if (!n)
        terminate("Node can not be created");
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

BTNode *btCreateRoot(BTree *tree, void *data)
{
    BTNode *root = createNode(data);
    tree->root = root;
    return root;
}

BTNode *btInsertLeft(BTree *tree, BTNode *n, void *data)
{
    (void)(tree);
    BTNode *nleft = createNode(data);
    n->left = nleft;
    nleft->parent = n;
    return nleft;
}

BTNode *btInsertRight(BTree *tree, BTNode *n, void *data)
{
    (void)(tree);
    BTNode *nright = createNode(data);
    n->right = nright;
    nright->parent = n;
    return nright;
}

BTNode *btRoot(BTree *tree)
{
    return tree->root;
}

BTNode *btLeft(BTree *tree, BTNode *n)
{
    (void)(tree);
    return n->left;
}

BTNode *btRight(BTree *tree, BTNode *n)
{
    (void)(tree);
    return n->right;
}

BTNode *btParent(BTree *tree, BTNode *n)
{
    (void)(tree);
    return n->parent;
}

void *btGetData(BTree *tree, BTNode *n)
{
    (void)(tree);
    return n->data;
}

void btSetData(BTree *tree, BTNode *n, void *data)
{
    (void)(tree);
    n->data = data;
}

int btIsRoot(BTree *tree, BTNode *n)
{
    (void)(tree);
    return (n->parent == NULL);
}

int btIsInternal(BTree *tree, BTNode *n)
{
    (void)(tree);
    return (n->left != NULL || n->right != NULL);
}

int btIsExternal(BTree *tree, BTNode *n)
{
    (void)(tree);
    return (n->left == NULL && n->right == NULL);
}

int btHasLeft(BTree *tree, BTNode *n)
{
    (void)(tree);
    return (n->left != NULL);
}

int btHasRight(BTree *tree, BTNode *n)
{
    (void)(tree);
    return (n->right != NULL);
}

static int btEqual_rec(BTNode *n1, BTNode *n2);

static int btEqual_rec(BTNode *n1, BTNode *n2)
{
    if (n1 == NULL && n2 == NULL)
        return 1;
    else if (n1 != NULL && n2 != NULL)
    {
        if (n1->data != n2->data)
            return 0;
        if (!btEqual_rec(n1->left, n2->left))
            return 0;
        if (!btEqual_rec(n1->right, n2->right))
            return 0;
        return 1;
    }
    else
        return 0;
}

int btEqual(BTree *tree1, BTree *tree2)
{
    return btEqual_rec(tree1->root, tree2->root);
}
