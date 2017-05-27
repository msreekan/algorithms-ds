/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a non-negative integer num, repeatedly add all its digits     */
/* until the result has only one digit.                                */
/* For example:                                                        */
/* Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 */
/* has only one digit, return it.                                      */
/***********************************************************************/
int addDigits(int num)
{
    int val = num, sum = 0;

    /* If the value is less than 10, then return. */
    if (num < 10)
        return num;

    /* Sum the digits. */
    while (val) {
        sum += val % 10;
        val /= 10;
    }

    /* Recursively generate the rest. */
    return addDigits(sum);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 38;
    printf("Sum digits = %d:\n", addDigits(num));
    return 0;
}
