/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

#if O_N_SPACE
/***********************************************************************/
/* Given a binary tree, flatten it to a linked list in-place.          */
/***********************************************************************/
void flatten(struct TreeNode* root)
{
    struct TreeNode **narr, **sarr;
    int i;

    /* Allocate an array to store the nodes */
    if ((narr = malloc(sizeof(struct TreeNode *) * MAX_DEPTH)) == NULL)
        return;

    /* Preorder traversal */
    sarr = narr;
    PreorderBtreeBArr(root, &narr);

    /* Flatten */
    for (i = 0; sarr[i] != *narr; ++i)
    {
        sarr[i]->left = NULL;
        sarr[i]->right = sarr[i + 1];
    }
    free(sarr);
}
#else

/***********************************************************************/
/* rflatten: Recursively flatten!                                      */
/*                                                                     */
/***********************************************************************/
void rflatten(struct TreeNode *root, struct TreeNode **prev)
{
    /* Return if the root is invalid */
    if (!root)
        return;
    *prev = root; // tracks the last visited node on the left
    rflatten(root->left, prev);
    /*
    ** Flatten in 3 steps:
        1. Update right sub-tree of last visited node.
        2. Present left sub-tree becomes the new right.
        3. Set left pointer to NULL.
    */
    (*prev)->right = root->right; // 1
    root->right = (root->left) ? root->left : root->right; //2
    root->left = NULL; // 3
    rflatten((*prev)->right, prev);
}
/***********************************************************************/
/* Given a binary tree, flatten it to a linked list in-place.          */
/***********************************************************************/
void flatten(struct TreeNode* root)
{
    struct TreeNode *prev;
    rflatten(root, &prev);
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(a) / sizeof(int);
    struct TreeNode *root;

    root = CreateBtree(a, 0, len - 1);

    printf("Inorder Traversal :\n");
    InorderBtree(root);

    flatten(root);

    printf("\nInorder Traversal of Flattened Tree :\n");
    InorderBtree(root);
    FreeBtree(root);
    return 0;
}
