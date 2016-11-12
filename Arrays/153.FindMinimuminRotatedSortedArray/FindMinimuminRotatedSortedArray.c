/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Suppose a sorted array is rotated at some pivot unknown to you      */
/* beforehand.                                                         */
/*                                                                     */
/* (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).                   */
/*                                                                     */
/* Find the minimum element.                                           */
/*                                                                     */
/* You may assume no duplicate exists in the array.                    */
/***********************************************************************/
int findMin(int* nums, int numsSize)
{
    int start = 0, end = numsSize - 1, mid;

    /* Do a binary search to find the pivot */
    while (start <= end) {
        /* Find the center */
        mid = start + (end - start) / 2;

        /* If this is the pivot, then return the offset */
        if (mid && nums[mid] < nums[mid - 1])
            return nums[mid];

        /* Else if the next element is the pivot, then return the value*/
        else if (mid + 1 < numsSize && nums[mid + 1] < nums[mid])
            return nums[mid + 1];

        /* If the center is greater than start, then move window to
        the right */
        else if (nums[mid] >= nums[start])
            start = mid + 1;
        /* Else move the window to the left */
        else
            end = mid;
    }

    /* Pivot at the start */
    return nums[0];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2,1,2,2,2};
    int len = sizeof(a) / sizeof(int);
    printf("Min value %d \n", findMin(a, len));
    return 0;
}
