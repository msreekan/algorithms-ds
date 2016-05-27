/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* climb: Recursively calculate the number of ways to climb steps      */
/*                                                                     */
/***********************************************************************/
int climb(int step, int *dp, int n)
{
    /* We have reached step 0, and hence return the last count */
    if (step <= 0)
        return dp[step + 1] + dp[step + 2];

    /* Else build on top of the previous calculation : Note that
    the number of ways to climb from step n is equal to sum of number
    of ways from step n + 1 and step + 2. */
    else
    {
        dp[step] = dp[step + 1] + dp[step + 2];
        return climb(step - 1, dp, n);
    }
}

/***********************************************************************/
/* You are climbing a stair case. It takes n steps to reach to the top.*/
/*                                                                     */
/* Each time you can either climb 1 or 2 steps. In how many distinct   */
/* ways can you climb to the top?                                      */
/***********************************************************************/
int climbStairs(int n)
{
    int i, num;
    int *dp;

    /* Ensure sanity */
    if ((!n) || (n < 0))
        return 0;

    /* Less than two is best case O(1) :) */
    if (n <= 2)
        return n;

    /* Allocate the array for dynamic programming */
    dp = malloc(sizeof(int) * (n));
    if (!dp)
        return 0;

    /* Initialize the array */
    for (i = 0; i < (n - 2); ++i)
        dp[i] = 0;

    /* Number of ways to climb from step n - 1 and n - 2 */
    dp[n - 1] = 1;
    dp[n - 2] = 2;

    /* Climb */
    num = climb(n - 3, dp, n);

    /* Free and return */
    free(dp);
    return num;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Climb Count = %d", climbStairs(44));
    return 0;
}

