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
/* Macros & Data Structures                  */
/*********************************************/
#define MAX_TREES 512
#define DPOFF(x, y, z)  (((x) * (y)) + (z))

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
        /* Generate left and right sub-trees */
        genbstnum(s, i - 1, sz, dp);
        genbstnum(i + 1, e, sz, dp);
        dp[dpoff] += dp[DPOFF(s, sz, i - 1)] * dp[DPOFF(i + 1, sz, e)];
    }

    /* NULL terminated leaf nodes are set to 1 */
    dp[dpoff] = dp[dpoff] == 0 ? 1: dp[dpoff];
}

/***********************************************************************/
/* Given an integer n, generate all structurally unique BSTs           */
/* (binary search trees) that store values 1...n.                      */
/***********************************************************************/
int numTrees(int n)
{
    int *dpsz, sz = (n + 2) * (n + 2), retsz;
    int off = DPOFF(1, n + 2, n);

    /* Trust, but verify. */
    if (n <= 0)
        return -1;

    /* Allocate memoization array */
    dpsz = calloc(sz, sizeof(int));
    if (!dpsz)
        return -1;

    /* Generate number of trees for the size n */
    genbstnum(1, n, n + 2, dpsz);

    /* Save result and free memoization array */
    retsz = dpsz[off];
    free(dpsz);
    return retsz;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 2;
    printf("Number of Unique BSTs %d = %d!\n", n, numTrees(n));
    return 0;
}
