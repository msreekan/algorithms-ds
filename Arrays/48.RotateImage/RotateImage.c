/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* swap_int: Swap integers                                             */
/*                                                                     */
/***********************************************************************/
void swap_int(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

/***********************************************************************/
/* rr: Recursive rotation.                                             */
/*                                                                     */
/***********************************************************************/
void rr(int** m, int r, int n)
{
    int j;

    /* End recursion */
    if (r >= n)
        return;

    /* Rotate all the elements in the row */
    for (j = r; j < n; ++j)
    {
        swap_int(m[r] + j, m[j] + n);
        swap_int(m[r] + j, m[n] + n - (j - r));
        swap_int(m[r] + j, m[n - (j - r)] + r);
    }

    /* Advance to the inner n-1 x n-1 sub-matrix */
    return rr(m, r + 1, n - 1);
}

/***********************************************************************/
/* You are given an n x n 2D matrix representing an image.             */
/* Rotate the image by 90 degrees (clockwise).                         */
/* Follow up:                                                          */
/* Could you do this in-place?                                         */
/***********************************************************************/
void rotate(int** matrix, int matrixRowSize, int matrixColSize)
{
    /*Maintain Sanity */
    if (!matrix || !matrixRowSize || (matrixRowSize != matrixColSize))
        return matrix;
    return rr(matrix, 0, matrixColSize - 1);
}

/***********************************************************************/
/* prn_matrix: Print the matrix.                                       */
/*                                                                     */
/***********************************************************************/
void prn_matrix(int **m, int rc)
{
    int i, j;
    for (i = 0; i < rc; ++i)
    {
        for (j = 0; j < rc; ++j)
            printf("%d, ", *(m[i] + j));
        printf("\n");
    }
    printf("\n\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[] = {11, 12, 13, 14};
    int a2[] = {21, 22, 23, 24};
    int a3[] = {31, 32, 33, 34};
    int a4[] = {41, 42, 43, 44};
    int *a[] = {a1, a2, a3, a4};
    int len = sizeof(a) / sizeof(int *);

    printf("Original Matrix \n");
    prn_matrix(a, len);

    rotate(a, len, len);

    printf("Rotated Matrix :\n");
    prn_matrix(a, len);
    return 0;
}
