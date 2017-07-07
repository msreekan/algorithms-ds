/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if RECURSIVE
/***********************************************************************/
/* GetCoins: Recursively generate maximum coins!                       */
/*                                                                     */
/***********************************************************************/
int GetCoins(int *arr, int s, int e, int *dp, int n)
{
    int i, max;

    /* If the result is cached, then simply return. */
    if (dp[s * n + e])
        return dp[s * n + e];

    /* Loop seeking the maximum possible count. */
    for (i = s; i <= e; ++i) {
        /* Calculate the count if 'i' is bursted last. */
        max = (s < i ? GetCoins(arr, s, i - 1, dp, n) : 0) +
              (s - 1 > - 1 ? arr[s - 1] : 1) * arr[i] *
              (e + 1 < n ? arr[e + 1] : 1) +
              (i < e ? GetCoins(arr, i + 1, e, dp, n) : 0);

        /* Set the maximum. */
        dp[s * n + e] = max > dp[s * n + e] ? max : dp[s * n + e];
    }

    /* Return the maximum value. */
    return dp[s * n + e];
}

/***********************************************************************/
/* https://leetcode.com/problems/burst-balloons/#/description          */
/*                                                                     */
/***********************************************************************/
int maxCoins(int* nums, int n)
{
    int *dp;
    int val;

    /* Allocate DP. */
    if (!n || !(dp = calloc(n * n, sizeof(int))))
        return 0;

    /* Get the maximum count, free the memory and return. */
    val = GetCoins(nums, 0, n - 1, dp, n);
    free(dp);
    return val;
}
#else
/***********************************************************************/
/* https://leetcode.com/problems/burst-balloons/#/description          */
/*                                                                     */
/***********************************************************************/
int maxCoins(int* nums, int n)
{
    int *dp, *arr;
    int i, j, l, val, dn = n + 2;

    /* Validate. */
    if (!(arr = calloc((n + 2) * (n + 3), sizeof(int))))
        return 0;
    dp = &arr[n + 2];

    /* Make a copy. */
    memcpy(&arr[1], nums, sizeof(int) * n);
    arr[0] = 1;
    arr[n + 1] = 1;

    /* Loop seeking the coin count for sequences of all lengths. */
    for (l = 1; l <= n; ++l) {
        for (j = 1; j <= n + 1 - l; ++j) { /* Start with offfset 1. */
            /* Loop selecting each coin as the last one to burst. */
            for (i = j; i < j + l; ++i)
            {
                val = dp[j * dn + i - 1] + arr[j - 1] * arr[i] * arr[j + l] +
                      dp[(i + 1) * dn + j + l - 1];
                dp[j * dn + j + l - 1] = val > dp[j * dn + j + l - 1] ?
                                         val : dp[j * dn + j + l - 1];

            }
        }
    }
    /* Save the maximum and return. */
    val = dp[dn + dn - 2];
    free(arr);
    return val;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {3, 1, 5, 8};
    int len = sizeof(a) / sizeof(int);
    printf("Max = %d :\n", maxCoins(a, len));
    return 0;
}
