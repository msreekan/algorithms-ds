/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

/*****************************************/
/* Macros                                */
/*****************************************/
#define INT_MAX 0x7FFFFFFF

/***********************************************************************/
/* Given an array of n positive integers and a positive integer s, find*/
/* the minimal length of a contiguous subarray of which the sum ≥ s. If*/
/* there isn't one, return 0 instead.                                  */
/* For example, given the array [2,3,1,2,4,3] and s = 7,               */
/* the subarray [4,3] has the minimal length under the problem         */
/* constraint.                                                         */
/***********************************************************************/
int minSubArrayLen(int s, int* nums, int numsSize)
{
    int start = 0, end = 0, sum = 0, min = INT_MAX;

    while (end < numsSize)
    {
        /* Move the end pointer till it reaches sum. */
        for (;end < numsSize && sum < s; end++)
            sum += nums[end];
        /* Move the start pointer till it end or as long as the sum is
        greater than s. */
        for (;start < end && sum >= s; start++)
        {
            /* Update the minimum length and then the sum. */
            min = min > (end - start) ? (end - start) : min;
            sum -= nums[start];
        }
    }

    /* Return the minimum. */
    return min != INT_MAX ? min : 0;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {2, 3, 1, 2, 4, 3}, sum = 100;
    int len = sizeof(arr) / sizeof(int);

    printf("Array:\n");
    PrintArray(arr, len);
    printf("\n");

    printf("Shortest Sub-array len = %d:\n", minSubArrayLen(sum, arr, len));
    return 0;
}
