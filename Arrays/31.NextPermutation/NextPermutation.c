/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* swap_ints : swap integer values                                     */
/*                                                                     */
/***********************************************************************/
void swap_ints(int *a, int * b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/***********************************************************************/
/* reverse_arr : Reverse the values in an array                        */
/*                                                                     */
/***********************************************************************/
void reverse_arr(int *a, int len)
{
    int i = 1, j, mid = len / 2;

    /* Select the offset based on the array length */
    if (len & 1)
        j = 1;
    else
        j = 0;

    /* Loop and reverse the array */
    while ((mid - i) >= 0)
    {
        swap_ints(&a[mid - i], &a[mid + j]);
        i++;
        j++;
    }
}

/***********************************************************************/
/* get_pivot : Get pivot for quick sort                                */
/*                                                                     */
/***********************************************************************/
int get_pivot(int *a, int start,  int end)
{
    int i = start, j = end - 1, pivot = end;

    /* Loop to figure out the pivot location */
    swap_ints(&a[start + ((end - start) / 2)], &a[pivot]);
    while (i <= j)
    {
        /* Locate the next element greater than pivot */
        while ((i < end) && (a[i] <= a[pivot]))
            i++;

        /* Locate the next element smaller than pivot */
        while ((j >= start) && (a[j] > a[pivot]))
            --j;

        /* Swap elements */
        if (i < j)
            swap_ints(&a[i], &a[j]);
    }

    /* Swap the pivot element into its location */
    if (i != pivot)
        swap_ints(&a[i], &a[pivot]);

    /* Return the pivot offset */
    return i;
}

/***********************************************************************/
/* quick_sort : Quick sort                                             */
/*                                                                     */
/***********************************************************************/
void quick_sort(int *a, int start, int end)
{
    int pivot;

    /* Exit condition check */
    if (start >= end)
        return;

    /* Get the pivot */
    pivot = get_pivot(a, start, end);

    /* Quick Sort!! */
    quick_sort(a, start, pivot - 1);
    quick_sort(a, pivot + 1, end);
}

/***********************************************************************/
/* Implement next permutation, which rearranges numbers into the       */
/* lexicographically next greater permutation of numbers.              */
/*                                                                     */
/* If such arrangement is not possible, it must rearrange it as the    */
/* lowest possible order (ie, sorted in ascending order).              */
/*                                                                     */
/* The replacement must be in-place, do not allocate extra memory.     */
/*                                                                     */
/* Here are some examples. Inputs are in the left-hand column and its  */
/* corresponding outputs are in the right-hand column.                 */
/* 1,2,3 → 1,3,2                                                       */
/* 3,2,1 → 1,2,3                                                       */
/* 1,1,5 → 1,5,1                                                       */
/***********************************************************************/
void nextPermutation(int* nums, int numsSize)
{
    int i, j, g = numsSize - 1;
    int len = numsSize;

    /* Maintain Sanity */
    if (!nums || !numsSize)
        return;

    /* Array length has to be greater than one */
    if (len <= 1)
        return;

    /* Seek the first offset where a number is preceded by a smaller
    value */
    for (i = len - 1; i >= 0; --i)
    {
        /* Break if the present offset value is smaller than the
        largest one till now */
        if (nums[i] < nums[g])
            break;

        /* If needed, update the largest value */
        if (nums[g] < nums[i])
            g = i;
    }

    /* If the array is sorted in decreasing order, then simply reverse */
    if (i < 0)
        reverse_arr(nums, len);

    /* Else we need to seek the pairs to swap */
    else
    {
        /* Locate the smallest value within the range [i, len] which is
        greater than the value at i */
        for (j = i + 1; j < len; ++j)
        {
            /* If needed, update the offset */
            if ((nums[j] > nums[i]) &&
                ((nums[j] - nums[i]) < (nums[g] - nums[i])))
                g = j;

            /* If the difference is one, then break */
            if (nums[g] - nums[i] == 1)
                break;
        }

        /* Swap the values, and sort the rest of the array */
        swap_ints(&nums[i], &nums[g]);
        quick_sort(nums, i + 1, len - 1);
    }
}

/***********************************************************************/
/* prn_array: Print array                                              */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *a, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[] = {4,2,0,2,3,2,0};
    int a1[] = {1};
    int a3[] = {4, 3, 2, 1, 0};
    int len3 = sizeof(a3) / sizeof(int);
    int len = sizeof(a) / sizeof(int), i;
    int len1 = sizeof(a1) / sizeof(int);
    int len2 = sizeof(a2) / sizeof(int);

    prn_arr(a, len);
    for (i = 0; i < 10; ++i)
    {
        nextPermutation(a, len);
        prn_arr(a, len);
    }

    prn_arr(a1, len1);
    nextPermutation(a1, len1);
    prn_arr(a1, len1);

    prn_arr(a2, len2);
    nextPermutation(a2, len2);
    prn_arr(a2, len2);

    prn_arr(a3, len3);
    nextPermutation(a3, len3);
    prn_arr(a3, len3);
    return 0;
}
