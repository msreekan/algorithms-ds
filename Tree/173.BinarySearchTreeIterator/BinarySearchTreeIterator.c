/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Utils/btree.h"
#include "../Utils/stack.h"

/***************************************/
/* Macros                              */
/***************************************/
#define STACK_SIZE 1024

/***********************************************************************/
/* Implement an iterator over a binary search tree (BST). Your iterator*/
/* will be initialized with the root node of a BST.                    */
/* Calling next() will return the next smallest number in the BST.     */
/* Note: next() and hasNext() should run in average O(1) time and uses */
/* O(h) memory, where h is the height of the tree.                     */
/*                                                                     */
/* * Your BSTIterator will be called like this:                        */
/* struct BSTIterator *i = bstIteratorCreate(root);                    */
/* while (bstIteratorHasNext(i)) printf("%d\n", bstIteratorNext(i));   */
/* bstIteratorFree(i);                                                 */
/***********************************************************************/

/******************************************/
/* Data Structure                         */
/******************************************/
struct BSTIterator
{
    void *stack;
};

/***********************************************************************/
/* bstIteratorCreate: Create the iterator!                             */
/*                                                                     */
/***********************************************************************/
struct BSTIterator *bstIteratorCreate(struct TreeNode *root)
{
    struct BSTIterator *bsiter = NULL;

    /* Validate the input, allocate memory */
    if (!root || !(bsiter = calloc(1, sizeof(struct BSTIterator))) ||
        !(bsiter->stack = StackAlloc(STACK_SIZE,
          sizeof(struct TreeNode *))))
        goto __bexit;

    /* Push all the elements until we reach the smallest one */
    while (root) {
        StackPush(bsiter->stack, &root);
        root = root->left;
    }

    /* Return the handle */
    return bsiter;

    /* Exit by releasing the memory */
__bexit:
    if (bsiter && bsiter->stack)
        StackFree(bsiter->stack);
    if (bsiter)
        free(bsiter);
    return NULL;
}

/***********************************************************************/
/* bstIteratorHasNext: Return whether we have a next smallest number.  */
/*                                                                     */
/***********************************************************************/
bool bstIteratorHasNext(struct BSTIterator *iter)
{
    /* Validate the parameter */
    if (!iter) return false;

    return (!StackEmpty(iter->stack)) ? true : false;
}

/***********************************************************************/
/* bstIteratorNext: Return the next smallest number.                   */
/*                                                                     */
/***********************************************************************/
int bstIteratorNext(struct BSTIterator *iter)
{
    struct TreeNode *node, *tnode;

    /* Validate the parameter */
    if (!iter) return -1;

    /* Pop the node */
    if (StackPop(iter->stack, &node))
        return -1;

    /* Get to the smallest element in the right sub-tree. */
    tnode = node->right;
    while (tnode) {
        StackPush(iter->stack, &tnode);
        tnode = tnode->left;
    }

    /* Return the present node */
    return node->val;
}

/***********************************************************************/
/* bstIteratorFree: Deallocates memory previously allocated for the    */
/*                  iterator                                           */
/***********************************************************************/
void bstIteratorFree(struct BSTIterator *iter)
{
    /* Validate the parameter */
    if (!iter) return;

    /* Free the stack and the memory */
    StackFree(iter->stack);
    free(iter);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root = CreateBtree(a, 0, len - 1);
    struct BSTIterator *i;

    /* Validate the root */
    if (!root) return -1;

    /* Print the B-Tree */
    InorderBtree(root);

    /* Iterator */
    printf("\n");
    i = bstIteratorCreate(root);
    while (bstIteratorHasNext(i))
        printf("%d\n", bstIteratorNext(i));
    bstIteratorFree(i);

    /* Free the tree */
    FreeBtree(root);
    return 0;
}
