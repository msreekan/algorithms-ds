/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************************************************/
/* get_happy: Get happy number!                                        */
/*                                                                     */
/***********************************************************************/
int get_happy(int num)
{
    int div = 10, val = 0;

    /* Loop seeking the value */
    while (num)
    {
        val += (num % 10) * (num % 10);
        num /= div;
    }

    /* Return the happy value */
    return val;
}

/***********************************************************************/
/* Write an algorithm to determine if a number is "happy".             */
/* A happy number is a number defined by the following process:        */
/* Starting with any positive integer, replace the number by the sum of*/
/* the squares of its digits, and repeat the process until the number  */
/* equals 1 (where it will stay), or it loops endlessly in a cycle     */
/* which does not include 1. Those numbers for which this process ends */
/* in 1 are happy numbers.                                             */
/* Example: 19 is a happy number                                       */
/*          12 + 92 = 82                                               */
/*          82 + 22 = 68                                               */
/*          62 + 82 = 100                                              */
/*          12 + 02 + 02 = 1                                           */
/*                                                                     */
/***********************************************************************/
bool isHappy(int n)
{
    int tn1 = n, tn2 = n;

    /* Floyd's searching algorithm. */
    do
    {
        tn1 = get_happy(tn1); // single step
        tn2 = get_happy(tn2); // two steps
        tn2 = get_happy(tn2);
    } while ((tn2 != 1) && (tn1 != tn2)); // detect loop and happy number

    /* Return depending on the final value. */
    return tn2 == 1 ? true : false;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 19;
    bool t = isHappy(num);
    printf("%d is %s!\n", num, t ? "Happy" : "Unhappy");
    return 0;
}
