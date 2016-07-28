/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

void prn_map(int *marr, int m, int n);

/***********************************************************************/
/* A robot is located at the top-left corner of a m x n grid (marked   */
/* 'Start' in the diagram below).                                      */
/* The robot can only move either down or right at any point in time.  */
/* The robot is trying to reach the bottom-right corner of the grid    */
/* (marked 'Finish' in the diagram below).                             */
/*                                                                     */
/* How many possible unique paths are there?                           */
/*                                                                     */
/***********************************************************************/
int uniquePaths(int m, int n)
{
    // m + 1 rows and n + 1 columns
    int *marr = calloc((m + 1) * (n + 1), sizeof(int));
    int ret, i, j;

    /* Trust but verify */
    if (!marr)
        return 0;

    /* Start from the end and grow the unique path counts */
    marr[(m * (n + 1)) + n - 1] = 1;
    for (i = n - 1; i >= 0; --i)
        for (j = m - 1; j >= 0; --j)
            marr[(j * (n + 1)) + i] = marr[((j + 1) * (n + 1)) + i] +
                                      marr[(j * (n + 1)) + i + 1];
    ret = marr[0];
    free(marr);
    return ret;
}

/***********************************************************************/
/* prn_map: Print map!                                                 */
/*                                                                     */
/***********************************************************************/
void prn_map(int *marr, int m, int n)
{
    int i, j;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
            printf("%d, ", marr[(i * n) + j]);
        printf("\n");
    }
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int m[] = {7, 3};
    int n[] = {8, 8};
    int i, len = sizeof(m) / sizeof(int);

    for (i = 0; i < len; ++i)
        printf("[%d, %d] = %d\n", m[i], n[i], uniquePaths(m[i], n[i]));
    return 0;
}
