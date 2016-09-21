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
/* BTreeDfs: Depth first traversal!                                    */
/*                                                                     */
/***********************************************************************/
void BTreeDfs(struct TreeNode* root, int level, int *maxdepth)
{
    /* If the node is invalid, then return */
    if (!root)
        return NULL;
    *maxdepth = *maxdepth <= level ? level + 1 : *maxdepth;
    BTreeDfs(root->right, level + 1, maxdepth);
    BTreeDfs(root->left, level + 1, maxdepth);
}

/***********************************************************************/
/* Given a binary tree, find its maximum depth.                        */
/*                                                                     */
/* The maximum depth is the number of nodes along the longest path from*/
/* the root node down to the farthest leaf node.                       */
/***********************************************************************/
int maxDepth(struct TreeNode *root)
{
    int maxdepth = 0;
    BTreeDfs(root, 0, &maxdepth);
    return maxdepth;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {8, 6, 3, 1, 9, 15, 7};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root = CreateBtree(a, 0, len - 1);

    printf("Inorder Traversal :\n");
    InorderBtree(root);
    printf("Max Depth of B Tree = %d :\n", maxDepth(root));
    FreeBtree(root);
    return 0;
}
