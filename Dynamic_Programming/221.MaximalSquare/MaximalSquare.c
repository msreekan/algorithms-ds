/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***************************************/
/* Macros.                             */
/***************************************/
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : \
                                   ((b) < (c) ? (b) : (c)))

/***********************************************************************/
/* Given a 2D binary matrix filled with 0's and 1's, find the largest  */
/* square containing only 1's and return its area.                     */
/* For example, given the following matrix:                            */
/* 1 0 1 0 0                                                           */
/* 1 0 1 1 1                                                           */
/* 1 1 1 1 1                                                           */
/* 1 0 0 1 0                                                           */
/* Return 4.                                                           */
/***********************************************************************/
int maximalSquare(char** mat, int rsize, int csize)
{
    int i, j, area = 0, min;
    int *arr;

    /* Allocate an integer matrix. */
    arr = malloc(sizeof(int) * rsize * csize);
    if (!arr)
        return -1;

    /* The idea here is to encode the length of the square ending at
    each location. For example, consider these sub-structures:
    a) 1 - square size is 1
    b) 1 1
       1 1
       From these 3 sub-structures 1 1
                                   1
       Fourth one can be derived, all the sourrounding locations need to be
       > 1 for the fourth one to be ending in a square greater than length 1.
       So we pick the smallest length and increment it by one.

       1 1
       1 2
    */

    /* Initialize the DP array. */
    for (i = 0; i < csize; ++i)
        if ((arr[i] = mat[0][i] == '0' ? 0 : 1) > area)
            area = 1;
    for (i = 0; i < rsize; ++i)
        if ((arr[i * csize] = mat[i][0] == '0' ? 0 : 1) > area)
            area = 1;

    /* Generate the length of the square ending at each location. */
    for (i = 1; i < rsize; ++i) {
        for (j = 1; j < csize; ++j)
        {
            min = MIN3(arr[i * csize + j - 1], arr[(i - 1) * csize + j],
                       arr[(i - 1) * csize + j - 1]);
            arr[i * csize + j] = (((mat[i])[j] == '1') && min > 0) ?
                                  min + 1 : (mat[i])[j] == '1' ? 1 : 0;
        }
    }

    /* Get the maximum area. */
    for (i = 1; i < rsize; ++i)
        for (j = 1; j < csize; ++j)
            if (area < arr[i * csize + j] * arr[i * csize + j])
                area = arr[i * csize + j] * arr[i * csize + j];

    /* Return the area. */
    free(arr);
    return area;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s1[] = {'1', '0', '1', '0', '0'}, s2[] = {'1', '0', '1', '1', '1'};
    char s3[] = {'1', '1', '1', '1', '1'}, s4[] = {'1', '0', '0', '1', '0'};
    char *s[] = {s1, s2, s3, s4};
    int r = sizeof(s) / sizeof(char *), c = sizeof(s1);
    printf("Maximal Square = %d:\n", maximalSquare(s, r, c));
    return 0;
}
