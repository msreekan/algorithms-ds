/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define FCOUNT_MAX 128
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
/* free_three : Free the pointers                                      */
/*                                                                     */
/***********************************************************************/
void free_three(int **nn, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        free(nn[i]);
    free(nn);
}

/***********************************************************************/
/* Given an array S of n integers, are there elements a, b, c in S such*/
/* that a + b + c = 0? Find all unique triplets in the array which     */
/* gives the sum of zero.                                              */
/*                                                                     */
/* Note: Elements in a triplet (a,b,c) must be in non-descending order.*/
/*       (ie, a = b = c)                                               */
/*       The solution set must not contain duplicate triplets.         */
/*       For example, given array S = {-1 0 1 2 -1 -4},                */
/*       A solution set is: (-1, 0, 1)                                 */
/*                          (-1, -1, 2)                                */
/*                                                                     */
/* URL : https://leetcode.com/problems/3sum/                           */
/***********************************************************************/
int** threeSum(int* nums, int numsSize, int* returnSize)
{
    int *a = nums, len = numsSize, i, j, k, tcount = 0, max;
    int **nn;
    int sort = 0, dsort = 0;

    /* Sanity Check */
    if ((nums == NULL) || (len < 3))
        return NULL;

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

    /*
    ** Three use case specific O(1) optimizations.
    */
    /* 1. If the smallest elements are greater than 0 or largest */
    /* elements are smaller than 0, it's a futile search */
    if (((nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3]) < 0) ||
        ((nums[0] + nums[1] + nums[2]) > 0))
        return NULL;

    /* 2. If the largest elements equate to the 0, then return */
    if ((nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3]) == 0)
    {
        /* Allocate the list */
        nn = malloc(sizeof(int *));
        if (!nn)
            return NULL;
        nn[0] = malloc (sizeof(int) * 3);
        if (!nn[0])
        {
            free_three(nn, 0);
            return NULL;
        }

        /* Assign and return the greatest values */
        *(nn[0]) = a[numsSize - 3];
        *(nn[0] + 1) = a[numsSize - 2];
        *(nn[0] + 2) = a[numsSize - 1];
        *returnSize = 1;
        return nn;
    }

    /* 3. If the smaller elements equate to the 0, then return */
    if ((numsSize == 3) && (nums[0] + nums[1] + nums[2]) == 0)
    {
        /* Allocate the list */
        nn = malloc(sizeof(int *));
        if (!nn)
            return NULL;
        nn[0] = malloc (sizeof(int) * 3);
        if (!nn[0])
        {
            free_three(nn, 0);
            return NULL;
        }

        /* Assign and return the smallest three values */
        *(nn[0]) = a[0];
        *(nn[0] + 1) = a[1];
        *(nn[0] + 2) = a[2];
        *returnSize = 1;
        return nn;
    }

    /* Allocate the list */
    nn = malloc(sizeof(int *) * FCOUNT_MAX);
    if (!nn)
        return NULL;

    /*
    ** Obvious brute force approach would be to use O(n^3), but here it's O(n^2).
    ** Another approach would be to have O(n^2 Log(n)) with the last element located
    ** via binary search.
    */

    /* Outer loop to pick the first element */
    i = 0;
    max = a[len - 1] + a[len - 2];
    while(i < (len - 2))
    {
        int tn1 = -1;

        /* Ensure this element is large enough to be part of the list */
        if ((max + a[i]) >= 0)
        {
            /* Left and Right scan indices */
            j = i + 1;
            k = len - 1;

            /* Scan while the left index is less than right and there is
               possibility to find two elements which eventually creates a
               list which adds up to zero */
            while ((j < k) && ((a[j] + a[j + 1] + a[i]) <= 0))
            {
                /* Set the next index */
                if ((tn1 == -1) && (a[j] != a[i]))
                  tn1 = j;

                /* If the elements add up to zero then save it to the list */
                if ((a[j] + a[k] + a[i]) == 0)
                {
                    int tk = k, tj = j;

                    /* Ensure access sanity */
                    if (tcount == FCOUNT_MAX)
                    {
                        free_three(nn, tcount);
                        return NULL;
                    }
                    nn[tcount] = malloc(sizeof(int) * 3);
                    if (nn[tcount] == NULL)
                    {
                        free_three(nn, 0);
                        return nn;
                    }

                    /* Save the numbers */
                    *nn[tcount] = a[i];
                    (*(nn[tcount] + 1)) = a[j];
                    (*(nn[tcount] + 2)) = a[k];
                    ++tcount;

                    /* Seek to the next distinct element */
                    do
                        --tk;
                    while ((tk > j) && (a[tk] == a[k]));
                    k = tk;

                    do
                        ++tj;
                    while ((tj < k) && (a[tj] == a[j]));
                    j = tj;
                }

                /* We need to increase the sum, increment the left pointer */
                else if ((a[j] + a[k]) < -a[i])
                    ++j;
                /* We need to reduce the sum, decrement the right pointer */
                else
                    --k;
            }

            /* If there are no distinct elements, then get out of the loop */
            if (tn1 == -1)
                break;

            /* Set the next index */
            i = tn1;
        }

        /* Else, move on to the next element */
        else
            ++i;
    }

    /* Set the array size, return */
    *returnSize = tcount;
    return nn;
}

/***********************************************************************/
/* prn_array: Print array                                              */
/*                                                                     */
/***********************************************************************/
void prn_array(int **arr, int len)
{
    int **sum = arr;
    int i;

    if (!len || !arr)
        return;

    for (i = 0; i < len; i += 1)
    {
        if ((*sum[i] > *(sum[i] + 1)) || (*(sum[i] + 1) > *(sum[i] + 2)))
            printf("ERROR %d:\n", i);
        printf("[%d, %d, %d] \n", *sum[i], *(sum[i] + 1), *(sum[i] + 2));
    }

}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    //              0   1  2   3    4    5   6  7   8  9 10  11  12  13 14 15
    //int array[] = {-1, -1, -2, -4, -6, -10, 11, -5, 0, 1, 2, -1, -4, 2, 3, 5};
    //int array[] = {1, 2, -2, -1};
    int array[] = {-1, 0, 1, 0};
    int i;
    //int array[] = {-1, 0, 1};
    int len = sizeof(array) / sizeof(int);
    int ret_sz, **ret_arr;
    ret_arr = threeSum(array, len, &ret_sz);
    prn_array(ret_arr, ret_sz);
    for(i = 0; i < ret_sz; ++i)
      free(ret_arr[i]);
    free(ret_arr);
    return 0;
}
