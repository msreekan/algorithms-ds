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
/* Invert a binary tree!                                               */
/*                                                                     */
/***********************************************************************/
struct TreeNode* invertTree(struct TreeNode* root)
{
    struct TreeNode *t;

    /* Validate. */
    if (!root)
      return NULL;

    /* Swap the children. */
    t = root->left;
    root->left = root->right;
    root->right = t;

    /* Invert the sub-trees. */
    invertTree(root->left);
    invertTree(root->right);

    /* Return the node. */
    return root;
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
