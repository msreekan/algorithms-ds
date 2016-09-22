/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/*******************************************/
/* Macros                                  */
/*******************************************/
#define MAX_LEVEL_ENTRY   512  // max entries in a level
#define MAX_LEVEL         1024 // max levels

/***********************************************************************/
/* RLTraverse: Recursive level traversal!                              */
/*                                                                     */
/***********************************************************************/
void RLTraverse(struct TreeNode *root, int level, int *csizes,
                int *rsize, int **larr)
{
    /* If node is invalid, or we exceed the allocated memory, return */
    if (!root || (level >= MAX_LEVEL))
        return;

    /* If the array is not allocated, then do the same */
    if (!csizes[level] &&
        ((larr[level] = malloc(sizeof(int) * MAX_LEVEL_ENTRY)) == NULL))
        return;

    /* Assign the values, increment the count and level size. Also check
       memory bounds. */
    if (csizes[level] < MAX_LEVEL_ENTRY) {
        *(larr[level] + csizes[level]) = root->val;
        csizes[level] += 1;
    }
    *rsize = (level >= *rsize) ? level + 1: *rsize;

    /* Traverse left, then right sub-trees */
    RLTraverse(root->left, level + 1, csizes, rsize, larr);
    RLTraverse(root->right, level + 1, csizes, rsize, larr);
}

/***********************************************************************/
/* Given a binary tree, return the level order traversal of its nodes' */
/* values. (ie, from left to right, level by level).                   */
/***********************************************************************/
int** levelOrder(struct TreeNode *root, int **columnSizes,
                 int *returnSize)
{
    int **larr;

    /* Allocate the entry array and column size array. */
    if ((larr = malloc(MAX_LEVEL * sizeof(int *))) == NULL)
        return NULL;
    if ((*columnSizes = calloc(MAX_LEVEL, sizeof(int))) == NULL)
    {
        free(larr);
        return NULL;
    }

    *returnSize = 0;

    /* Invoke the function, return the entries. */
    RLTraverse(root, 0, *columnSizes, returnSize, larr);
    return larr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {8, 6, 3, 1, 9, 15, 7};
    int len = sizeof(a) / sizeof(int), ret, *csize, i, j;
    int **larr;
    struct TreeNode *root;
    root = CreateBtree(a, 0, len - 1);
    printf("Inorder of the tree \n");
    InorderBtree(root);
    printf("\n Level Order :\n");
    larr = levelOrder(root, &csize, &ret);
    for (i = 0; i < ret && larr; ++i)
    {
        for (j = 0; j < csize[i]; ++j)
            printf("%d, ", *(larr[i] + j));
        free(larr[i]);
        printf("\n");
    }
    free(csize);
    return 0;
}
