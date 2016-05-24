/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define HEAP_SORT 0
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
/* threeSumClosest: Given an array S of n integers, find three integers*/
/*                  in S such that the sum is closest to a given       */
/*                  number, target. Return the sum of the three        */
/*                  integers. You may assume that each input would have*/
/*                   exactly one solution.                             */
/*                                                                     */
/*   For example, given array S = {-1 2 1 -4}, and target = 1.         */
/*   The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).     */
/*                                                                     */
/*   URL: https://leetcode.com/problems/3sum-closest/                  */
/*                                                                     */
/***********************************************************************/
int threeSumClosest(int* nums, int numsSize, int target)
{
    int *a = nums;
    int len = numsSize, i, j, pt = -1, psum;
    int sort = 0, dsort = 0;

    /* Sanity Check */
    if ((nums == NULL) || (len < 3))
        return -1;

    /* Best case optimization */
    if (len == 3)
        return a[0] + a[1] + a[2];

    /* Loop and check whether the array is already sorted */
    for (i = 1; i < numsSize; ++i)
    {
        /* If the array is not sorted in increasing order, then set the
           flag */
        if ((!sort) && (i) && (nums[i] < nums[i - 1]))
            sort = 1;
        /* If the array is not sorted in decreasing order , then set the
           flag */
        if ((!dsort) && (i) && (nums[i] > nums[i - 1]))
            dsort = 1;
    }

    /* If array is sorted in decreasing order, then simply reverse */
    if (!dsort)
    {
        int k = 0, l = numsSize - 1;
        while (k < l)
        {
            swap_ints(&nums[k], &nums[l]);
            k++;
            l--;
        }
    }

    /* Else sort */
    else if (sort)
    {
        /* SORT */
#if HEAP_SORT
        heap_sort(a, len);
#else
        quick_sort(a, 0, len - 1);
#endif // HEAP_SORT
    }

    /* Initialize the present sum and difference */
    i = 0;
    psum = a[0] + a[1] + a[2];
    pt = abs(target - psum);

    /* Outer loop picking the first element */
    while ((i < (len - 2)) && pt)
    {
        int k = len - 1, ti = -1;
        j = i + 1;

        /* Scan the array from left and right, attempting to narrow in on
           the correct pair */
        while (j < k)
        {
            /* Initialize the sum and difference */
            int tsum = a[j] + a[k] + a[i];
            int tpt = abs(target - tsum);

            /* Assign the next index */
            if ((ti == -1) && (a[j] != a[i]))
                ti = j;

            /* If the new sum is closer to the target, then update the
            status */
            if (tpt < pt)
            {
                pt = tpt;
                psum = tsum;
            }

            /* If target is found, then return */
            if (tsum == target)
                return target;
            /* Else if sum is larger than target, then decrement the right index */
            else if (tsum > target)
                k--;
            /* Else increment left index */
            else
                j++;
        }

        /* If there are no distinct elements anymore, then break */
        if (ti == -1)
            break;
        /* Assign the next index */
        i = ti;
    }

    /* Return the sum */
    return psum;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int array[] = {87,6,-100,-19,10,-8,-58,56,14,-1,-42,-45,-17,10,20,-4,13,-17,0,11,-44,65,74,-48,30,-91,13,-53,76,-69,-19,-69,16,78,-56,27,41,67,-79,-2,30,-13,-60,39,95,64,-12,45,-52,45,-44,73,97,100,-19,-16,-26,58,-61,53,70,1,-83,11,-35,-7,61,30,17,98,29,52,75,-73,-73,-23,-75,91,3,-57,91,50,42,74,-7,62,17,-91,55,94,-21,-36,73,19,-61,-82,73,1,-10,-40,11,54,-81,20,40,-29,96,89,57,10,-16,-34,-56,69,76,49,76,82,80,58,-47,12,17,77,-75,-24,11,-45,60,65,55,-89,49,-19,4};
    int target = -275;
    //int array[] = {1, 1, 1, 0};
    //int target = 100;
    int len = sizeof(array) / sizeof(int);
    printf("Closest 3sum = %d :\n", threeSumClosest(array, len, target));
    return 0;
}
