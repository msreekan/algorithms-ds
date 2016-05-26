/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* swap_int: Swap pointer values                                       */
/*                                                                     */
/***********************************************************************/
void swap_int(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

/***********************************************************************/
/* Given an unsorted integer array, find the first missing positive    */
/* integer.                                                            */
/*                                                                     */
/* For example,                                                        */
/* Given [1,2,0] return 3,                                             */
/* and [3,4,-1,1] return 2.                                            */
/*                                                                     */
/* Your algorithm should run in O(n) time and uses constant space.     */
/***********************************************************************/
int firstMissingPositive(int* nums, int numsSize)
{
    int i = 0;

    /* Scan the array relocating elements within the range */
    while (i < numsSize)
    {
        /* Avoid swapping values if the element is outside the range :
          ie: negative or beyond array size. Or if it's already in place
          or if the destination already has the same value.  */
        if ((nums[i] == (i + 1)) || (nums[i] <= 0) ||
            (nums[i] >= numsSize) || (nums[i] == nums[nums[i] - 1]))
            ++i;

        /* SWAP */
        else
            swap_int(&nums[i], &nums[nums[i] - 1]);
    }

    /* Now run through the list, the first location with an out of place
    value provides the answer */
    for (i = 0; i < numsSize; ++i)
        if (nums[i] != i + 1)
            return i + 1;

    /* Return */
    return numsSize + 1;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 1};
    int len = sizeof(a) / sizeof(int);
    printf("First missing = %d :\n", firstMissingPositive(a, len));
    return 0;
}

