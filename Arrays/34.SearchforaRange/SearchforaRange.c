/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* BinSearch: Binary search for a value                                */
/*                                                                     */
/***********************************************************************/
int BinSearch(int *arr, int start, int end, int target)
{
    int s = start, e = end, mid;

    /* Loop while start <= end */
    while (s <= e)
    {
        /* If we have a hit, then return */
        mid = (s + (e - s) / 2);
        if (arr[mid] == target)
            return mid;

        /* If the target is smaller, then shift the end */
        if (arr[mid] > target)
            e = mid - 1;
        /* Else shift the start */
        else
            s = mid + 1;
    }

    /* Return failure */
    return -1;
}

/***********************************************************************/
/* Given a sorted array of integers, find the starting and ending      */
/* position of a given target value.                                   */
/* Your algorithm's runtime complexity must be in the order of         */
/* O(log n).                                                           */
/* If the target is not found in the array, return [-1, -1].           */
/* For example,                                                        */
/* Given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].        */
/*                                                                     */
/***********************************************************************/
int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int *range = malloc(sizeof(int) * 2);

    /* Sanity */
    if (!nums || !numsSize || !returnSize || !range)
        return NULL;
    *returnSize = 2;
    range[0] = range[1] = -1;

    /* Search for target. If it's not found, then return. */
    if ((range[1] = range[0] = BinSearch(nums, 0, numsSize - 1, target)) < 0)
        return range;

    /* Seek to the end of the range */
    while (range[1] < numsSize - 1 && nums[range[1] + 1] == target)
        ++range[1];

    /* Seek to the beginning range */
    while (range[0] > 0 && nums[range[0] - 1] == target)
        --range[0];

    /* Return */
    return range;
}


/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1}, len = sizeof(a) / sizeof(int), rsize = 0, i;
    int *r = NULL;

    r = searchRange(a, len, 0, &rsize);
    for (i = 0; i < rsize; ++i)
        printf("%d ", r[i]);
    free(r);

    return 0;
}
