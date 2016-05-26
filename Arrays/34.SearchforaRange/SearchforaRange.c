/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

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
    int start = 0, end = numsSize - 1, mid;
    int *range;

    /* Sanity */
    if (!nums || !numsSize || !returnSize)
        return NULL;

    /* Allocate the array to be returnd */
    range = malloc(sizeof(int) * 2);
    if (range == NULL)
        return NULL;

    /* Binary search loop */
    while (start <= end)
    {
        /* Get the center of the array and compare */
        mid = start + (end - start) / 2;
        if (nums[mid] == target)
        {
            int s = mid, e = mid;

            /* Seek to the first index location */
            while ((s) && (nums[s - 1] == target))
                s -= 1;
            /* Seek to the last index location */
            while (((e + 1) < numsSize) && (nums[e + 1] == target))
                e += 1;

            /* Set the return size and locations */
            *returnSize = e - s + 1;
            range[0] = s;
            range[1] = e;

            /* Return!!! */
            return range;
        }

        /* Narrow the search window towards the left */
        else if (nums[mid] > target)
            end = mid - 1;

        /* Narrow the search window towards the Right */
        else if (nums[mid] < target)
            start = mid + 1;
    }

    /* Sought but not found */
    *returnSize = 2;
    range[0] = -1;
    range[1] = -1;
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

