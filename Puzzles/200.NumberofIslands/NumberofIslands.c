/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* IslandTraverse: Traverse an island!                                 */
/*                                                                     */
/***********************************************************************/
void IslandTraverse(char **grid, int rows, int cols, int r, int c)
{
    /* If the index is out of range, then return. */
    if (r < 0 || c < 0 || r >= rows || c >= cols)
        return;

    /* If the value is '1', then reset and continue traversal. */
    if ((grid[r])[c] == '1') {
        (grid[r])[c] = '2'; // reset
        IslandTraverse(grid, rows, cols, r + 1, c);
        IslandTraverse(grid, rows, cols, r - 1, c);
        IslandTraverse(grid, rows, cols, r, c + 1);
        IslandTraverse(grid, rows, cols, r, c - 1);
    }
}

/***********************************************************************/
/* Given a 2d grid map of '1's (land) and '0's (water), count the      */
/* number of islands. An island is surrounded by water and is formed by*/
/* connecting adjacent lands horizontally or vertically. You may assume*/
/* all four edges of the grid are all surrounded by water.             */
/***********************************************************************/
int numIslands(char** grid, int rows, int cols)
{
    int count = 0, i, j;

    /* Seek starting of islands */
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j)
            /* If start of an island is found, then traverse. */
            if ((grid[i])[j] == '1') {
                IslandTraverse(grid, rows, cols, i, j);
                count++;
            }

    /* Return the count */
    return count;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s1[] = "11110", s2[] = "11010", s3[] = "11000";
    char s4[] = "00000";
    char *s[] = {s1, s2, s3, s4};
    int i, rows = sizeof(s) / sizeof(char *), cols = sizeof(s1);

    /* Print the grid */
    for (i = 0; i < rows; ++i)
        printf("%s \n", s[i]);

    printf("Number of Islands = %d \n", numIslands(s, rows, cols));
    return 0;
}
