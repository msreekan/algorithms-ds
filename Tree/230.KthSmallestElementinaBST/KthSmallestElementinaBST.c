/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/***********************************************************************/
/* inorder: Run an inorder!                                            */
/*                                                                     */
/***********************************************************************/
void inorder(struct TreeNode *root, int k, int *count, int **val)
{
    /* Valdate. */
    if (!root || *val)
        return;
    inorder(root->left, k, count, val);
    if(*count == k)
        *val = &root->val;
    ++*count;
    inorder(root->right, k, count, val);
}

/***********************************************************************/
/* Given a binary search tree, write a function kthSmallest to find the*/
/* kth smallest element in it.                                         */
/* Note:                                                               */
/* You may assume k is always valid, 1 ? k ? BST's total elements.     */
/* Follow up:                                                          */
/* What if the BST is modified (insert/delete operations) often and you*/
/* need to find the kth smallest frequently? How would you optimize the*/
/* kthSmallest routine?                                                */
/***********************************************************************/
int kthSmallest(struct TreeNode* root, int k)
{
    int *val = NULL;
    int count = 1;
    inorder(root, k, &count, &val);
    return *val;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Hello world!\n");
    return 0;
}
