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
/* Given two binary trees, write a function to check if they are equal */
/* or not.                                                             */
/* Two binary trees are considered equal if they are structurally      */
/* identical and the nodes have the same value.                        */
/***********************************************************************/
bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    /* If there is a pointer mismatch, then return false */
    if ((!p && q) || (!q && p))
        return false;

    /* Else, we proceed to check values and then recursively traverse
       left and right sub-trees. */
    else if (p && q) {
        if (q->val != p->val)
            return false;
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
    return true; // both pointers are NULL
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[] = {1, 2, 4, 5, 6, 7}, a2[] = {1, 2, 4, 5, 6};
    int len1 = sizeof(a1) / sizeof(int), len2 = sizeof(a2) / sizeof(int);
    struct TreeNode *p, *q;
    p = CreateBtree(a1, 0, len1 - 1);
    q = CreateBtree(a2, 0, len2 - 1);
    printf("Inorder P : \n");
    InorderBtree(p);
    printf("Inorder Q : \n");
    InorderBtree(q);
    if (p && q)
        printf("\nP and Q Comparison = %d :\n", isSameTree(p, q));
    FreeBtree(p);
    FreeBtree(q);
    return 0;
}
