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
/* CheckBalance: Recursively check the btree balance.                  */
/*                                                                     */
/***********************************************************************/
int CheckBalance(struct TreeNode* root, int level, bool *code)
{
    int llevel, rlevel;

    /* Return FALSE, stop recursion as soon as code is reset. */
    if (!*code)
        return false;

    /* If the caller is leaf node, then return the same level */
    if (!root)
        return level - 1;

    llevel = CheckBalance(root->left, level + 1, code);
    rlevel = CheckBalance(root->right, level + 1, code);
    if (abs(llevel - rlevel) > 1)
        *code = false;
    return llevel > rlevel ? llevel : rlevel;
}
/***********************************************************************/
/* Given a binary tree, determine if it is height-balanced.            */
/*                                                                     */
/* For this problem, a height-balanced binary tree is defined as a     */
/* binary tree in which the depth of the two subtrees of every node    */
/* never differ by more than 1.                                        */
/***********************************************************************/
bool isBalanced(struct TreeNode* root)
{
    bool code = true;
    CheckBalance(root, 0, &code);
    return code;
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
    printf("Is Balance = %d :\n", isBalanced(root));
    FreeBtree(root);

    return 0;
}
