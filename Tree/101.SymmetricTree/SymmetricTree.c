/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"
#include <stdbool.h>

#if RECURSIVE
/***********************************************************************/
/* ChkSymmetry: Check Binary Tree Symmetry!                            */
/*                                                                     */
/***********************************************************************/
int ChkSymmetry(struct TreeNode *left, struct TreeNode *right)
{
    /* If any of these pointers are NULL, or if their values mismatch,
       then return FALSE */
    if ((!left && right) || (left && !right) ||
        (left && (left->val != right->val)))
        return false;

    /* If left and right are NULL, return true. Else continue
    recursion */
    return (left && right) ? ChkSymmetry(left->left, right->right) &&
                             ChkSymmetry(left->right, right->left) :
                             true;
}

/***********************************************************************/
/* Given a binary tree, check whether it is a mirror of itself (ie,    */
/* symmetric around its center).                                       */
/***********************************************************************/
bool isSymmetric(struct TreeNode *root)
{
    return ChkSymmetry(root->left, root->right);
}
#else
/***********************************************/
/* Macros                                      */
/***********************************************/
#define MAX_DEPTH 1024

/***********************************************************************/
/* Given a binary tree, check whether it is a mirror of itself (ie,    */
/* symmetric around its center).                                       */
/***********************************************************************/
bool isSymmetric(struct TreeNode *root)
{
    void *stack1 = NULL, *stack2 = NULL;
    bool status = false;
    struct TreeNode *ltree, *rtree;

    /* If the tree is NULL */
    if (!root) return true;

    /* Initialize the stack */
    if (!(stack1 = StackAlloc(MAX_DEPTH, sizeof(struct TreeNode *))) ||
        !(stack2 = StackAlloc(MAX_DEPTH, sizeof(struct TreeNode *))))
        goto __exit;

    /* Loop */
    ltree = root->left;
    rtree = root->right;
    while ((ltree || rtree) && status == false)
    {
        /* 1. If there is an asymmetry break.
           2. Else push the right subtree to the stack, break if it fails.
           3. Push the left subtree to the stack, break if it fails*/
        if (!ltree || !rtree || ltree->val != rtree->val ||
            ltree->right && StackPush(stack1, &ltree->right) ||
            rtree->left && StackPush(stack2, &rtree->left))
            break;

        /* If it's a non leaf node, then move into the children */
        else if  (rtree->right || ltree->left) {
            rtree = rtree->right;
            ltree = ltree->left;
        }
        /* Else pop */
        else
        {
            /* If either of the stacks failed to pop, set NULL */
            if (StackPop(stack1, &ltree))
                ltree = NULL;
            if (StackPop(stack2, &rtree))
                rtree = NULL;
        }
    }

    /* If both the pointers are NULL, then symmetric */
    if (!ltree && !rtree)
        status = true;

__exit:
    if (stack1) StackFree(stack1);
    if (stack2) StackFree(stack2);
    return status;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 3, 2, 1, 6};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Inorder TREE \n");
    InorderBtree(root);
    printf("Tree Asymmetry : %d \n", isSymmetric(root));
    FreeBtree(root);
    return 0;
}
