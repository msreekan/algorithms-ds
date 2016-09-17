/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/btree.h"

/*********************************************/
/* Macros & Data Structures                  */
/*********************************************/
#define MEMOIZATION 1
#define DPOFF(x, y, z)  (((x) * (y)) + (z))

#if MEMOIZATION
/***********************************************************************/
/* genbstnum: Recursively generate number of unique BSTs.              */
/*                                                                     */
/***********************************************************************/
void genbstnum(int s, int e, int sz, int *dp)
{
    int i, dpoff = DPOFF(s, sz, e);

    /* If value cached, then return. */
    if (dp[dpoff]) return;

    /* Loop from the start to the end selecting different root values. */
    for (i = s; i <= e; ++i)
    {
        /* Generate number of left and right sub-trees */
        genbstnum(s, i - 1, sz, dp);
        genbstnum(i + 1, e, sz, dp);
        dp[dpoff] += dp[DPOFF(s, sz, i - 1)] * dp[DPOFF(i + 1, sz, e)];
    }

    /* NULL terminations are set to 1 */
    dp[dpoff] = dp[dpoff] == 0 ? 1: dp[dpoff];
}

/***********************************************************************/
/* genbst: Generate a BSTs from a list of numbers                      */
/*                                                                     */
/***********************************************************************/
struct TreeNode **genbst(int start, int end, int sz,
                         struct TreeNode ***dpt, int *dpsz)
{
    int i, j, k, cnt = 0, dpoff = DPOFF(start, sz, end);
    struct TreeNode **bst_arr = NULL, **lbst_arr, **rbst_arr;
    struct TreeNode *root;

    /* If valid, then return the cached value */
    if (dpt[dpoff] != NULL)
        return dpt[dpoff];

    /* Initialize array with the number of entries. */
    if ((bst_arr  = calloc(dpsz[dpoff], sizeof(struct TreeNode *))) == NULL)
        return NULL;

    /* Loop from the start to the end selecting different root values. */
    for (i = start; i <= end; ++i)
    {
        /* Generate left and right sub-trees */
        lbst_arr = genbst(start, i - 1, sz, dpt, dpsz);
        rbst_arr = genbst(i + 1, end, sz, dpt, dpsz);

        /* Generate all possible combinations with i as the root */
        for (j = 0; j < dpsz[DPOFF(start, sz, i - 1)] && lbst_arr; ++j)
            for (k = 0; k < dpsz[DPOFF(i + 1, sz, end)] && rbst_arr; ++k)
            {
                /* Allocate root */
                if ((root = malloc(sizeof(struct TreeNode))) == NULL)
                    return NULL;
                root->val = i;

                /* Assign left and right sub-trees and root. */
                root->left = lbst_arr[j];
                root->right = rbst_arr[k];
                bst_arr[cnt++] = root;
            }
    }

    /* Update the cache */
    dpt[dpoff] = bst_arr;
    return bst_arr;
}

/***********************************************************************/
/* Given an integer n, generate all structurally unique BSTs           */
/* (binary search trees) that store values 1...n.                      */
/***********************************************************************/
struct TreeNode** generateTrees(int n, int *returnSize)
{
    struct TreeNode ***dpt;
    struct TreeNode **t = NULL;
    int *dpsz, sz = (n + 2) * (n + 2), i;

    if (n >= 1) {
        /* Allocate memoization array */
        dpt = calloc((sizeof(struct TreeNode **) + sizeof(int)) * sz, 1);
        if (!dpt)
            return NULL;
        dpsz = (int *)(dpt + sz);

        /* Generate number of trees */
        genbstnum(1, n, n + 2, dpsz);

        /* Generate Trees for the size n */
        t = genbst(1, n, (n + 2), dpt, dpsz);
        *returnSize = dpsz[DPOFF(1, n + 2, n)];

        /* Free all the array except the final 1 - n solution */
        for (i = 0; i < sz; ++i)
            if (dpt[i] && dpt[i] != t) free(dpt[i]);
        free(dpt);
    }
    return t;
}
#else
/***********************************************************************/
/* genbst: Generate a BSTs from a list of numbers                      */
/*                                                                     */
/***********************************************************************/
struct TreeNode **genbst(int start, int end, int *retsz)
{
    int i, lret, rret, j, k, cnt = 0, arr_sz = 0;
    struct TreeNode **bst_arr = NULL, **lbst_arr, **rbst_arr;
    struct TreeNode *root;

    /* Initialize array with one entry.  */
    if ((bst_arr  = calloc(1, sizeof(struct TreeNode *))) == NULL)
        goto __exit;

    /* Loop from the start to the end selecting different root values. */
    for (i = start; i <= end; ++i)
    {
        /* Generate left and right sub-trees */
        lbst_arr = genbst(start, i - 1, &lret);
        rbst_arr = genbst(i + 1, end, &rret);

        /* Generate all possible combinations with i as the root */
        for (j = 0; j < lret; ++j)
            for (k = 0; k < rret; ++k)
            {
                /* Allocate root */
                if ((root = malloc(sizeof(struct TreeNode))) == NULL)
                    goto __exit;
                root->val = i;

                /* Assign left and right sub-trees */
                root->left = lbst_arr[j];
                root->right = rbst_arr[k];
                if (cnt == arr_sz) {
                    arr_sz += MAX_TREES;
                    bst_arr = realloc(bst_arr, arr_sz *
                                      sizeof(struct TreeNode *));
                    if (!bst_arr)
                        goto __exit;
                }

                /* Array of trees structured by values 'start' to 'end' */
                bst_arr[cnt++] = root;
            }
        free(lbst_arr);
        free(rbst_arr);
    }

__exit:
    /* Return size will be zero only in case of failure */
    *retsz = cnt > 0 ? cnt : 1;
    *retsz = !bst_arr ? 0 : *retsz;
    return bst_arr; // Note, this could be NULL
}

/***********************************************************************/
/* Given an integer n, generate all structurally unique BSTs           */
/* (binary search trees) that store values 1...n.                      */
/***********************************************************************/
struct TreeNode** generateTrees(int n, int *returnSize)
{
    struct TreeNode **t = NULL;

    if (n >= 1) {
        /* Generate Trees for the size n */
        t = genbst(1, n, returnSize);
    }
    return t;
}
#endif

/***********************************************************************/
/* prn: Print tree!                                                    */
/*                                                                     */
/***********************************************************************/
void prn(struct TreeNode *root)
{
    if (!root)
    {
        printf("NULL, ");
        return;
    }
    printf("%d ", root->val);
    prn(root->left);
    prn(root->right);
}

/***********************************************************************/
/* free_tree: Free tree!                                               */
/*                                                                     */
/***********************************************************************/
void free_tree(struct TreeNode *root)
{
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    root->left = root->right = NULL;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct TreeNode** arr;
    int ret, i;
    arr = generateTrees(8, &ret);
    for (i = 0; i < ret; ++i)
    {
        prn(arr[i]);
        printf("\n");
    }
    for (i = 0; i < ret; ++i)
        free_tree(arr[i]);
    free(arr);

    return 0;
}
