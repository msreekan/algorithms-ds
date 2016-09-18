/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"
#include "../Utils/generic.h"

/***********************************************************************/
/* CheckBST: Recursively figure out the aberrations !                  */
/*                                                                     */
/***********************************************************************/
void CheckBST(struct TreeNode *root, struct TreeNode **prevd,
              struct TreeNode **prev1, struct TreeNode **prev2)
{
    /* Stop if NULL */
    if (!root)
        return;

    /* Traverse the left sub-tree */
    CheckBST(root->left, prevd, prev1, prev2);

    /* If there is an aberration, then record the nodes for swapping */
    if (*prevd && (*prevd)->val >= root->val) {
        if (!(*prev1))
            *prev1 = *prevd;
        *prev2 = root;
        }

    /* Save the previous node pointer and proceed to right sub-tree */
    *prevd = root;
    CheckBST(root->right, prevd, prev1, prev2);
}

/***********************************************************************/
/* Two elements of a binary search tree (BST) are swapped by mistake.  */
/* Recover the tree without changing its structure.                    */
/* Note:                                                               */
/* A solution using O(n) space is pretty straight forward. Could you   */
/* devise a constant space solution?                                   */
/*                                                                     */
/***********************************************************************/
void recoverTree(struct TreeNode* root)
{
    struct TreeNode *prevd = NULL, *prev1 = NULL, *prev2 = NULL;
    CheckBST(root, &prevd, &prev1, &prev2); // find
    INT_SWAP(&prev2->val, &prev1->val); // swap!
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 0};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Before the fix :\n");
    InorderBtree(root);
    recoverTree(root);
    printf("\nAfter the fix:\n");
    InorderBtree(root);
    FreeBtree(root);
    return 0;
}
