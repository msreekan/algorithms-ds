/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"
#include <stdbool.h>

/***********************************************************************/
/* ChkSymmetry: Check Binary Tree Symmetry!                            */
/*                                                                     */
/***********************************************************************/
int ChkSymmetry(struct TreeNode *left, struct TreeNode *right)
{
    /* If any of these pointers are NULL, or if their values mismatch,
       then return FALSE */
    if ((!left && right) || (left && !right) ||
        (left && (left->val != right->val)))
        return false;

    /* If left and right are NULL, return true. Else continue
    recursion */
    return (left && right) ? ChkSymmetry(left->left, right->right) &&
                             ChkSymmetry(left->right, right->left) :
                             true;
}

/***********************************************************************/
/* Given a binary tree, check whether it is a mirror of itself (ie,    */
/* symmetric around its center).                                       */
/***********************************************************************/
bool isSymmetric(struct TreeNode *root)
{
    return ChkSymmetry(root->left, root->right);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 3, 2, 1};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Inorder TREE \n");
    InorderBtree(root);
    printf("Tree Asymmetry : %d \n", isSymmetric(root));
    FreeBtree(root);
    return 0;
}
