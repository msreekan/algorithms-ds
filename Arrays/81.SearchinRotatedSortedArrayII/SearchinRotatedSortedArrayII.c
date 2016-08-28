/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**********************************/
/* Data Structure                 */
/**********************************/
typedef int bool;

/***********************************************************************/
/* psearch: Search for the pivot!                                      */
/*                                                                     */
/***********************************************************************/
int psearch(int *a, int len, int t)
{
    int i = 0, j = len - 1, mid;

    /* Loop seeking the pivot */
    while (i < j)
    {
        /* Return if we find the target or the pivot */
        mid = i + (j - i) / 2;
        if ((a[mid] > a[mid + 1]) || (a[mid] == t))
            return mid + 1;

        /* If the location is to the right of pivot, then move left */
        if ((a[mid] < a[i]) || (a[mid] < a[j]))
            j = mid;
        /* Else move right */
        else if ((a[mid] > a[i]) || (a[mid] > a[j]))
            i = mid;

        /* Else we have the case where they are equal. So if pivot is at 0, then
           all the characters between i and j would be equal. Otherwise we
           need to move to the next unequal character location */
        else
            while (i != j && a[i] == a[j])
                i++;
    }

    /* Return starting address */
    return 0;
}

/***********************************************************************/
/* bin_search: Binary search!                                          */
/*                                                                     */
/***********************************************************************/
int bin_search(int *a, int len, int target)
{
    int i = 0, j = len - 1, mid;

    /* If the target is the first value, return. Handles array with
     one entry */
    if (a[i] == target)
        return 1;

    /* Loop seeking the pivot */
    while (i <= j)
    {
        /* Check whether it's the pivot */
        mid = i + (j - i) / 2;
        if (a[mid] == target)
            return 1;

        /* If the location is to the right of pivot, then move left */
        if (a[mid] > target)
            j = mid - 1;
        /* Else move right */
        else
            i = mid + 1;
    }

    /* Return failure */
    return 0;
}

/***********************************************************************/
/* Follow up for "Search in Rotated Sorted Array":                     */
/* What if duplicates are allowed?                                     */
/*                                                                     */
/* Would this affect the run-time complexity? How and why?             */
/*                                                                     */
/* Write a function to determine if a given target is in the array.    */
/*                                                                     */
/***********************************************************************/
bool search(int* nums, int numsSize, int target)
{
    int p = psearch(nums, numsSize, target);

    /* If the target was found, then return */
    if (p && nums[p - 1] == target)
        return 1;

    /* Figure out which side of the array should be searched */
    if (nums[p] <= target && nums[numsSize - 1] >= target)
        return bin_search(&nums[p], numsSize - p, target);
    else if (nums[0] <= target && p && nums[p - 1] >= target)
        return bin_search(&nums[0], p, target);

    /* Target out of range */
    return 0;
}

/***********************************************************************/
/* prn_arr: Print array!                                               */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *a, int len)
{
    int i;

    for (i = 0; i < len - 1; ++i)
        printf("%d, ", a[i]);
    printf("%d \n", a[i]);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[] = {1, 1, 3, 1}, a2[] = {1, 1}, a3[] = {3, 5, 1};
    int *a[] = {a3, a1, a1};
    int l = sizeof(a) / sizeof(int *), i;
    int len[] = {sizeof(a3) / sizeof(int),
                 sizeof(a1) / sizeof(int),
                 sizeof(a2) / sizeof(int)};
    int r[] = {1, 1, 0}, t[] = {3, 3, 0};

    /* Loop through the array */
    for (i = 0; i < l; ++i)
    {
        prn_arr(a[i], len[i]);
        printf("Target = %d : Result = %d \n\n", t[i],
               (r[i] == search(a[i], len[i], t[i])) ? 1 : -1);
    }

    return 0;
}
