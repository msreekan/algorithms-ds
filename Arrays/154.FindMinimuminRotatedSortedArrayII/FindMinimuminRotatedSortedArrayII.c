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
/* The array may contain duplicates.                                   */
/***********************************************************************/
int findMin(int* nums, int numsSize)
{
    int start = 0, end = numsSize - 1, mid;

    /* Loop while the search window is valid */
    while (start < end)
    {
        /* Calculate the center of the array */
        mid = start + (end - start) / 2;

        /* Check for the two cases where we have the pivot. */
        if (mid && nums[mid] < nums[mid - 1])
            return nums[mid];
        else if (mid + 1 < numsSize && nums[mid + 1] < nums[mid])
            return nums[mid + 1];

        /* Else if the center is less than the start or if it's less
        than or equal to the end, then move the window left */
        else if (nums[mid] < nums[start] && nums[mid] <=  nums[end])
            end = mid;

        /* Else if the center is greater than or equal to start and the
        end is less than center, then pivot is to the right */
        else if (nums[mid] >= nums[start] && nums[mid] > nums[end])
            start = mid;

        /* Else revert to sequential scan */
        else
            end--;

    }
    /* Return the start, not a rotated array */
    return nums[0];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //int a[] = {-9,-9,-9,-8,-8,-7,-7,-7,-7,-6,-6,-6,-6,-6,-6,-6,-6,-6,-5,-5,-5,-5,-5,-4,-4,-4,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,0,0,0,1,1,2,2,2,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,7,7,7,7,7,8,9,9,9,10,10,10,10,10,10,10,-10,-9,-9,-9,-9};
    //int a[] = {10,1,10,10,10};
    //int a[] = {10,10,10,1,10};
    int a[] = {1,2,2,2};
    int len = sizeof(a) / sizeof(int);
    printf("Min value %d \n", findMin(a, len));
    return 0;
}
