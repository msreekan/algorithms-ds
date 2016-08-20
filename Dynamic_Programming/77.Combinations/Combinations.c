/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ENT_COUNT (16 * 1024)

/***********************************************************************/
/* save_arr: Save generated combinations!                              */
/*                                                                     */
/***********************************************************************/
void save_arr(int *arr, int k, int **c, int *sz, int *csizes)
{
    int i;
    /* Allocate memory */
    c[*sz] = malloc(sizeof(int) * k);
    if (!c[*sz]) return;

    /* Copy the generated array */
    for (i = 0; i < k; ++i)
        *(c[*sz] + i) = arr[i];
    csizes[*sz] = k;
    (*sz) += 1;
}

/***********************************************************************/
/* combo: Generate combinations!                                       */
/*                                                                     */
/***********************************************************************/
void combo(int *arr, int ns, int n, int kc, int k, int **c, int *sz,
          int *csizes)
{
    int i;

    /* If we are done generating the combination, save and return */
    if (kc == k)
        save_arr(arr, k, c, sz, csizes);

    /* Else generate the numbers */
    else
    for (i = ns; (arr[kc] =  i) && i + (k - kc - 1) <= n; ++i)
        combo(arr, i + 1, n, kc + 1, k, c, sz, csizes);
}

/***********************************************************************/
/* Given two integers n and k, return all possible combinations of k   */
/* numbers out of 1 ... n.                                             */
/*                                                                     */
/* For example,                                                        */
/* If n = 4 and k = 2, a solution is:                                  */
/* [                                                                   */
/* [2,4],                                                              */
/* [3,4],                                                              */
/* [2,3],                                                              */
/* [1,2],                                                              */
/* [1,3],                                                              */
/* [1,4],                                                              */
/* ]                                                                   */
/***********************************************************************/
int** combine(int n, int k, int** columnSizes, int* returnSize)
{
    int *arr;
    int **carr;

    /* Validate */
    if (k > n)
        return NULL;

    /* Allocate the array */
    arr = malloc(sizeof(int) * k);
    if (!arr)
        return NULL;

    /* Allocate the column array */
    carr = malloc(sizeof(int *) * ENT_COUNT);
    if (!carr)
    {
        free(arr);
        return NULL;
    }

    /* Allocate space for column count */
    *columnSizes = malloc(sizeof(int) *  ENT_COUNT);
    if (!*columnSizes)
    {
        free(carr);
        return NULL;
    }

    /* Never mind the failure */
    *returnSize = 0;
    combo(arr, 1, n, 0, k, carr, returnSize, *columnSizes);
    free(arr);
    return carr;
}
