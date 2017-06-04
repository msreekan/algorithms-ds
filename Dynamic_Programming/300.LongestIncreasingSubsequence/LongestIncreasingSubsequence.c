/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#if O_N2
/***********************************************************************/
/* Given an unsorted array of integers, find the length of longest     */
/* increasing subsequence.                                             */
/* For example,                                                        */
/* Given [10, 9, 2, 5, 3, 7, 101, 18],                                 */
/* The longest increasing subsequence is [2, 3, 7, 101], therefore the */
/* length is 4. Note that there may be more than one LIS combination,  */
/* it is only necessary for you to return the length.                  */
/* Your algorithm should run in O(n2) complexity.                      */
/* Follow up: Could you improve it to O(n log n) time complexity?      */
/***********************************************************************/
int lengthOfLIS(int* nums, int numsSize)
{
    int *dp;
    int i, j, max = 0, smax = 0;

    /* Validate the parameters. */
    if (!nums || numsSize < 0)
        return 0;

    /* Allocate space for the DP array. */
    if (!(dp = calloc(numsSize, sizeof(int))))
        return 0;

    /* Loop generating the DP array to find the maximum sequence. */
    for (i = 0; i < numsSize; ++i)
    {
        /* A sequence is at least of length 1. */
        dp[i] = 1;

        /* Scan for the previous sequences and pick the longest. */
        for (max = 0, j = i - 1; j >= max; --j)
            max = dp[j] > max && nums[i] > nums[j] ? dp[j] : max;
        dp[i] += max;
        /* Track the maximum. */
        smax = smax < dp[i] ? dp[i] : smax;
    }

    /* Free the DP array and return the maximum. */
    free(dp);
    return smax;
}
#else /* O_N_LOGN */
/***********************************************************************/
/* BinSearch: Binary search an array!                                  */
/*                                                                     */
/***********************************************************************/
int BinSearch(int *arr, int len, int val)
{
    int start = 0, end = len - 1, mid = 0;

    /* Search. */
    while (start <= end)
    {
        /* Get the middle and check whether there is a match. */
        mid = start + (end - start + 1) / 2;
        if (arr[mid] == val)
            break;

        /* If the value is greater, then the target will be to the
        left. */
        if (arr[mid] > val)
            end = mid - 1;
        else
            start = mid + 1;
    }

    /* Return the last checked location. */
    return mid;
}

/***********************************************************************/
/* Given an unsorted array of integers, find the length of longest     */
/* increasing subsequence.                                             */
/* For example,                                                        */
/* Given [10, 9, 2, 5, 3, 7, 101, 18],                                 */
/* The longest increasing subsequence is [2, 3, 7, 101], therefore the */
/* length is 4. Note that there may be more than one LIS combination,  */
/* it is only necessary for you to return the length.                  */
/* Your algorithm should run in O(n2) complexity.                      */
/* Follow up: Could you improve it to O(n log n) time complexity?      */
/***********************************************************************/
int lengthOfLIS(int* nums, int numsSize)
{
    int *dp;
    int i, dloc, dlen = 1;

    /* Validate the parameters. */
    if (!nums || numsSize <= 0)
        return 0;

    /* Allocate space for the DP array. */
    if (!(dp = malloc(numsSize * sizeof(int))))
        return 0;

    /* Loop generating the DP array to find the maximum sequence. */
    dp[0] = nums[0];
    for (i = 1; i < numsSize; ++i)
    {
        /* Search for a location. If the maximum value in the DP array is
        smaller than the search key, then simply append. */
        dloc = dp[dlen - 1] > nums[i] ? BinSearch(dp, dlen, nums[i]) :
                                        dlen - 1;
        /* If the value is greater, then simply replace. */
        if (dp[dloc] > nums[i])
            dp[dloc++] = nums[i];
        /* Else if the value is less, then insert it to the next
        location. We are stacking the numbers in the increasing order
        and the eventual length of the array would give the maximum
        sequence length.*/
        else if (dp[dloc] < nums[i])
        {
            dp[++dloc] = nums[i];
            if (dloc == dlen) ++dlen; // update the length
        }
    }

    /* Free the DP array and return the maximum. */
    free(dp);
    return dlen;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
