/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/***************************************/
/* Macros                              */
/***************************************/
#define MAX_SIZE 8192

/***********************************************************************/
/* traverserlr: Traverse root-right-left                               */
/*                                                                     */
/***********************************************************************/
void traverserlr(struct TreeNode* root, int *arr, int* rsize,
                 int *mlevel, int level)
{
    /* If node is invalid, then return. */
    if (!root)
        return;

    /* Save the node only when the present depth is greater then the
    previous maximum. */
    if (*mlevel < level) {
        *mlevel = level;             // update maximum
         arr[*rsize] = root->val;    // save the value
        (*rsize) += 1;               // update the size
    }

    /* Continue traversal */
    traverserlr(root->right, arr, rsize, mlevel, level + 1);
    traverserlr(root->left, arr, rsize, mlevel, level + 1);
}

/***********************************************************************/
/* Given a binary tree, imagine yourself standing on the right side of */
/* it, return the values of the nodes you can see ordered from top to  */
/* bottom.                                                             */
/***********************************************************************/
int* rightSideView(struct TreeNode* root, int* rsize)
{
    int *arr;
    int mlevel = -1;

    /* Sanity check and allocate space for the output array. */
    if (!root || !rsize || !(arr = malloc(sizeof(int) * MAX_SIZE)))
        return NULL;
    *rsize = 0;
    traverserlr(root, arr, rsize, &mlevel, 0);
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {1, 2, 3, 5, 6, 7, 8};
    int *a;
    int size;
    struct TreeNode *root;

    /* Create the tree. */
    root = CreateBtree(arr, 0, sizeof(arr) / sizeof(int) - 1);
    if (root) {
        int i;

        printf("Inorder Traversal :\n");
        InorderBtree(root);
        printf("\n");
        a = rightSideView(root, &size);
        for (i = 0; i < size; ++i)
            printf("%d, ", a[i]);
        free(a);
        printf("\n");
    }
    return 0;
}
