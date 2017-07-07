/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* Write a program to find the nth super ugly number.                  */
/* Super ugly numbers are positive numbers whose all prime factors are */
/* in the given prime list primes of size k. For example, [1, 2, 4, 7, */
/* 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super*/
/* ugly numbers given primes = [2, 7, 13, 19] of size 4.               */
/* Note:                                                               */
/* (1) 1 is a super ugly number for any given primes.                  */
/* (2) The given numbers in primes are in ascending order.             */
/* (3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.                 */
/* (4) The nth super ugly number is guaranteed to fit in a 32-bit      */
/*     signed integer.                                                 */
/***********************************************************************/
int nthSuperUglyNumber(int n, int *p, int pnum)
{
  int *dp, *pn, *tpn;
  int l = 0, i, val;

  /* Validate the parameters. */
  if (n < 2 || !p || pnum < 1)
    return 1;

  /* Allocate the array. */
  if (!(dp = calloc((n + (pnum * 2)), sizeof(int))))
    return 1;
  pn = &dp[n];
  tpn = &pn[pnum];

  /* Initialize the array. */
  dp[0] = 1;
  memcpy(tpn, p, sizeof(int) * pnum);
  /* Seek the nth ugly number. */
  for (l = 0; l < n - 1; ++l)
    for (i = 0; i < pnum; ++i)
    {
        /* Update the value if this is the present ugly. */
        if (dp[l] == tpn[i])
            tpn[i] = dp[++pn[i]] * p[i];

        /* Initialize the next ugly. */
        if (!i)
            dp[l + 1] = tpn[i];
        /* Keep updating it. */
        dp[l + 1] = dp[l + 1] <= tpn[i] ? dp[l + 1] : tpn[i];
    }
  /* Save the value. */
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
    int p[] = {2, 7, 13, 19};
    int pl = sizeof(p) / sizeof(int);
    int n = 12;
    printf ("%dth Super Ugly Number = %d:\n", n, nthSuperUglyNumber(n, p, pl));
    return 0;
}
