/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

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
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int sqr[] = {2147395599, 9, 16, 36, 64, 81, 49, 51};
    int len = sizeof(sqr) / sizeof(int), i;

    for (i = 0; i < len; ++i)
        printf("Sqrt(%d) = %d \n", sqr[i], mySqrt(sqr[i]));
    return 0;
}
