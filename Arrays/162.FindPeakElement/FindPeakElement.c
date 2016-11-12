/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* A peak element is an element that is greater than its neighbors.    */
/*                                                                     */
/* Given an input array where num[i] ≠ num[i+1], find a peak element   */
/* and return its index.                                               */
/*                                                                     */
/* The array may contain multiple peaks, in that case return the index */
/* to any one of the peaks is fine.                                    */
/*                                                                     */
/* You may imagine that num[-1] = num[n] = -∞.                         */
/*                                                                     */
/* For example, in array [1, 2, 3, 1], 3 is a peak element and your    */
/* function should return the index number 2.                          */
/*                                                                     */
/* Note:                                                               */
/* Your solution should be in logarithmic complexity.                  */
/***********************************************************************/
int findPeakElement(int* nums, int numsSize)
{
    int start = 0, end = numsSize - 1, mid;

    /* Loop while the indices are valid */
    while (start <= end)
    {
        /* Calculate the center */
        mid = start + ((end - start + 1) >> 1);

        /* If we have a peak, then break. */
        if (mid && mid < numsSize - 1 && nums[mid] > nums[mid - 1] &&
            nums[mid] > nums[mid + 1])
            break;

        /* Else move the scan window to the side with the greater
        value. Even in the worst case of a fully increasing sequence
        the last location will be the peak. We want to ALWAYS avoid a
        decreasing sequence. */
        else if (mid && nums[mid] < nums[mid - 1])
            end = mid - 1;
        else
            start = mid + 1;
    }

    /* Return the last visited middle, in the worst case this would be the
    first and last locations in the array. */
    return mid;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    //int a[] = {1, 2, 3,1,3,4,5,0};
    //int a[] = {2,1};
    int a[] = {1,2,3,4,5,2,1};
    int len = sizeof(a) / sizeof(int);
    int index = findPeakElement(a, len);
    printf("Peak index %d and element = %d", index, a[index]);
    return 0;
}
