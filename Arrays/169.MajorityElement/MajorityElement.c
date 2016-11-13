/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of size n, find the majority element. The majority   */
/* element is the element that appears more than ⌊ n/2 ⌋ times.        */
/* You may assume that the array is non-empty and the majority element */
/* always exist in the array.                                          */
/***********************************************************************/
int majorityElement(int* nums, int numsSize)
{
    int i, count = 1, mval = nums[0];

    /* Scan the array looking for the majority element. The array has a
    property where one element occurs more than the rest. So, we can
    take advantage of this property and simply scan the array assigning
    weight for each occurrence of a value, eventually the majority
    element wins. */
    for (i = 1; i < numsSize && count <= numsSize - i; ++i)
    {
        /* Decrement the weight for each mismatch, otherwise
        increment */
        count = (nums[i] != mval) ? count - 1 : count + 1;

        /* If the weight is zero, then switch majority element */
        if (!count){
            mval = nums[i];
            count = 1;
        }
    }

    /* Return the majority element */
    return mval;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1,2,3,1,1};
    int len = sizeof(a) / sizeof(int);
    printf("Majority Element = %d \n", majorityElement(a, len));
    return 0;
}
