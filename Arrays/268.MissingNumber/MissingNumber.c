/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#if O_N2
/***********************************************************************/
/* Given an array containing n distinct numbers taken from 0, 1, 2,..n,*/
/* find the one that is missing from the array.                        */
/* For example,                                                        */
/* Given nums = [0, 1, 3] return 2.                                    */
/* Note:                                                               */
/* Your algorithm should run in linear runtime complexity. Could you   */
/* implement it using only constant extra space complexity?            */
/***********************************************************************/
int missingNumber(int* nums, int numsSize)
{
    int i;

    /* Loop swapping out of place elements. Repeat this until all the
    elements are in place. */
    for (i = 0; i < numsSize; ++i) {
        while (nums[i] < numsSize && nums[i] != i)
        {
            int t  = nums[i];
            nums[i] = nums[t];
            nums[t] = t;
        }
    }

    /* Now look for the out of place element. */
    for (i = 0; i < numsSize; ++i)
        if (nums[i] != i)
            return i;
    /* Else return the last value. */
    return numsSize;
}
#else
/***********************************************************************/
/* Given an array containing n distinct numbers taken from 0, 1, 2,..n,*/
/* find the one that is missing from the array.                        */
/* For example,                                                        */
/* Given nums = [0, 1, 3] return 2.                                    */
/* Note:                                                               */
/* Your algorithm should run in linear runtime complexity. Could you   */
/* implement it using only constant extra space complexity?            */
/***********************************************************************/
int missingNumber(int* nums, int numsSize)
{
    int i, x = numsSize;

    /* Keep XoRing the values. */
    for (i = 0; i < numsSize; ++i)
        x ^= (i ^ nums[i]);

    /* Return the result. */
    return x;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {3, 2, 0};
    int len = sizeof(a) / sizeof(int);
    printf("Missing number = %d :\n", missingNumber(a, len));
    return 0;
}
