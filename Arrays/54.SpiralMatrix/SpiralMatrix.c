/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* spiral_architect: Recursively unravel                               */
/*                                                                     */
/***********************************************************************/
void spiral_architect(int** matrix, int r, int c, int mr, int mc, int *a)
{
    int i;

    /* End recursion */
    if (c > mc || r > mr)
        return;

    for (i = c; i <= mc; ++i, ++a) // Extract first row
        *a = *(matrix[r] + i);

    for (i = r + 1; i <= mr; ++i, ++a) // Extract last column
        *a = *(matrix[i] + mc);

    for (i = mc - 1; i >= c && r < mr; --i, ++a) // Last row
        *a = *(matrix[mr] + i);

    for (i = mr - 1; i > r && c < mc; --i, ++a) // And then 1st column
        *a = *(matrix[i] + c);

    /* Turn to the inner sub-matrix */
    spiral_architect(matrix, r + 1, c + 1, mr - 1, mc - 1, a);
}

/***********************************************************************/
/* Given a matrix of m x n elements (m rows, n columns), return all    */
/* elements of the matrix in spiral order.                             */
/*                                                                     */
/***********************************************************************/
int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize)
{
    int *a;
    int r = matrixRowSize, c = matrixColSize;

    /* Allocate space for array */
    a = malloc(sizeof(int) * r * c);
    if (!a)
        return NULL;
    /* Call the matrix unraveling  function */
    spiral_architect(matrix, 0, 0, r - 1, c - 1, a);
    return a;
}

/***********************************************************************/
/* prn_array: Print arrays                                             */
/*                                                                     */
/***********************************************************************/
void prn_array(int *a, int num)
{
    int i;
    for (i = 0; i < num; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int m1[] = {1, 2, 3}, m2[] = {4, 5, 6}, m3[] = {7, 8, 9};
    int *m[] = {m1, m2, m3};
    int c = sizeof(m1) / sizeof(int), r = sizeof(m) / sizeof(int *);
    int *a;
    a = spiralOrder(m, r, c);
    prn_array(a, r * c);
    free(a);
    return 0;
}
