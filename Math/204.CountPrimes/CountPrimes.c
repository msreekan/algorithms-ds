/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if BRUTE_FORCE
/***********************************************************************/
/* CheckPrime : Check whether a number is prime                        */
/***********************************************************************/
bool CheckPrime(int n)
{
    int i;

    /* Loop seeking a divisor. */
    for (i = 2; i <= n / 2; ++i)
        if (!(n % i)) // check for divisor
            return false;

    /* If there were no divisors, then return true. */
    return true;
}

/***********************************************************************/
/* Count number of prime numbers less than a non-negative number, n.   */
/***********************************************************************/
int countPrimes(int n)
{
    int count = 0, i;

    /* Loop seeking all the primes. */
    for (i = 2; i < n; ++i)
        if (CheckPrime(i))
            count++;

    /* Return the count. */
    return count;
}
#else
/***********************************************************************/
/* Implement int sqrt(int x).                                          */
/*                                                                     */
/* Compute and return the square root of x.                            */
/***********************************************************************/
int mySqrt(int x)
{
    int y = 2, inc = 32; // 32 is a random pick
    /* Increment till it's more than square root. Also, avoid going
       overboard */
    for(y = 2; y <= x/y; y += inc, inc <<= 3)
        inc = ((y + inc) > x / (y + inc)) ? 1 : inc;
    return x == 0 ? x : y - 1; // handle case 0
}

/***********************************************************************/
/* Count number of prime numbers less than a non-negative number, n.   */
/* Sieve of Eratosthenes                                               */
/***********************************************************************/
int countPrimes(int n)
{
    int i, j, scount = n - 2 > 0 ? n - 2 : 0, sqrt = mySqrt(n);
    unsigned char *map = calloc(n, sizeof(unsigned char));

    /* Run through all the numbers, from 2 to square root of n.
    It's square root because the inner loop starts with square.
    More details below. */
    for (j = 2; j <= sqrt; ++j)
    /* 1. If the number itself is not prime, the the multiples of this
          number would be covered by its factors -- !map[j].
       2. Multiples with values less than j would have already been
          covered by previous loops -- (i = j). For example, if j = 5,
          then 5 x 2 would have been covered by previous loops. */
        for (i = j; i * j < n && !map[j]; ++i)
            if (!map[i * j]) {
                map[i * j] = 1;
                scount--; // increment the count
            }

    /* Free the map and return the count. */
    free(map);
    return scount;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 499979;
    //int n = 10;
    printf("Number of primes less than %d = %d. \n", n, countPrimes(n));
    return 0;
}
