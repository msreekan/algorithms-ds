/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if O_NLOGN
/***********************************************************************/
/* bsearch: Binary search!                                             */
/*                                                                     */
/***********************************************************************/
int binsearch(int *arr, int start, int end, int t)
{
    int mid;

    /* Loop seeking the element. */
    while (start <= end)
    {
        /* If we have a hit, then return. */
        mid = start + (end - start + 1) / 2;
        if (arr[mid] == t)
            return mid;
        /* Else if the value is to the left, then search first half. */
        else if (arr[mid] > t)
            end = mid - 1;
        /* Else search the second half. */
        else
            start = mid + 1;
    }

    /* Not found. */
    return mid;
}

/***********************************************************************/
/* Write an efficient algorithm that searches for a value in an m x n  */
/* matrix. This matrix has the following properties:                   */
/* Integers in each row are sorted in ascending from left to right.    */
/* Integers in each column are sorted in ascending from top to bottom. */
/*                                                                     */
/***********************************************************************/
bool searchMatrix(int** mat, int rsz, int csz, int target)
{
    int i, loc = csz / 2, start = 0, end = csz - 1;
    bool ret = false;

    /* Validate the parameters. */
    if (!mat || rsz <= 0 || csz <= 0)
        return false;

    /* Loop seeking the value in all the arrays. */
    for (i = 0; i < rsz && ret == false; ++i)
    {
        /* Run the binary search. */
        loc = binsearch(mat[i], start, end, target);
        if ((mat[i])[loc] == target)
            ret = true;
    }

    /* Return the status. */
    return  ret;
}
#else
/***********************************************************************/
/* Write an efficient algorithm that searches for a value in an m x n  */
/* matrix. This matrix has the following properties:                   */
/* Integers in each row are sorted in ascending from left to right.    */
/* Integers in each column are sorted in ascending from top to bottom. */
/*                                                                     */
/***********************************************************************/
bool searchMatrix(int** mat, int rsz, int csz, int target)
{
    int row = rsz - 1, col = 0;

    /* Loop seeking the value in all the arrays. */
    while (row >= 0 && (mat[row])[col] != target)
        if ((mat[row])[col] < target && col < csz)
            col++;
        else
            row--;

    /* Return the status. */
    return  (col < csz && row >= 0 && (mat[row])[col] == target) ?
            true : false;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 1
    int a1[] = {1,   4,  7, 11, 15, 20}, a2[] = {2,   5,  8, 12, 19, 30};
    int a3[] = {3,   6,  9, 16, 22, 40}, a4[] = {10, 13, 14, 17, 24, 50};
    int a5[] = {18, 21, 23, 26, 30, 60};
    int *a[] = {a1, a2, a3, a4, a5};
    int t = 90;
    #elif 0
    int a1[] = {1, 1};
    int *a[] = {a1};
    int t = 0;
    #elif 1
    int a1[] = {-5};
    int *a[] = {a1};
    int t = -5;
    #endif
    int rsz = sizeof(a) / sizeof(int *);
    int csz = sizeof(a1) / sizeof(int);

    printf("Search = %d: \n", searchMatrix(a, rsz, csz, t));
    return 0;
}
