/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>


/***********************************************************************/
/* Reverse digits of an integer.                                       */
/* Example1: x = 123, return 321                                       */
/* Example2: x = -123, return -321                                     */
/*                                                                     */
/***********************************************************************/
int reverse(int x)
{
    unsigned long y = 0;  // unsigned long to handle overflow
    unsigned int x1 = abs(x);  // ignore sign

    /* Loop as long as there are digits to be reversed */
    while (x1)
    {
        /* Shift digits to the left */
        y = y * 10;

        /* Detect overflow */
        if (y > 0x7FFFFFFF)
            return 0;

        /* Pick the least significant digit */
        y += x1 % 10;
        x1 = x1 / 10;
    }

    /* Add the sign */
    if (x < 0)
        x = (int)-y;
    else
        x = y;

    /* Return */
    return x;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf ("Reverse of %d = %d", 1234, reverse(1234));
    return 0;
}

