/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a sorted array and a target value, return the index if the    */
/* target is found. If not, return the index where it would be if it   */
/* were inserted in order.                                             */
/*                                                                     */
/* You may assume no duplicates in the array.                          */
/* Here are few examples.                                              */
/* [1,3,5,6], 5 ? 2                                                    */
/* [1,3,5,6], 2 ? 1                                                    */
/* [1,3,5,6], 7 ? 4                                                    */
/* [1,3,5,6], 0 ? 0                                                    */
/*                                                                     */
/***********************************************************************/
int searchInsert(int *nums, int numsSize, int target)
{
    int *a = nums;
    int start = 0, end = numsSize - 1;
    int mid = 0;

    /* Handle the case where the target is outside the array range. */
    if (target < nums[0])
        return 0;
    if (target > nums[numsSize - 1])
        return numsSize;

    /* Binary search */
    while (start <= end)
    {
        /* Get to the center */
        mid = start + ((end - start + 1) / 2);

        /* Target found */
        if (a[mid] == target)
            return mid;

        /* Narrow the search window based on the target size */
        if (a[mid] < target)
            start = mid + 1;
        else
            end = mid - 1;
    }

    /* Return the location where the the target will be inserted */
    return start;
}

/***********************************************************************/
/* binary_search: Binary search                                        */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 3, 5, 6};
    int len = sizeof(a) / sizeof(int);
    printf("Position = %d:\n", searchInsert(a, len, 0));
    return 0;
}

