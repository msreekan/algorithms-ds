/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of numbers nums, in which exactly two elements appear*/
/* only once and all the other elements appear exactly twice. Find the */
/* two elements that appear only once.                                 */
/* For example:                                                        */
/* Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].                     */
/* Note:                                                               */
/* The order of the result is not important. So in the above example,  */
/* [5, 3] is also correct.                                             */
/* Your algorithm should run in linear runtime complexity. Could you   */
/* implement it using only constant space complexity?                  */
/***********************************************************************/
int* singleNumber(int* nums, int numsSize, int* returnSize)
{
    int x1, i;
    int *arr;

    /* Validate the parameters. */
    if (!nums || numsSize <= 0 || !returnSize)
        return NULL;

    /* Allocate the return array. */
    arr = calloc(2, sizeof(int));
    if (!arr)
        return NULL;
    *returnSize = 0;

    /* Xor loop. */
    x1 = 0;
    for (i = 0; i < numsSize; ++i)
        x1 ^= nums[i];

    /* Now separate the numbers based on the bits set within x1.
    The bits set in x1 helps us differentiate the two numbers without
    duplicates. */
    x1 = x1 & ~(x1 - 1);
    for (i = 0; i < numsSize; ++i)
    {
        if (x1 & nums[i])
            arr[0] ^= nums[i];
        else
            arr[1] ^= nums[i];
    }

    /* Return the array. */
    *returnSize = 2;
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2, 1, 2, 3, 4, 1};
    int len = sizeof(a) / sizeof(int), ret, i;
    int *arr;
    /* Get the numbers. */
    arr = singleNumber(a, len, &ret);
    for (i = 0; i < ret; ++i)
        printf("%d ",arr[i]);
    free(arr);
    return 0;
}
