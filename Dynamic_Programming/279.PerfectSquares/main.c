/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************************************/
/* Macros                              */
/***************************************/
#define INT_MAX 0x7FFFFFFF

/***********************************************************************/
/* Given a positive integer n, find the least number of perfect square */
/* numbers (for example, 1, 4, 9, 16, ...) which sum to n.             */
/* For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given   */
/* n = 13, return 2 because 13 = 4 + 9.                                */
/***********************************************************************/
int numSquares(int n)
{
    int *dp;
    int val, j, i;

    /* If the value is less than 1, then return 0. */
    if (n < 1)
        return 0;

    /* Allocate DP array. */
    if (!(dp = calloc(n + 1, sizeof(int))))
        return 0;

    /* Generate best case combinations for all the numbers in the range
       1 - n. And progressively generate the best combination using that
       DP array. */
    for (j = 1; j <= n; ++j)
        for (dp[j] = INT_MAX, i = sqrt(j); i * i > 0 && dp[j] > 1; --i)
            dp[j] = 1 + dp[j - (i * i)] > dp[j] && dp[j] ? dp[j] :
                    1 + dp[j - (i * i)];
    /* Return the minimum. */
    val = dp[n];
    free(dp);
    return val;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Min Squares = %d \n", numSquares(35));
    return 0;
}
