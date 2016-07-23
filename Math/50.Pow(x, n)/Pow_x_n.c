/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Implement pow(x, n).                                                */
/*                                                                     */
/***********************************************************************/
double myPow(double x, int n)
{
    double y = x, t = 1;
    unsigned int i, nt = abs(n);

    /* Multiply n times */
    while (nt)
    {
        /* Keep squaring */
        for (i = 2; i < nt; i <<= 1)
            y *= y;

        /* Accumulate the product */
        t *= y;

        /* Reset y and recalculate the exponent */
        y = x;
        nt -= i >> 1;
    }

    /* Return while handling 0 and negative powers */
    return (n == 0) ? 1 : ((n > 0) ? t : 1 / t);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Pow (%f, %d) = %f!\n", 2.00000, 9, myPow(2.0000, 9));
    printf("Pow (%f, %d) = %f!\n", 0.00001, 2147483647, myPow(0.00001, 2147483647));
    printf("Pow (%f, %d) = %f!\n", 0.44528, 0, myPow(0.44528, 0));
    return 0;
}
