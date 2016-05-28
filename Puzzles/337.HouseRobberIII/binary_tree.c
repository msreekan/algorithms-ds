/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include "binary_tree.h"

/***********************************************************************/
/* Binary Tree Routines                                                */
/***********************************************************************/

/***********************************************************************/
/* free_tree: Free tree                                                */
/*                                                                     */
/***********************************************************************/
void free_tree(struct node *root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

/***********************************************************************/
/* generate_tree: Generate a binary tree from an array                 */
/*                                                                     */
/***********************************************************************/
struct node *generate_tree(int *a, int start, int end)
{
    struct node *root;
    int mid = start + (end - start) / 2;

    /* Done */
    if (start > end)
        return NULL;

    /* Allocate the node */
    root = malloc(sizeof(struct node));
    if (!root)
        return NULL;

    /* Assign value */
    root->val = a[mid];

    /* Generate the left and right sub-tree */
    root->left = generate_tree(a, start, mid - 1);
    root->right = generate_tree(a, mid + 1, end);

    /* Return the node */
    return root;
}
