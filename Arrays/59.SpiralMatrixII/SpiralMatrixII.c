/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* gen_mat: Recursively generate the matrix                            */
/*                                                                     */
/***********************************************************************/
void gen_mat(int **m, int r, int c, int mc, int val)
{
    int i;

    /* End recursion */
    if (r > mc || c > mc)
        return;

    /* Set the first row */
    for (i = c; i <= mc; ++i)
        *(m[r]+ i) = val++;

    /* Set the last column */
    for (i = r + 1; i <= mc; ++i)
        *(m[i] + mc) = val++;

    /* Set the last row */
    for (i = mc - 1; i >= c; --i)
        *(m[mc] + i) = val++;

    /* Set the first column */
    for (i = mc - 1; i > r; --i)
        *(m[i] + c) = val++;

    /* Recursively do the same on the inner sub-matrix */
    gen_mat(m, r + 1, c + 1, mc - 1, val);
}

/***********************************************************************/
/* free_mat: Free the matrix!                                          */
/*                                                                     */
/***********************************************************************/
void free_mat(int **m, int n)
{
    int i;
    for (i = 0; i < n; ++i)
        free(m[i]);
    free(m);
}

/***********************************************************************/
/* Given an integer n, generate a square matrix filled with elements   */
/* from 1 to n2 in spiral order.                                       */
/*                                                                     */
/* For example,                                                        */
/* Given n = 3,                                                        */
/* You should return the following matrix:                             */
/* [                                                                   */
/* [ 1, 2, 3 ],                                                        */
/* [ 8, 9, 4 ],                                                        */
/* [ 7, 6, 5 ]                                                         */
/* ]                                                                   */
/*                                                                     */
/***********************************************************************/
int** generateMatrix(int n)
{
    int **m;
    int i;

    /* Allocate space for rows */
    m = malloc(sizeof(int *) * n);
    if (!m)
        return NULL;

    /* Allocate space for the columns */
    for (i = 0; i < n; ++i)
    {
        m[i] = malloc(sizeof(int) * n);
        if (!m[i])
        {
            free_mat(m, i);
            return NULL;
        }
    }

    /* Generate the matrix */
    gen_mat(m, 0, 0, n - 1, 1);
    return m;
}

/***********************************************************************/
/* prn_mat: Print and free the matrix!                                 */
/*                                                                     */
/***********************************************************************/
void prn_mat(int **m, int n)
{
    int i, j;
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            printf("%d,", *(m[i] + j));
        free(m[i]);
        printf("\n");
    }
    free(m);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n[] = {2, 3, 4};
    int len = sizeof(n) / sizeof(int), i;
    int **m;

    for (i = 0; i < len; ++i)
    {
        m = generateMatrix(n[i]);
        prn_mat(m, n[i]);
        printf("\n\n");
    }
    return 0;
}
