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

/***********************************************************************/
/* CheckPathSum: Recursively check path sum.                           */
/*                                                                     */
/***********************************************************************/
void CheckPathSum(struct TreeNode* root, int psum, int sum,
                  bool *status)
{
    /* If the caller is leaf node, then return */
    if (!root || *status)
        return;

    /* If it's a leaf node, then check and update the depth status */
    psum += root->val;
    if (!root->left && !root->right && psum == sum)
        *status = 1;
    CheckPathSum(root->left, psum, sum, status);
    CheckPathSum(root->right, psum, sum, status);
}

/***********************************************************************/
/* Given a binary tree and a sum, determine if the tree has a          */
/* root-to-leaf path such that adding up all the values along the path */
/* equals the given sum.                                               */
/***********************************************************************/
bool hasPathSum(struct TreeNode* root, int sum)
{
    bool status = 0;
    CheckPathSum(root, 0, sum, &status);
    return status;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {8, 6, 3, 1, 9, 15, 7, 9};
    int len = sizeof(a) / sizeof(int), sum = 5;
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Inorder of the tree \n");
    InorderBtree(root);
    printf("\n");
    printf("Path sum for %d = %d:\n", sum, hasPathSum(root, sum));
    FreeBtree(root);
    return 0;
}
