/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/*********************************************/
/* Macros                                    */
/*********************************************/
#define MAX_DEPTH   1024
#define MAX_BREADTH 512

/***********************************************************************/
/* getMaxDepth: Recursively get Btree maximum depth!                   */
/*                                                                     */
/***********************************************************************/
int getMaxDepth(struct TreeNode *root, int level)
{
    int depthl, depthr;
    if (!root)
        return level;
    depthl = getMaxDepth(root->left, level + 1);
    depthr = getMaxDepth(root->right, level + 1);
    return  depthl > depthr ? depthl : depthr;
}

/***********************************************************************/
/* lorderBottom: Recursively generate bottom up level order!           */
/*                                                                     */
/***********************************************************************/
void lorderBottom(struct TreeNode *root, int level, int **arr,
                  int *csizes, int depth)
{
    int offset = depth - level;

    /* If root is NULL, return */
    if (!root)
        return;

    /* If the array is not allocated yet, then do the same */
    if (!csizes[offset] &&
        ((arr[offset] = malloc(sizeof(int) * MAX_BREADTH)) == NULL))
        return;

    /* Save and increment the size */
    *(arr[offset] + csizes[offset]) = root->val;
    csizes[offset]++;

    /* Continue traversal */
    lorderBottom(root->left, level + 1, arr, csizes, depth);
    lorderBottom(root->right, level + 1, arr, csizes, depth);
}


/***********************************************************************/
/* Given a binary tree, return the bottom-up level order traversal of  */
/* its nodes' values. (ie, from left to right, level by level from leaf*/
/* to root).                                                           */
/***********************************************************************/
int** levelOrderBottom(struct TreeNode *root, int **columnSizes,
                       int* returnSize)
{
    int **arr;
    int depth;

    /* Validate */
    if (!root)
        return NULL;

    /* Get maximum depth */
    depth = getMaxDepth(root, 0);

    /* Allocate the pointer to the list */
    arr = malloc(sizeof(int *) * (depth + 1));
    if (!arr)
        return NULL;

    /* Allocate space for storing array lengths */
    *columnSizes = calloc(depth + 1, sizeof(int));
    if (!*columnSizes)
    {
        free(arr);
        return NULL;
    }

    /* Set the array length, traverse and return */
    *returnSize = depth + 1;
    lorderBottom(root, 0, arr, *columnSizes, depth);
    return arr;
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

    printf("\n Reverse Level Order :\n");
    larr = levelOrderBottom(root, &csize, &ret);
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
