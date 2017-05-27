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
/* nodeSeek: Seek to nodes!                                            */
/*                                                                     */
/***********************************************************************/
int nodeSeek(struct TreeNode* root, struct TreeNode* p,
                struct TreeNode* q, struct TreeNode **pr)
{
    int ret = 0;

    /* If the node is invalid or if the parent is already found,
    then return. */
    if (!root || *pr)
        return 0;

    /* If either of the children are found, then increment status. */
    if (root == p || root == q)
        ret += 1;
    ret += nodeSeek(root->right, p, q, pr);
    ret += nodeSeek(root->left, p, q, pr);

    /* If both the children are found and the parent is not set yet,
    then assign this node. */
    if (ret == 2 && !*pr)
        *pr = root;
    /* Return the count. */
    return ret;
}

/***********************************************************************/
/* Given a binary tree, find the lowest common ancestor (LCA) of two   */
/* given nodes in the tree. According to the definition of LCA on      */
/* Wikipedia: “The lowest common ancestor is defined between two nodes */
/* v and w as the lowest node in T that has both v and w as descendants*/
/* (where we allow a node to be a descendant of itself).”              */
/***********************************************************************/
struct TreeNode* lowestCommonAncestor(struct TreeNode* root,
                                      struct TreeNode* p,
                                      struct TreeNode* q)
{
    struct TreeNode *parent = NULL;
    nodeSeek(root, p, q, &parent);
    return parent;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
