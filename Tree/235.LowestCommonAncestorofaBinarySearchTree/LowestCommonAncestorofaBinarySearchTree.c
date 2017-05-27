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
/* Given a binary search tree (BST), find the lowest common ancestor   */
/* (LCA) of two given nodes in the BST.                                */
/* According to the definition of LCA on Wikipedia: “The lowest common */
/* ancestor is defined between two nodes v and w as the lowest node in */
/* T that has both v and w as descendants (where we allow a node to be */
/* a descendant of itself).”                                           */
/***********************************************************************/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root,
                                      struct TreeNode* p,
                                      struct TreeNode* q)
{
    /* Validate the parameter. */
    if (!root || !p || !q)
        return NULL;

    /* Check whether the nodes fall in left or right sub-tree.
       The idea is that the lowest common ancestor value would be
       in between the two nodes. And with the below traversal, it also
       would be the first node with this property.
    */
    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    return root;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
