/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define RECURSIVE_BOTTOM_UP 1

#if RECURSIVE_DFS
/****************************************/
/* Macros                               */
/****************************************/
#define MAX_INT 0x7FFFFFFF
#define OFF(r, n, c) (((r) * (n)) + (c))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/***********************************************************************/
/* GetMin: Get minimum path from the triangle!                         */
/*                                                                     */
/***********************************************************************/
void GetMin(int **tr, int row, int mrow, int idx, int *sum, int *dp)
{
    /* If we have reached the end, then return. */
    if (mrow == row)
        return;

    /* Check the first available path. */
    if (dp[OFF(row, mrow, idx)] == MAX_INT) {
        dp[OFF(row, mrow, idx)] = (tr[row])[idx];
        GetMin(tr, row + 1, mrow, idx, &dp[OFF(row, mrow, idx)], dp);
    }

    /* If the value is not cached, then check the next available path. */
    if (dp[OFF(row, mrow, idx + 1)] == MAX_INT) {
        dp[OFF(row, mrow, idx + 1)] = (tr[row])[idx + 1];
        GetMin(tr, row + 1, mrow, idx + 1, &dp[OFF(row, mrow, idx + 1)],
               dp);
    }

    /* Update sum with the minimum value */
    (*sum) += MIN(dp[OFF(row, mrow, idx + 1)], dp[OFF(row, mrow, idx)]);
}

/***********************************************************************/
/* Given a triangle, find the minimum path sum from top to bottom. Each*/
/* step you may move to adjacent numbers on the row below.             */
/***********************************************************************/
int minimumTotal(int** triangle, int triangleRowSize,
                 int *triangleColSizes)
{
    int sum = 0, *dp, i;

    /* Allocate DP array */
    dp = malloc(sizeof(int) * triangleRowSize * triangleRowSize);
    for (i = 0; i < triangleRowSize * triangleRowSize; ++i)
        dp[i] = MAX_INT;

    /* Find path, free DP, return sum */
    sum = (triangle[0])[0];
    GetMin(triangle, 1, triangleRowSize, 0, &sum, dp);
    free(dp);
    return sum;
}
#elif RECURSIVE_BOTTOM_UP
/***********************************************************************/
/* Given a triangle, find the minimum path sum from top to bottom. Each*/
/* step you may move to adjacent numbers on the row below.             */
/***********************************************************************/
int minimumTotal(int** tr, int tRow, int *tColSizes)
{
    int j, row = tRow - 2;
    for (j = 0; row >= 0 && j < tColSizes[row]; ++j)
            (tr[row])[j] += (tr[row + 1])[j] > (tr[row + 1])[j + 1] ?
                             (tr[row + 1])[j + 1] : (tr[row + 1])[j];
    /* Stop recursion when rows < 2 */
    return (tRow <= 2) ? **tr : minimumTotal(tr, tRow - 1, tColSizes);
}
#else
/***********************************************************************/
/* Given a triangle, find the minimum path sum from top to bottom. Each*/
/* step you may move to adjacent numbers on the row below.             */
/***********************************************************************/
int minimumTotal(int** tr, int tRow, int *tColSizes)
{
    int j, i;
    /* Loop and select the smaller sums */
    for (i = tRow - 2; i >= 0; --i)
        for (j = 0; j < tColSizes[i]; ++j)
            (tr[i])[j] += (tr[i + 1])[j] > (tr[i + 1])[j + 1] ?
                          (tr[i + 1])[j + 1] : (tr[i + 1])[j];
    return (tr[0])[0];
}
#endif // RECURSIVE

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a0[] = {2}, a1[] = {3,4}, a2[] = {6, 5, 7}, a3[] = {4, 1, 8, 3};
    int *a[] = {a0, a1, a2, a3};
    int rownum = sizeof(a) / sizeof(int *);
    int colsizes[] = {sizeof(a0) / sizeof(int), sizeof(a1) / sizeof(int),
                      sizeof(a2) / sizeof(int), sizeof(a3) / sizeof(int)};
    printf("Min Path = %d", minimumTotal(a, rownum, colsizes));
    return 0;
}
