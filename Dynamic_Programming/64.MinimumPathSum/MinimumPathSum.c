/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a m x n grid filled with non-negative numbers, find a path    */
/* from top left to bottom right which minimizes the sum of all numbers*/
/* along its path.                                                     */
/*                                                                     */
/***********************************************************************/
int minPathSum(int** grid, int gridRowSize, int gridColSize)
{
    int i, j, m = gridRowSize, n = gridColSize;

    /* Set the cost for the last column */
    for (i = n - 1, j = m - 2; j >= 0; --j)
        (*(grid[j] + i)) += *(grid[j + 1] + i);

    /* Find the cost for the inner sub-matrix */
    for (i = n - 2; i >= 0; --i)
    {
        /* Set the last column cost */
        (*(grid[m - 1] + i)) +=  *(grid[m - 1] + i + 1);

        /* Run through the column picking the smaller cost */
        for (j = m - 2; j >= 0; --j)
        (*(grid[j] + i)) += (*(grid[j + 1] + i) > *(grid[j] + i + 1) ?
                            *(grid[j] + i + 1) : *(grid[j + 1] + i));
    }

    /* Return the identified minimum cost */
    return *grid[0];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    /* No test cases */
    return 0;
}
