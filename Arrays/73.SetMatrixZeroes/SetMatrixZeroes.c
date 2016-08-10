/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a m x n matrix, if an element is 0, set its entire row and    */
/* column to 0. Do it in place.                                        */
/*                                                                     */
/***********************************************************************/
void setZeroes(int** matrix, int matrixRowSize, int matrixColSize)
{
    int i, j, r0 = 0, c0 = 0;

    /* Record any instance of zero on the first row */
    for (j = 0; j < matrixColSize && !r0; ++j)
        if (*(matrix[0] + j) == 0)
            r0 = 1;

    /* Record any instance of zero on the column */
    for (j = 0; j < matrixRowSize && !c0; ++j)
        if (*(matrix[j] + 0) == 0)
            c0 = 1;

    /* Encode presence of zeros within the first row/column */
    for (i = 1; i < matrixRowSize; ++i)
        for (j = 1; j < matrixColSize; ++j)
            if (*(matrix[i] + j) == 0)
                *(matrix[0] + j) = *(matrix[i] + 0) = 0;

    /* Seek and reset rows if the column entry is zero */
    for (i = 1; i < matrixRowSize; ++i)
        if (*(matrix[i] + 0) == 0)
            for (j = 1; j < matrixColSize; ++j)
                *(matrix[i] + j) = 0;

    /* Seek and reset columns if the row entry is zero */
    for (i = 0; i < matrixColSize; ++i)
        if (*(matrix[0] + i) == 0)
            for (j = 1; j < matrixRowSize; ++j)
                *(matrix[j] + i) = 0;

    /* If needed, reset first row and column to zero */
    for (j = 0; j < matrixColSize && r0; ++j)
        *(matrix[0] + j) = 0;
    for (j = 0; j < matrixRowSize && c0; ++j)
        *(matrix[j] + 0) = 0;
}

/***********************************************************************/
/* prn_mat: Print matrix                                               */
/*                                                                     */
/***********************************************************************/
void prn_mat(int **a, int r, int c)
{
    int i, j;
    for (i = 0; i < r; ++i, printf("\n"))
        for (j = 0; j < c; ++j)
            printf("%d, ", *(a[i] + j));
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[] = { 1, 2, 3, 4}, a2[] = {3, 2, 1, 5}, a3[] = {5, 0, 0, 1};
    int *a[] = {a1, a2, a3};
    prn_mat(a, sizeof(a) / sizeof(int *), sizeof(a1) / sizeof(int));
    setZeroes(a, sizeof(a) / sizeof(int *), sizeof(a1) / sizeof(int));
    prn_mat(a, sizeof(a) / sizeof(int *), sizeof(a1) / sizeof(int));
    return 0;
}
