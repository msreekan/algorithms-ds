/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* The gray code is a binary numeral system where two successive values*/
/* differ in only one bit.                                             */
/*                                                                     */
/* Given a non-negative integer n representing the total number of bits*/
/* in the code, print the sequence of gray code. A gray code sequence  */
/* must begin with 0.                                                  */
/*                                                                     */
/* For example, given n = 2, return [0,1,3,2]. Its gray code sequence  */
/* is:                                                                 */
/* 00 - 0                                                              */
/* 01 - 1                                                              */
/* 11 - 3                                                              */
/* 10 - 2                                                              */
/*                                                                     */
/* Note: For a given n, a gray code sequence is not uniquely defined.  */
/*                                                                     */
/* For example, [0,2,3,1] is also a valid gray code sequence according */
/* to the above definition.                                            */
/***********************************************************************/
int* grayCode(int n, int* returnSize)
{
    int i, j = 1, code = 0, mask = 2;
    int *arr;

    /* Calculate the power of 2 */
    *returnSize = 1;
    for (i = 0; i < n; ++i)
        (*returnSize) *= 2;

    /* Allocate the array */
    arr = malloc(sizeof(int) * (*returnSize));
    if (!arr)
        return NULL;

    /* Assign the first two numbers */
    arr[0] = code;
    if (n > 0)
        arr[1] = code + 1;

    /* Generate rest of the array:
        Pattern formula : arr[i] = mask | arr[i - j]
        Explanation :
        0    << Initialized
        1    <<    ''
        11   << mask = 2, i = 2, j = 1
        10   << mask = 2, i = 3, j = 3
        110  << mask <<= 1, mask = 4, i = 4, j = 1
        111  << mask = 4, i = 5, j = 3
        101  << mask = 4, i = 6, j = 5
        100  << mask = 4, i = 7, j = 7
        1100 << mask <<= 1, mask = 8, i = 8, j = 1
        ................
        ...............
        .....
    */
    for (i = 2; i < *returnSize; ++i, j += 2)
    {
        /* Power of two, so reset the index, change the mask,
           and then assign the value. */
        j = ((i & ~(mask - 1)) > mask) ? 1 : j;
        mask = ((i & ~(mask - 1)) > mask) ? mask << 1 : mask;
        arr[i] = mask | arr[i - j];
    }

    /* Return the array */
    return arr;
}

/***********************************************************************/
/* prn_arr: Print array!                                               */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *arr, int len)
{
    int i;
    for (i = 0; i < len - 1; ++i)
        printf("%d, ", arr[i]);
    printf("%d\n", arr[i]);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int *arr;
    int ret;
    arr = grayCode(4, &ret);
    if (arr)
        prn_arr(arr, ret);
    free(arr);
    return 0;
}
