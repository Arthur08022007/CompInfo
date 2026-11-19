
#include <stdio.h>
#include "BTree.h"

static int btCountLeaves(BTree *tree);
static int btHeight(BTree *tree);
static int btHeight_rec(BTree *tree, BTNode *n);

static int btCountLeaves(BTree *tree) {
  // A completer

  // ...
  
  return 0;
  
}

static int btHeight(BTree *tree) {
   return btHeight_rec(tree, btRoot(tree));
}

static int btHeight_rec(BTree *tree, BTNode *n) {
  if (btIsExternal(tree, n))
     return 0;
  else {
    int hl = 0;
    int hr = 0;
    if (btHasLeft(tree, n))
      hl = btHeight_rec(tree, btLeft(tree, n));
    if (btHasRight(tree, n))
      hr = btHeight_rec(tree, btRight(tree, n));
    return 1 + (hl>hr? hl: hr);
  }
}

int main(void) {

  /* tree 1

    n1:6
     / \
  n2:2  n5:8
   / \     \
n3:1 n4:4   n6:11 
  
  */
  
  BTree *tree1 = btCreate();
  BTNode *t1n1 = btCreateRoot(tree1, 6);
  BTNode *t1n2 = btInsertLeft(tree1, t1n1, 2);
  BTNode *t1n3 = btInsertLeft(tree1, t1n2, 1);
  btInsertRight(tree1, t1n2, 4);
  BTNode *t1n5 = btInsertRight(tree1, t1n1, 8);
  btInsertRight(tree1, t1n5, 11);

  /*  tree 2

    n1:1
     / \
  n2:4  n4:9
   /      \
n3:2      n5:-4

  */

  BTree *tree2 = btCreate();
  BTNode *t2n1 = btCreateRoot(tree2, 1);
  BTNode *t2n2 = btInsertLeft(tree2, t2n1, 4);
  BTNode *t2n3 = btInsertLeft(tree2, t2n2, 2);
  BTNode *t2n4 = btInsertRight(tree2, t2n1, 9);
  BTNode *t2n5 = btInsertRight(tree2, t2n4, -4);
  
  /* tree 3: a copy of tree 1 */
  
  BTree *tree3 = btCreate();
  BTNode *t3n1 = btCreateRoot(tree3, 6);
  BTNode *t3n2 = btInsertLeft(tree3, t3n1, 2);
  BTNode *t3n3 = btInsertLeft(tree3, t3n2, 1);
  btInsertRight(tree3, t3n2, 4);
  BTNode *t3n5 = btInsertRight(tree3, t3n1, 8);
  BTNode *t3n6 = btInsertRight(tree3, t3n5, 11);

    /*  tree 4

    n1:1
     / \
  n2:4  n4:7
   /     
n3:2     

  */

  BTree *tree4 = btCreate();
  BTNode *t4n1 = btCreateRoot(tree4, 1);
  BTNode *t4n2 = btInsertLeft(tree4, t4n1, 4);
  btInsertLeft(tree4, t4n2, 2);
  btInsertRight(tree4, t4n1, 7);
  
  printf("Number of leaves in tree1: %d (over %d nodes) (expected: 3)\n", btCountLeaves(tree1), btSize(tree1));
  printf("Number of leaves in tree2: %d (over %d nodes) (expected: 2)\n", btCountLeaves(tree2), btSize(tree2));
  printf("Number of leaves in tree3: %d (over %d nodes) (expected: 3)\n", btCountLeaves(tree3), btSize(tree3));

  printf("btEqual(tree1,tree1) = %d\n", btEqual(tree1,tree1));
  printf("btEqual(tree1,tree3) = %d\n", btEqual(tree1,tree3));
  printf("btEqual(tree1,tree2) = %d\n", btEqual(tree1,tree2));

  printf("btIsAncestor(tree1,t1n1,t1n2) = %d (expected: 1)\n", btIsAncestor(tree1, t1n1, t1n3));
  printf("btIsAncestor(tree2,t2n4,t2n5) = %d (expected: 1)\n", btIsAncestor(tree2, t2n4, t2n5));
  printf("btIsAncestor(tree2,t2n4,t2n4) = %d (expected: 0)\n", btIsAncestor(tree2, t2n4, t2n4));
  printf("btIsAncestor(tree2,t2n4,t2n3) = %d (expected: 0)\n", btIsAncestor(tree2, t2n4, t2n3));
  printf("btIsAncestor(tree3,t3n5,t3n3) = %d (expected: 0)\n", btIsAncestor(tree3, t3n5, t3n3));  

  printf("Height of tree3: %d\n", btHeight(tree3));
  printf("Swapping n2 and n1 in tree3 (nothing should change)\n");
  btSwap(tree3, t3n2, t3n1);
  btSwap(tree3, t3n1, t3n2);
  printf("btEqual(tree1,tree3) = %d (expected 1)\n", btEqual(tree1,tree3));
  printf("Swapping n2 and n6 in tree3\n");
  fflush(stdout);
  btSwap(tree3, t3n2, t3n6);
  printf("btEqual(tree1,tree3) = %d (expected 0)\n", btEqual(tree1,tree3));
  printf("Height of tree3: %d (expected 3)\n", btHeight(tree3));
  printf("btIsAncestor(tree3, t3n5, t3n3) = %d (expected 1)\n", btIsAncestor(tree3, t3n5, t3n3));
  printf("Swapping n2 and n6 in tree3 again\n");
  btSwap(tree3, t3n2, t3n6);
  printf("btEqual(tree1,tree3) = %d (expected 1)\n", btEqual(tree1,tree3));
  printf("btIsUniform(tree1) = %d (expected 1)\n", btIsUniform(tree1));
  printf("btIsUniform(tree4) = %d (expected 0)\n", btIsUniform(tree4));
  
  btFree(tree1);
  btFree(tree2);
  btFree(tree3);
  btFree(tree4);
}
