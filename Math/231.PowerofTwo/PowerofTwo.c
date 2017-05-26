/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if O_LOGN
/***********************************************************************/
/* Given an integer, write a function to determine if it is a power of */
/* two.                                                                */
/***********************************************************************/
bool isPowerOfTwo(int n)
{
    int n1 = n, n2, b = 16;
    /* If it's negative, then return false. */
    if (n <= 0)  return false;

    /* Loop while there are bits remaining to check. */
    while (b)
    {
        /* Pick the lower half. */
        n2 = n1 & ((1 << b) - 1);
        /* Now the upper half. */
        n1 >>= b;

        /* If there are bits set in both, then it's not a
        power of two. */
        if (n1 && n2)
            return false;
        /* Pick the one with bits set. */
        if (n2) n1 = n2;
        b /= 2;
    }

    /* Power of two. */
    return true;
}
#else
/***********************************************************************/
/* Given an integer, write a function to determine if it is a power of */
/* two.                                                                */
/***********************************************************************/
bool isPowerOfTwo(int n)
{
    unsigned int x = n;
    if (n <= 0) return false;
    return !(x & (x - 1)) ? true : false;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int i;
    for (i = 0x40000000; i; i >>= 1)
        if (isPowerOfTwo(i) == false)
            printf("Error:\n");
    return 0;
}
