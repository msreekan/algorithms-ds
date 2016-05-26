/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_INT 0x7FFFFFFF

/***********************************************************************/
/* Divide two integers without using multiplication, division and mod  */
/* operator.                                                           */
/*                                                                     */
/* If it is overflow, return MAX_INT.                                  */
/***********************************************************************/
int divide(int dividend, int divisor)
{
    unsigned int divd = abs(dividend), divs = abs(divisor), i = 1;
    int sign = 0, q = 0;
    unsigned abs_divs = abs(divisor);

    /* Identify the sign */
    if (((dividend < 0) && (divisor > 0)) ||
        ((dividend > 0) && (divisor < 0)))
        sign = 1;

    /* Loop till the divisor is equal to the dividend */
    while (divd >= divs)
    {
      /* Binary search for the quotient */
      for(i = 1; (divd >= divs); i <<= 1)
      {
          /* Overflow detection */
          if (divs & 0x80000000)
             break;
          divs <<= 1;
      }

      /* Left shift if the divisor went beyond
      the dividend */
      if (divs > divd)
      {
          divs >>= 1;
          i >>= 1;
      }

      /* Subtract divisor from dividend */
      divd -= divs;

      /* Reset the divisor */
      divs = abs_divs;

      /* Increment the quotient */
      q += i;

      /* If there is an over flow, return MAX_INT */
      if ((q & 0x80000000) && !sign)
        return MAX_INT;
    }

    /* Add the sign */
    if (sign)
        q = -q;

    /* Return quotient */
    return q;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int ndivd, ndivs;

    ndivd = -2147483648; ndivs = 1;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));

    ndivd = -1; ndivs = 1;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));

    ndivd = 36; ndivs = 4;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));

    ndivd = -2147483648; ndivs = -2147483648;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));

    ndivd = -2147483648; ndivs = -1;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));

    ndivd = -2147483648; ndivs = 1;
    printf("Dividing %d / %d = %d \n", ndivd, ndivs,
           divide(ndivd, ndivs));
    return 0;
}

