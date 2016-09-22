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
/* Given an array where elements are sorted in ascending order, convert*/
/* it to a height balanced BST.                                        */
/***********************************************************************/
struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    struct TreeNode *root;
    int mid = numsSize / 2;

    /* Validate the size */
    if (numsSize <= 0)
        return NULL;

    /* Allocate the new node */
    if ((root = malloc(sizeof(struct TreeNode))) == NULL)
        return NULL;
    root->val = nums[mid];

    /* Recursively generate left and right sub-trees */
    root->left = sortedArrayToBST(nums, mid);
    root->right = sortedArrayToBST(&nums[mid + 1], numsSize - mid - 1);
    return root;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {8, 6, 3, 1, 9, 15, 7, 9};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Inorder of the tree \n");
    InorderBtree(root);
    FreeBtree(root);

    root = sortedArrayToBST(a, len);
    printf("\nInorder of the Generated tree \n");
    InorderBtree(root);
    FreeBtree(root);
    return 0;
}
