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

/***********************************************************************/
/* BstCheck: Recursively check for BST                                 */
/*                                                                     */
/***********************************************************************/
bool BstCheck(struct TreeNode* root, struct TreeNode** prev)
{
    /* If root is valid, then recursively traverse the tree while
    updating the prev pointer. */
    if (root && ((!BstCheck(root->left, prev)) ||
                (*prev && (*prev)->val >= root->val) ||
                !(*prev = root) || !BstCheck(root->right, prev)))
        return false;
    return true;
}

/***********************************************************************/
/* Given a binary tree, determine if it is a valid binary search tree  */
/* (BST).                                                              */
/* Assume a BST is defined as follows:                                 */
/* The left subtree of a node contains only nodes with keys less than  */
/* the node's key. The right subtree of a node contains only nodes with*/
/* keys greater than the node's key. Both the left and right subtrees  */
/* must also be binary search trees.                                   */
/***********************************************************************/
bool isValidBST(struct TreeNode* root)
{
    struct TreeNode *prev = NULL;
    return BstCheck(root, &prev);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {0};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root = CreateBtree(a, 0, len - 1);
    InorderBtree(root);
    printf("Btree Status = %d \n", isValidBST(root));
    FreeBtree(root);
    return 0;
}
