/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***************************************************************************/
/* https://leetcode.com/problems/range-sum-query-2d-immutable/#/description*/
/***************************************************************************/
typedef struct
{
    int **mat;
} NumMatrix;

/***********************************************************************/
/* numMatrixCreate: Create the matrix!                                 */
/*                                                                     */
/***********************************************************************/
NumMatrix* numMatrixCreate(int** cmat, int rsz, int csz)
{
    NumMatrix *n;
    int i, j;
    int *arr;
    int **mat;

    /* Validate the parameters. */
    if (!cmat || rsz < 1 || csz < 0)
        return NULL;

    /* Allocate space. */
    n = malloc(sizeof(NumMatrix) + (sizeof(int *) * (rsz + 1)) +
               (sizeof(int) * (rsz + 1) * (csz + 1)));
    if (!n) return NULL;

    /* Initialize the structure. */
    mat = n->mat = (int **)&n[1];
    arr = (int *)&n->mat[rsz + 1];

    /* Set the matrix. */
    for (i = 0; i <= rsz; ++i)
        mat[i] = &arr[i * (csz + 1)];

    /* Set the first row and column to zeroes. */
    for (i = 0; i <= csz; ++i)
        (mat[0])[i] = 0;
    for (i = 1; i <= rsz; ++i)
        (mat[i])[0] = 0;

    /* Generate the matrix. The idea behind this algorithm is similar
    to the one about finding largest square within a matrix of 0s and 1s.
    The same dynamic programming sub-structure determining squares can be
    utilized here also. At every cell we record the size of the rectangle
    ending there. This way we can derive any rectangle size. */
    for (i = 1; i <= rsz; ++i)
        for (j = 1; j <= csz; ++j)
            (mat[i])[j] = (cmat[i - 1])[j - 1] + (mat[i - 1])[j] +
                          (mat[i])[j - 1] - (mat[i - 1])[j - 1];
    /* Return the handle. */
    return n;
}

/***********************************************************************/
/* numMatrixSumRegion: Sum the region!                                 */
/*                                                                     */
/***********************************************************************/
int numMatrixSumRegion(NumMatrix* obj, int r1, int c1, int r2, int c2)
{
    int **mat = obj->mat;
    int tr1 = r1 + 1, tr2 = r2 + 1, tc1 = c1 + 1, tc2 = c2 + 1;

    /*
     1. Get the size of the rectangle ending at [r2, c2],
     2. Subtract the rectangle at [r1 - 1, c2 - 1] and [r2 - 1, c1 - 1].
     3. Now add the rectangle at [r1 - 1, c1 - 1] to compensate for
        double subtraction done above.
    */
    return (mat[tr2])[tc2] - (mat[tr1 - 1])[tc2] - (mat[tr2])[tc1 - 1] +
           (mat[tr1 - 1])[tc1 - 1];
}

/***********************************************************************/
/* numMatrixFree: Live free!                                           */
/*                                                                     */
/***********************************************************************/
void numMatrixFree(NumMatrix* obj)
{
    free(obj);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
