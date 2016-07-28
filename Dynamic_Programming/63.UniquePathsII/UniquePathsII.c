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
/* Now consider if some obstacles are added to the grids. How many     */
/* unique paths would there be?                                        */
/*                                                                     */
/* An obstacle and empty space is marked as 1 and 0 respectively in    */
/* the grid.                                                           */
/*                                                                     */
/* For example, there is one obstacle in the middle of a 3x3 grid as   */
/* illustrated below.                                                  */
/*                                                                     */
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize,
                             int obstacleGridColSize)
{
    int m = obstacleGridRowSize, n = obstacleGridColSize;
    int **omap = obstacleGrid;

    // m + 1 rows and n + 1 columns!
    int *marr = calloc((m + 1) * (n + 1), sizeof(int));
    int ret, i, j;

    /* Calloc : Trust but verify */
    if (!marr) return 0;

    marr[(m * (n + 1)) + n - 1] = 1; // initialize the last location

    /* Update the array with unique path count only if the input array
    location is 0 */
    for (i = n - 1; i >= 0; --i)
        for (j = m - 1; j >= 0; --j)
            marr[(j * (n + 1)) + i] = (*(omap[j] + i) == 0) ?
            marr[((j + 1) * (n + 1)) + i] + marr[(j * (n + 1)) + i + 1] : 0;
    ret = marr[0];
    free(marr);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    /* NO Test cases */
    return 0;
}
