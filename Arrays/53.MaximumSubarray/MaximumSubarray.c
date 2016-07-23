/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Find the contiguous subarray within an array (containing at least   */
/* one number) which has the largest sum.                              */
/*                                                                     */
/* For example, given the array [−2,1,−3,4,−1,2,1,−5,4],               */
/* the contiguous subarray [4,−1,2,1] has the largest sum = 6.         */
/*                                                                     */
/***********************************************************************/
int maxSubArray(int* nums, int numsSize)
{
    int max_here, max_total, i;
    int *arr = nums;

    /* Maintain sanity */
    if (!nums || !numsSize)
        return 0;

    /* Implement Kadane's algorithm */
    max_here = nums[0];
    max_total = max_here;
    for (i = 1; i < numsSize; ++i)
    {
        max_here = (max_here + arr[i]) > arr[i] ? (max_here + arr[i]) : arr[i];
        max_total = max_here > max_total ? max_here : max_total;
    }

    /* Return */
    return max_total;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4, 4, 5, -10, -2, 1, -3, 4, -1, 2, 1, -5, 4, 4, 5, -10, -2, 1, -3, 4, -1, 2, 1, -5, 4, 4, 5, -10, -2, 1, -3, 4, -1, 2, 1, -5, 4, 4, 5, -10};
    int len = sizeof(arr) / sizeof(int);
    printf("Kadane: Max_total = %d", maxSubArray(arr, len));
    return 0;
}
