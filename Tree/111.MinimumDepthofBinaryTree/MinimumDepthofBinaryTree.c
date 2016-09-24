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
/* CheckMinDepth: Recursively get the minimum depth of btree.          */
/*                                                                     */
/***********************************************************************/
void CheckMinDepth(struct TreeNode* root, int level, int *depth)
{
    /* If the caller is leaf node, then return. */
    if (!root)
        return;

    /* If it's a leaf node, then update the depth*/
    if (!root->left && !root->right && (*depth > (level + 1) || !*depth))
        *depth = level + 1;
    CheckMinDepth(root->left, level + 1, depth);
    CheckMinDepth(root->right, level + 1, depth);
}

/***********************************************************************/
/* Given a binary tree, find its minimum depth.                        */
/*                                                                     */
/* The minimum depth is the number of nodes along the shortest path    */
/* from the root node down to the nearest leaf node.                   */
/***********************************************************************/
int minDepth(struct TreeNode* root)
{
    int depth = 0;
    CheckMinDepth(root, 0, &depth);
    return depth;
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
    printf("\n");
    printf("Minimum Depth = %d :\n", minDepth(root));
    FreeBtree(root);
    return 0;
}
