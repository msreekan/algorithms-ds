/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define FCOUNT_MAX 128

/***********************************************************************/
/* swap_ints : swap integer values                                     */
/*                                                                     */
/***********************************************************************/
void swap_ints(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
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
/* free_fours : Free the pointers                                      */
/*                                                                     */
/***********************************************************************/
void free_fours(int **fours, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        free(fours[i]);
    free(fours);
}

/***********************************************************************/
/* fourSum : Given an array "nums" of numsSize integers, are there     */
/*           elements a, b, c and d in S such that                     */
/*           a + b + c + d = target? Find all unique quadruplets in the*/
/*           array which gives the sum of target.                      */
/*                                                                     */
/*     Note: Elements in a quadruplet (a,b,c,d) must be in             */
/*           non-descending order. (ie, a = b = c = d). The solution   */
/*           set must not contain duplicate quadruplets.               */
/*                                                                     */
/*      URL: https://leetcode.com/problems/4sum/                       */
/***********************************************************************/
int** fourSum(int* nums, int numsSize, int target, int* returnSize)
{
    int i, j, k, fcount = 0;
    int **fours = NULL;
    int *a = nums;
    int sort = 0, dsort = 0;

    /* Sanity Check */
    if ((numsSize < 4)|| !nums)
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
        quick_sort(a, 0, numsSize - 1);
#endif // HEAP_SORT
    }

    /*
    ** Three use case specific O(1) optimizations.
    */
    /* 1. If the smallest elements are greater than target or largest */
    /* elements are smaller than target, it's a futile search */
    if (((nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3] +
          nums[numsSize - 4]) < target) || ((nums[0] + nums[1] +
          nums[2] + nums[3]) > target))
        return NULL;

    /* 2. If the largest elements equate to the target, then return */
    if ((nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3] +
         nums[numsSize - 4]) == target)
    {
        /* Allocate the list */
        fours = malloc(sizeof(int *));
        if (!fours)
            return NULL;
        fours[0] = malloc (sizeof(int) * 4);
        if (!fours[0])
        {
            free_fours(fours, 0);
            return NULL;
        }

        /* Assign and return the greatest values */
        *(fours[0]) = a[numsSize - 4];
        *(fours[0] + 1) = a[numsSize - 3];
        *(fours[0] + 2) = a[numsSize - 2];
        *(fours[0] + 3) = a[numsSize - 1];
        *returnSize = 1;
        return fours;
    }

    /* 3. If the smaller elements equate to the target, then return */
    if ((numsSize == 4) && ((nums[0] + nums[1] + nums[2] + nums[3]) == target))
    {
        /* Allocate the list */
        fours = malloc(sizeof(int *));
        if (!fours)
            return NULL;
        fours[0] = malloc (sizeof(int) * 4);
        if (!fours[0])
        {
            free_fours(fours, 0);
            return NULL;
        }

        /* Assign and return the smallest four values */
        *(fours[0]) = a[0];
        *(fours[0] + 1) = a[1];
        *(fours[0] + 2) = a[2];
        *(fours[0] + 3) = a[3];
        *returnSize = 1;
        return fours;
    }

    /* Allocate the list */
    fours = malloc(sizeof(int *) * FCOUNT_MAX);
    if (!fours)
        return NULL;

    /*
    ** Obvious brute force approach would be to use O(n^4), but here it's O(n^3).
    ** Another approach would be to have O(n^3 Log(n)) with the last element located
    ** via binary search.
    */

    /* Outer loop to pick the first element */
    i = 0;
    while (i < numsSize - 3)
    {
        int n1 = a[i];

        /* If this element is not large enough to be part of the list, then skip */
        if ((target - n1) <= (a[numsSize - 1] + a[numsSize - 2] + a[numsSize - 3]))
        {
            int tn1 = -1;

            /* Pick the second element */
            j = i + 1;
            while (j < numsSize - 2)
            {
                int n2 = a[j];
                int tn2 = -1;

                /* Next distinct element for the outer loop can be
                identified here */
                if ((tn1 == -1) && (n2 != n1))
                    tn1 = j;

                /* If this element is not large enough to be part of the list,
                then skip */
                if ((target - n1 - n2) <= (a[numsSize - 1] + a[numsSize - 2]))
                {
                    /* This loop identifies two remaining elements by scanning from
                    both the ends. Kind of similar to the quick sort partitioning
                    algorithm, but here we are looking for two elements which add up
                    to a particular sum */
                    int l = numsSize - 1;
                    k = j + 1;

                    /* Scan until the two pointers do not meet and as long as there is
                    a possibility of finding two elements adding up to the target */
                    while ((k < l) && ((a[k] + a[k + 1]) <= (target - n1 - n2)))
                    {
                        /* Next distinct element for the outer loop can be
                        identified here */
                        if ((tn2 == -1) && (a[k] != n2))
                            tn2 = k;
                        /* We have a match */
                        if ((a[k] + a[l]) == (target - n1 - n2))
                        {
                            int tk = k, tl = l;

                            /* Sanity check */
                            if (fcount == FCOUNT_MAX)
                            {
                                free_fours(fours, fcount);
                                return NULL;
                            }

                            /* Allocate and set the list */
                            fours[fcount] = malloc (sizeof(int) * 4);
                            if (!fours[fcount])
                            {
                                free_fours(fours, fcount);
                                return NULL;
                            }
                            *(fours[fcount]) = n1;
                            *(fours[fcount] + 1) = n2;
                            *(fours[fcount] + 2) = a[k];
                            *(fours[fcount] + 3) = a[l];
                            fcount++;

                            /* Find the next distinct element */
                            do
                                tk++;
                            while((tk < l) && (a[tk] == a[k]));
                            k = tk;

                            /* Again, find the next distinct element! */
                            do
                                tl--;
                            while((tl > k) && (a[tl] == a[l]));
                            l = tl;
                        }

                        /* We need to reduce the sum, decrement the right pointer */
                        else if ((a[k] + a[l]) > (target - n1 - n2))
                            --l;

                        /* We need to increase the sum, increment the left pointer */
                        else
                            ++k;
                    }

                    /* If there are no distinct elements, then get out of the loop */
                    if (tn2 == -1)
                        break;
                    /* Set the next index */
                    j = tn2;
                }
                /* Else, move on to the next element */
                else
                    ++j;
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
    *returnSize = fcount;
    return fours;
}

/***********************************************************************/
/*  prn_list: Print and free the list                                  */
/*                                                                     */
/***********************************************************************/
void prn_list(int **a, int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        printf("%d, %d, %d, %d \n", *a[i], *(a[i] + 1), *(a[i] + 2), *(a[i] + 3));
        free(a[i]);
    }
    free(a);
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    //          0  1  2   3  4  5  6   7
    int a[] = {-5, 5, 4, -3, 0, 0, 4, -2};
    int len = sizeof(a)/ sizeof(int), sz, target = 4;
    int **fours;
    fours = fourSum(a, len, target, &sz);
    if (fours)
        prn_list(fours, sz);
    return 0;
}

