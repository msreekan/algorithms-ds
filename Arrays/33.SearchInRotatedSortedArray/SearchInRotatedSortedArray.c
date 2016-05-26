/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* binary_search_pivot: Get the location where array is rotated        */
/*                                                                     */
/***********************************************************************/
int binary_search_pivot(int *arr, int len)
{
    int end = len - 1, start = 0, mid;

    /* Narrow down on the pivot by scanning the array from both the
    ends */
    while (end >= start)
    {
        /* Get the center */
        mid = start +  (end - start) / 2;

        /* If we have the pivot, then return the same */
        if (((mid + 1) <= end) && (arr[mid] > arr[mid + 1]))
            return mid + 1;
        if ((mid) && (arr[mid] < arr[mid - 1]))
            return mid;

        /* Pivot is to the left */
        if ((arr[mid] <= arr[start]) || (arr[end] >= arr[mid]))
            end = mid - 1;

        /* Else pivot is to the right */
        else if ((arr[end] < arr[mid]) || (arr[mid] >= arr[start]))
            start = mid + 1;
    }

    /* Should not happen */
    return 0;
}

/***********************************************************************/
/* binary_search: Binary search                                        */
/*                                                                     */
/***********************************************************************/
int binary_search(int *arr, int start, int end, int val)
{
    int max = end, min = start, mid;

    /* Log(n) complexity scan! */
    while (max >= min)
    {
        /* Get to the center */
        mid = (max + min) / 2;

        /* We have a hit? */
        if (arr[mid] == val)
            return mid;

        /* Else adjust the scan window */
        else if (arr[mid] < val)
            min = mid + 1;
        else
            max = mid - 1;
    }

    /* Fail */
    return -1;
}

/***********************************************************************/
/* Suppose a sorted array is rotated at some pivot unknown to you      */
/* beforehand.                                                         */
/* (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).                   */
/*                                                                     */
/* You are given a target value to search. If found in the array       */
/* return its index, otherwise return -1.                              */
/* You may assume no duplicate exists in the array.                    */
/*                                                                     */
/***********************************************************************/
int search(int* nums, int numsSize, int target)
{
    int loc = -1;
    int pivot;

    /* Get the index where the array is rotated */
    pivot = binary_search_pivot(nums, numsSize);
    if (pivot == -1)
        return -1;

    /* Pivot zero meants it's not a rotated array */
    if (pivot == 0)
        loc = binary_search(nums, 0, numsSize - 1, target);

    /* Else search both the halves */
    else
    {
        /* Search the first half */
        if ((target <= nums[pivot - 1]) && (target > nums[numsSize - 1]))
            loc = binary_search(nums, 0, pivot - 1, target);
        /* Second half */
        else if ((target >= nums[pivot]) && (target <= nums[numsSize - 1]))
            loc = binary_search(nums, pivot, numsSize - 1, target);
    }

    /* Return the location */
    return loc;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    //              0    1  2  3  4  5  6  7  8  9  10 11  12  13  14  15  16
    int array[] = { 100, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 23, 34, 40, 59, 67};
    int search_array[] = {4, 5, 6, 7, 8, 9, 10, 23, 33, 44, 77, 88, 23, 34,
                          67, 59, 0, 1, 2, 33, 78};
    int slen = sizeof(search_array) / sizeof(int);
    int alen = sizeof(array) / sizeof(int), i;
    int t[] = { 5, 6, 1 };

    /* Search the rotated array */
    for (i = 0; i < slen; ++i)
        printf("%d at location : %d:\n", search_array[i],
               search(array, alen, search_array[i]));
    printf("%d at location : %d:\n", 1, search(t, 3, 1));
    return 0;
}

