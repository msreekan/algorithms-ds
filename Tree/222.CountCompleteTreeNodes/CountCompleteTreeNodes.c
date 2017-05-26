/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "..\Utils\btree.h"

/***********************************************************************/
/* Given a complete binary tree, count the number of nodes.            */
/* Definition of a complete binary tree from Wikipedia:                */
/* In a complete binary tree every level, except possibly the last, is */
/* completely filled, and all nodes in the last level are as far left  */
/* as possible. It can have between 1 and 2h nodes inclusive at the    */
/* last level h.                                                       */
/***********************************************************************/
int countNodes(struct TreeNode* root)
{
    struct TreeNode *l, *r;
    int depth = 1;

    /* If the node is NULL, then return 0. */
    if (!root)
        return 0;

    /* The sub-structure here has one property. If the depth of
    left and right children are same, then the total number of the
    nodes can be claculated using the formula 2^n - 1.
    If the depth is not the same, then we need to recursively
    go into sub-trees until we narrow down the tree with imbalanced
    structure. */

    /* Calculate the left and right tree depth. */
    l = root->left;
    r = root->right;
    while (l && r) {
        depth++;
        l = l->left;
        r = r->right;
    }

    /* If the depth is same, then we can calculate the node count and
    return. */
    if (!l && !r)
        return (1 << depth) - 1;

    /* Else recursively repeat the above until we reach the balanced
    sub-tree. */
    return countNodes(root->left) + countNodes(root->right) + 1;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int len = sizeof(arr) / sizeof(int);
    struct TreeNode *root = CreateBtree(arr, 0, len - 1);

    printf("Number of nodes = %d :\n", countNodes(root));
    FreeBtree(root);
    return 0;
}
