/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

#if PARTITION_METHOD
/***********************************************************************/
/* GetPivot: Get the pivot!                                            */
/*                                                                     */
/***********************************************************************/
int GetPivot(int *nums, int start, int len)
{
    int i = start, j = len - 2, pivot = len - 1;

    /* Loop seeking the pivot. */
    while (i <= j)
    {
        /* Move the index as long as the values are less than equal
        to pivot. */
        while ((i < len - 1) && nums[i] <= nums[pivot])
            i++;

        /* Decrement the index as long as the values are greater than
        pivot. */
        while ((j >= 0) && nums[j] > nums[pivot])
            j--;

        /* If there is a need to swap, then do the same. */
        if (i < j)
            INT_SWAP(&nums[i], &nums[j]);
    }

    /* Swap pivot into place and return the pivot. */
    INT_SWAP(&nums[i], &nums[pivot]);
    return i;
}

/***********************************************************************/
/* Find the kth largest element in an unsorted array. Note that it is  */
/* the kth largest element in the sorted order, not the kth distinct   */
/* element.                                                            */
/* For example,                                                        */
/* Given [3,2,1,5,6,4] and k = 2, return 5.                            */
/* Note:                                                               */
/* You may assume k is always valid, 1 ≤ k ≤ array's length.           */
/***********************************************************************/
int findKthLargest(int* nums, int numsSize, int k)
{
    int pivot = -1, tk = numsSize - k, off = 0, len = numsSize;

    /* Validate the parameters. */
    if (!nums || numsSize < k )
        return -1;

    /* Divide and conquer: Keep looking for the pivot which equal 'k' */
    while (pivot != tk)
    {
        /* Get the pivot. */
        pivot = GetPivot(nums, off, len);

        /* If the pivot is greater than k, then search the lower half
        of the array. */
        if (pivot > tk)
            len = pivot;
        /* Else if the pivot is less than k, then search the upper half. */
        else if (pivot < tk)
            off = pivot;
    }

    /* Return the value. */
    return nums[pivot];
}
#else
/***********************************************************************/
/* Find the kth largest element in an unsorted array. Note that it is  */
/* the kth largest element in the sorted order, not the kth distinct   */
/* element.                                                            */
/* For example,                                                        */
/* Given [3,2,1,5,6,4] and k = 2, return 5.                            */
/* Note:                                                               */
/* You may assume k is always valid, 1 ≤ k ≤ array's length.           */
/***********************************************************************/
int findKthLargest(int* nums, int numsSize, int k)
{
    int *pq;
    int i, g;

    /* If priority queue allocation failed or if the parameters are
    invalid, then return. */
    if (!nums || numsSize < 1 || !(pq = malloc(k * sizeof(int))))
        return -1;

    /* Initialize the queue elements. */
    for (i = 0; i < k; ++i)
        pq[i] = -0x80000000;

    /* Add all the values to the priority Q.*/
    for (i = 0; i < numsSize; ++i)
    {
        /* If the value is greater than the root, then delete the root
        and insert the new value. */
        if (pq[0] < nums[i])
        {
            int p = 0, c1 = 1, c2 = 2, c;

            /* Sift down. Allow the smallest value to rise to the
            top. Deletion/Insertion always at the root. */
            pq[0] = nums[i];
            while (p < k)
            {
                /* Select the smaller child. */
                c = c1;
                if (c2 < k && pq[c2] < pq[c1])
                    c = c2;

                /* If the child is smaller, then swap. */
                if (c < k && pq[c] < pq[p])
                    INT_SWAP(&pq[c], &pq[p]);
                /* Else we are done. */
                else
                    break;

                /* Present child is the new parent. */
                p = c;
                c1 = (c * 2) + 1;
                c2 = (c * 2) + 2;
            }
        }
   }

    /* Free and return. */
    g = pq[0];
    free(pq);
    return g;
}
#endif
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int arr[] = {3, 2, 1, 5, 6, 4};
    int k = 5;
    #elif 0
    int arr[] = {1};
    int k = 1;
    #elif 0
    int arr[] = {2, 1};
    int k = 1;
    #else
    int arr[] = {7,6,5,4,3,2,1};
    int k = 2;
    #endif
    int len = sizeof(arr) / sizeof(int);

    printf("%d(k)th Largest = %d :\n", k, findKthLargest(arr, len, k));
    return 0;
}
