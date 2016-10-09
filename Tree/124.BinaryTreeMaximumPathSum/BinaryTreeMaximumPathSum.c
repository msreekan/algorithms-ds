/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/***************************************/
/* Macros                              */
/***************************************/
#define MAX(a, b, c) ((((a) > (b)) ? (a) : (b)) > (c) ? \
                      (((a) > (b)) ? (a) : (b)) : (c))
#define MIN_INT -0x7FFFFFFF

/***********************************************************************/
/* maxSum: Recursively seek the maximum path sum!                      */
/*                                                                     */
/***********************************************************************/
int maxSum(struct TreeNode* root, int *max)
{
    int ml, mr, mx;

    /* Return zero if the root is NULL */
    if (!root) return 0;

    /* Get the maximum values from the left and right sub-trees */
    ml = maxSum(root->left, max);
    mr = maxSum(root->right, max);

    /* Maximum can be either
       1. The whole sub-tree, or
       2. Just the left subtree + root or
       3. Right sub-tree + root. */
    *max = *max < (mx = MAX(root->val + ml + mr, root->val + ml,
                            root->val + mr)) ? mx : *max;

    /* Return the larger of the two sub-trees + root or just the root. */
    return MAX(root->val, root->val + ml, root->val + mr);
}

/***********************************************************************/
/* Given a binary tree, find the maximum path sum. For this problem,   */
/* a path is defined as any sequence of nodes from some starting node  */
/* to any node in the tree along the parent-child connections. The path*/
/* does not need to go through the root.                               */
/***********************************************************************/
int maxPathSum(struct TreeNode* root)
{
    int sum1 = MIN_INT, sum2;
    sum2 = maxSum(root, &sum1);
    return sum1 > sum2 ? sum1 : sum2;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {-1, -2, 3, -1, -1};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Max Path Sum = %d :\n", maxPathSum(root));
    FreeBtree(root);
    return 0;
}
