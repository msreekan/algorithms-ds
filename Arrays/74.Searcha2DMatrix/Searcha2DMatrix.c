/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ROW 4
#define COL 4

/***********************************************************************/
/* Write an efficient algorithm that searches for a value in an m x n  */
/* matrix. This matrix has the following properties:                   */
/*                                                                     */
/* Integers in each row are sorted from left to right.                 */
/* The first integer of each row is greater than the last integer of   */
/* the previous row. For example,                                      */
/* Consider the following matrix:                                      */
/* [                                                                   */
/* [1,   3,  5,  7],                                                   */
/* [10, 11, 16, 20],                                                   */
/* [23, 30, 34, 50]                                                    */
/* ]                                                                   */
/*                                                                     */
/***********************************************************************/
int searchMatrix(int** matrix, int matrixRowSize, int matrixColSize,
                 int target)
{
    int start = 0, end = (matrixRowSize * matrixColSize) - 1, mid;

    /* Ensure the search is required */
    if (!matrix || !(matrixRowSize * matrixColSize) ||
        (target < matrix[0][0]) || (target > matrix[matrixRowSize - 1][matrixColSize - 1]))
        return 0;

    /* Binary search on a 2D array */
    while (start <= end)
    {
        int col, row;

        /* Calculate the center */
        mid = start + ((end - start) / 2);

        /* Transform into columns and rows */
        col = mid % matrixColSize;
        row = mid / matrixColSize;

        /* Hit! */
        if (matrix[row][col] == target)
            return 1;

        /* Adjust the search window */
        if (matrix[row][col] > target)
            end = mid - 1;
        else
            start = mid + 1;
    }

    /* Not found */
    return 0;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[COL] = {1, 2, 3, 4};
    int a2[COL] = {11, 12, 13, 14};
    int a3[COL] = {21, 22, 23, 24};
    int a4[COL] = {31, 32, 33, 34};
    int *a[ROW] = {a1, a2, a3, a4};

    printf("Matrix Search = %d :\n", searchMatrix((int **)a, ROW, COL, 1));
    return 0;
}

