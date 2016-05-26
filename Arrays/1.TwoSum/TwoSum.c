/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define HEAP_SORT 0
#define BINARY_SEARCH 0

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

#if HEAP_SORT
/***********************************************************************/
/* sift_down : Sift down the tree                                      */
/*                                                                     */
/***********************************************************************/
void sift_down(int *a, int s, int len)
{
    int p = s;
    int c1, c2, c;

    /* Loop only till the index reaches the last non-leaf node. Allow the
       largest value to rise to the top */
    while(p <= ((len - 2) / 2))
    {
        /* First child index */
        c = c1 = (p * 2) + 1;

        /* Second child index */
        c2 = (p * 2) + 2;

        /* Pick the second child if it's greater than the first */
        if ((c2 < len) && (a[c2] > a[c1]))
            c = c2;

        /* Sift down the smaller value */
        if ((c < len) && (a[c] > a[p]))
            swap_ints(&a[c], &a[p]);

        /* Else we are done here */
        else
            break;
        /* Move to the next index */
        p = c;
    }
}
/***********************************************************************/
/*  heapify : Transform array into a heap                              */
/*                                                                     */
/***********************************************************************/
void heapify(int *a, int len)
{
    int p = (len - 2) / 2; // set the first non-leaf node index
    int c1, c2, c;

    /* Loop till the root node index */
    while(p >= 0)
    {
        /* First and second child index */
        c = c1 = (p * 2) + 1;
        c2 = (p * 2) + 2;

        /* Pick the second child if it's greater than the first */
        if ((c2 < len) && (a[c2] > a[c1]))
            c = c2;

        /* Sift down the smaller value */
        if (a[c] > a[p])
            sift_down(a, p, len);
        /* Decrement the parent index */
        p--;
    }
}

/***********************************************************************/
/* heap_sort: Heap sort!                                               */
/*                                                                     */
/***********************************************************************/
void heap_sort(int *a, int len)
{
    int i;

    /* Sanity check */
    if (!a || !len)
        return;

    /* Heapify the array */
    heapify(a, len);

    /* Heap Sort */
    for (i = 0; i < len; ++i)
    {
        swap_ints(&a[0], &a[len - 1 - i]);
        sift_down(a, 0, len - i - 1);
    }
}
#else
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
#endif

/***********************************************************************/
/* binary_search: Binary search                                        */
/*                                                                     */
/***********************************************************************/
int binary_search(int *a, int start, int end, int val)
{
    int mid;

    /* If the value is out of the range, return failure */
    if ((val < a[start]) || (val > a[end]))
        return -1;

    /* Loop while the index is within the range */
    while (start <= end)
    {
        /* Calculate the mid */
        mid = (start + ((end - start + 1) / 2));

        /* If there is a hit, return SUCCESS */
        if (a[mid] == val)
            return mid;
        /* Else adjust the "end" */
        else if (a[mid] > val)
            end = mid - 1;
        /* Else adjust the "start" */
        else
            start = mid + 1;
    }

    /* Return failure */
    return -1;
}

/***********************************************************************/
/* get_loc: Get the location from the original array                   */
/*                                                                     */
/***********************************************************************/
int get_loc(int *n, int len, int val, int aoffst)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        if ((i != aoffst) && (n[i] == val))
            return i;
    }
    return -1;
}

/***********************************************************************/
/* Given an array of integers, return indices of the two numbers such  */
/* that they add up to a specific target. You may assume that each     */
/* input would have exactly one solution.                              */
/*                                                                     */
/* Example: Given nums = [2, 7, 11, 15], target = 9,                   */
/* Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].               */
/*                                                                     */
/* URL : https://leetcode.com/problems/two-sum/                        */
/***********************************************************************/
int* twoSum(int* nums, int numsSize, int target)
{
    int i = 0, j;
    int *tn, sort = 0, dsort = 0;

    /* Sanity Check */
    if (!nums || (numsSize < 2))
        return NULL;

    /* Allocate */
    tn = malloc(sizeof(int) * numsSize);
    if (!tn)
        return NULL;

    /* Make a copy of the original array */
    for (i = 0; i < numsSize; ++i)
    {
        /* If the array is not sorted in increasing order, then set the
           flag */
        if ((!sort) && (i) && (nums[i] < nums[i - 1]))
            sort = 1;
        /* If the array is not sorted in decreasing order , then set the
           flag */
        if ((!dsort) && (i) && (nums[i] > nums[i - 1]))
            dsort = 1;
        tn[i] = nums[i];
    }

    /* If array is sorted in decreasing order, then simply reverse */
    if (!dsort)
    {
        int k = 0, l = numsSize - 1;
        while (k < l)
        {
            swap_ints(&tn[k], &tn[l]);
            k++;
            l--;
        }
    }

    /* Else if not sorted, sort */
    else if (sort)
    {
        /* SORT */
#if HEAP_SORT
        heap_sort(tn, numsSize);
#else
        quick_sort(tn, 0, numsSize - 1);
#endif // HEAP_SORT
    }

    /* If the largest values are less than target or smallest values are
    greater than target, return */
    if (((tn[numsSize - 1] + tn[numsSize - 2]) < target) ||
        ((tn[0] + tn[1]) > target))
        return NULL;

    /* If the largest values are equal to target, return the array */
    if ((tn[numsSize - 1] + tn[numsSize - 2]) == target)
    {
        int *arr = malloc(2 * sizeof(int));
        /* If malloc was successful, assign values */
        if(arr)
        {
            arr[0] = get_loc(nums, numsSize, tn[numsSize - 2], -1);
            arr[1] = get_loc(nums, numsSize, tn[numsSize - 1], arr[0]);
        }
        free(tn);
        return arr;
    }

#if BINARY_SEARCH
    /* Loop selecting the first element */
    for (i = 0; i < numsSize - 1; ++i)
    {
        int loc;

        /* Binary search for the next element */
        if ((loc = binary_search(tn, i + 1, numsSize - 1, target - tn[i])) != -1)
        {
            int *arr = malloc(2 * sizeof(int));

            /* If malloc was successful, assign values */
            if(arr)
            {
                arr[0] = get_loc(nums, numsSize, tn[i], -1);
                arr[1] = get_loc(nums, numsSize, tn[loc], arr[0]);
            }
            free(tn);
            return arr;
        }
    }
#else
    i = 0;
    j = numsSize - 1;

    /* Scan the array from both left and right. */
    while(i < j)
    {
        /* If the sum matches the target, we have a hit */
        if((tn[i] + tn[j]) == target)
        {
            int *arr = malloc(2 * sizeof(int));

            /* If malloc was successful, assign values */
            if(arr)
            {
                arr[0] = get_loc(nums, numsSize, tn[i], -1);
                arr[1] = get_loc(nums, numsSize, tn[j], arr[0]);
            }
            free(tn);
            return arr;
        }

        /* Else if the sum is greater then target, decrement the left index */
        else if ((tn[i] + tn[j]) > target)
            j--;

        /* Else if the sum is less then target, increment the right index */
        else
            i++;
    }
#endif
    /*
    ** Else return failure
    */
    free(tn);
    return NULL;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int *main_arr = NULL, *ret_arr = NULL;
    //int sampl[] = {0, 0, 3, 4, 5};
    int sampl[] = {5, 4, 3, 1, 0, 0};
    int len = sizeof(sampl) / sizeof(int);
    ret_arr = twoSum(sampl, len, 0);
    printf("ret_arr [%d] [%d]", ret_arr[0], ret_arr[1]);
    free(ret_arr);
    return 0;
}
