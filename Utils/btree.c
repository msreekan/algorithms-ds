/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/***********************************************************************/
/* CreateBtree: Create binary tree from an integer array               */
/*                                                                     */
/***********************************************************************/
struct TreeNode *CreateBtree(int *arr, int s, int e)
{
    struct TreeNode *root;
    int mid = s + (e - s) / 2;

    /* We are the leaf nodes */
    if (e < s)
        return NULL;

    /* Allocate the node */
    root = malloc(sizeof(struct TreeNode ));
    if (!root)
        return NULL;
    /* Assign the value and recursively generate left and right
    sub-trees */
    root->val = arr[mid];
    root->left = CreateBtree(arr, s, mid - 1);
    root->right = CreateBtree(arr, mid + 1, e);
    return root;
}

/***********************************************************************/
/* FreeBtree: Free binary tree                                         */
/*                                                                     */
/***********************************************************************/
void FreeBtree(struct TreeNode *root)
{
    if (!root)
        return;
    FreeBtree(root->left);
    root->left = NULL;
    FreeBtree(root->right);
    root->left = root->right = NULL;
    free(root);
}

/***********************************************************************/
/* InorderBtree: Inorder print of Btree                                */
/*                                                                     */
/***********************************************************************/
void InorderBtree(struct TreeNode *root)
{
    if (!root)
        return;
    InorderBtree(root->left);
    printf("%d ", root->val);
    InorderBtree(root->right);
}
