#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BTree.h"
#include "List.h"
#include "bttraversals.h"

/* Writes the subtree rooted at node as value(left,right). A leaf is written
 * as its value only and an empty subtree as nothing. */
static void printNode(FILE *fp, BTree *tree, BTNode *node)
{
    if (!node)
        return;
    fprintf(fp, "%s", (char *)btGetData(tree, node));
    if (btIsInternal(tree, node))
    {
        fprintf(fp, "(");
        printNode(fp, tree, btLeft(tree, node));
        fprintf(fp, ",");
        printNode(fp, tree, btRight(tree, node));
        fprintf(fp, ")");
    }
}

/* Writes tree to fp, followed by an end of line. */
static void btPrintTree(FILE *fp, BTree *tree)
{
    printNode(fp, tree, btRoot(tree));
    fprintf(fp, "\n");
}

/* Writes a list of strings to fp, separated by commas, followed by an end
 * of line. */
static void listPrint(FILE *fp, List *l)
{
    fprintf(fp,"{");
    for (ListNode *n = listHead(l); n; n = listNext(n))
        fprintf(fp, n == listHead(l) ? "%s" : ",%s", (char *)listGetData(n));
    fprintf(fp, "}\n");
}

/* Writes the n strings of array a to fp, separated by commas, followed by an
 * end of line. */
static void arrayPrint(FILE *fp, char **a, int n)
{

    fprintf(fp,"{");
    for (int i = 0; i < n; i++)
        fprintf(fp, i == 0 ? "%s" : ",%s", a[i]);
    fprintf(fp, "}\n");
}

int main(void)
{
    char *a = "a", *b = "b", *d = "d", *e = "e", *f = "f", *g = "g", *h = "h";

    /* Example of the statement: d(g(a,e),b(,h(f,))) */

    BTree *tree = btCreate();
    BTNode *nd = btCreateRoot(tree, d);
    BTNode *ng = btInsertLeft(tree, nd, g);
    btInsertLeft(tree, ng, a);
    btInsertRight(tree, ng, e);
    BTNode *nb = btInsertRight(tree, nd, b);
    BTNode *nh = btInsertRight(tree, nb, h);
    btInsertLeft(tree, nh, f);

    int nbnodes = 7;
    char *true_pre[] = {d, g, a, e, b, h, f};
    char *true_in[] = {a, g, e, d, b, f, h};
    char *true_post[] = {a, e, g, f, h, b, d};


    printf("Tree for the test:\n");
    btPrintTree(stdout, tree);

    List *pre = btGetPreOrderData(tree);
    printf("\nOutput of btGetPreOrderData(tree):\n");
    listPrint(stdout, pre);
    printf("expected:\n");
    arrayPrint(stdout, true_pre, nbnodes);

    List *in = btGetInOrderData(tree);
    printf("\nOutput of btGetInOrderData(tree):\n");
    listPrint(stdout, in);
    printf("expected:\n");
    arrayPrint(stdout, true_in, nbnodes);

    List *post = btGetPostOrderData(tree);
    printf("\nOutput of btGetPostOrderData(tree):\n");
    listPrint(stdout, post);
    printf("expected:\n");
    arrayPrint(stdout, true_post, nbnodes);
    listFree(post);

    BTree *newtree = btFromTraversals(pre, in);
    printf("\nOutput of btFromTraversals(pre, in):\n");
    btPrintTree(stdout, tree);
    printf("expected:\n");
    btPrintTree(stdout, newtree);
    btFree(newtree);
    listFree(in);
    listFree(pre);

    btFree(tree);

    return EXIT_SUCCESS;
}
