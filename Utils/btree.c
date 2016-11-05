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
/* CreateBLtree: Create binary linked tree from an integer array       */
/*                                                                     */
/***********************************************************************/
struct TreeLinkNode *CreateBLTree(int *arr, int s, int e)
{
    struct TreeLinkNode *root;
    int mid = s + ((e - s + 1) / 2);

    /* Array is empty */
    if (s > e)
        return NULL;
    root = malloc(sizeof(struct TreeLinkNode));
    if (!root)
        return NULL;

    root->val = arr[mid];
    root->next = NULL;
    root->left = CreateBLTree(arr, s, mid - 1);
    root->right = CreateBLTree(arr, mid + 1, e);
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

/***********************************************************************/
/* InorderBLtree: Inorder print of BLtree                              */
/*                                                                     */
/***********************************************************************/
void InorderBLTree(struct TreeLinkNode *root)
{
    /* Validate the node */
    if (!root)
        return;
    InorderBLTree(root->left);
    printf("%d ", root->val);
    InorderBLTree(root->right);
}

/***********************************************************************/
/* PreorderBtree: Preorder print of Btree                              */
/*                                                                     */
/***********************************************************************/
void PreorderBtree(struct TreeNode *root)
{
    if (!root)
        return;
    printf("%d ", root->val);
    PreorderBtree(root->left);
    PreorderBtree(root->right);
}

/***********************************************************************/
/* PostorderBtree: Postorder print of Btree                            */
/*                                                                     */
/***********************************************************************/
void PostorderBtree(struct TreeNode *root)
{
    if (!root)
        return;
    PostorderBtree(root->left);
    PostorderBtree(root->right);
    printf("%d ", root->val);
}

/***********************************************************************/
/* InorderBtreeArr: Inorder storing of Btree into an array             */
/*                                                                     */
/***********************************************************************/
void InorderBtreeArr(struct TreeNode *root, int **arr)
{
    if (!root)
        return;
    InorderBtreeArr(root->left, arr);
    **arr = root->val;
    (*arr) += 1;
    InorderBtreeArr(root->right, arr);
}

/***********************************************************************/
/* PreorderBtreeArr: Preorder storing of Btree into an array           */
/*                                                                     */
/***********************************************************************/
void PreorderBtreeArr(struct TreeNode *root, int **arr)
{
    if (!root)
        return;
    **arr = root->val;
    (*arr) += 1;
    PreorderBtreeArr(root->left, arr);
    PreorderBtreeArr(root->right, arr);
}

/***********************************************************************/
/* PreorderBtreeBArr: Preorder storing of Btree nodes into an array    */
/*                                                                     */
/***********************************************************************/
void PreorderBtreeBArr(struct TreeNode *root, struct TreeNode ***arr)
{
    if (!root)
        return;
    **arr = root;
    (*arr) += 1;
    PreorderBtreeBArr(root->left, arr);
    PreorderBtreeBArr(root->right, arr);
}

/***********************************************************************/
/* PostorderBtreeArr: Postorder storing of Btree into an array         */
/*                                                                     */
/***********************************************************************/
void PostorderBtreeArr(struct TreeNode *root, int **arr)
{
    if (!root)
        return;
    PostorderBtreeArr(root->left, arr);
    PostorderBtreeArr(root->right, arr);
    **arr = root->val;
    (*arr) += 1;
}

/***********************************************************************/
/* LevelTraversalBLtree: Level traversal of BLtree                     */
/*                                                                     */
/***********************************************************************/
void LevelTraversalBLtree(struct TreeLinkNode *root)
{
    struct TreeLinkNode *tnode;

    /* Validate the input */
    if (!root)
        return;

    /* Save pointer to the next level, print the present level */
    tnode = root->left ? root->left : root->right;
    do
        printf("%d ", root->val);
    while ((root = root->next));
    printf("\n");

    /* Move to the next level */
    LevelTraversalBLtree(tnode);
}

/***********************************************************************/
/* FreeBLtree: Free binary linked tree                                 */
/*                                                                     */
/***********************************************************************/
void FreeBLtree(struct TreeLinkNode *root)
{
    if (!root)
        return;

    FreeBLtree(root->left);
    root->left = NULL;
    FreeBLtree(root->right);
    root->right = NULL;
    free(root);
}
