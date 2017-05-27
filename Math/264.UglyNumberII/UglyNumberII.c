/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************/
/* Macros.                                     */
/***********************************************/
#define MIN(a, b, c) ((a) >  (b) ? ((b) > (c) ? (c) : (b)) : \
                                   ((a) > (c) ? (c) : (a)))

/***********************************************************************/
/* Write a program to find the n-th ugly number.                       */
/* Ugly numbers are positive numbers whose prime factors only include  */
/* 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence*/
/* of the first 10 ugly numbers.                                       */
/* Note that 1 is typically treated as an ugly number, and n does not  */
/* exceed 1690                                                         */
/***********************************************************************/
int nthUglyNumber(int n)
{
    int val, i, two = 0, three = 0, five = 0, l = 0;
    int *dp;

    /* If the value is less than equal to 0, then return error. */
    if (n <= 0) return 0;

    /* Allocate space. */
    dp = malloc(sizeof(long) * n);
    if (!dp)
        return 0;
    dp[0] = 1;

    /* Get to the nth value. */
    for (i = 1; i < n; ++i)
    {
        /* Pick the smallest for the next value in the sequence. */
        dp[++l] = MIN(dp[two] * 2, dp[three] * 3, dp[five] * 5);

        /* Increment the offsets until the values are greater than the
        largest one. */
        while(dp[two] * 2 <= dp[l]) two++;
        while(dp[three] * 3 <= dp[l]) three++;
        while(dp[five] * 5 <= dp[l]) five++;
    }

    /* Return the value. */
    val = dp[l];
    free(dp);
    return val;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 10;
    printf("Ugly number %d = %d !\n", n, nthUglyNumber(n));
    return 0;
}
