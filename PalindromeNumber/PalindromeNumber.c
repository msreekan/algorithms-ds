/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>


/***********************************************************************/
/* check_palindrome : Recursively strip the integer from both the ends */
/*                                                                     */
/***********************************************************************/
int check_palindrome(int x, int c, int *div_list)
{
    int mnum, lnum;
    int d = 1;

    /* Left with one integer, it's a palindrome */
    if (c <= 1)
        return 1;

    /* Pick the divisor to extract most significant bit */
    d = div_list[c - 1 - 1];

    /* Get most and least significant digits */
    lnum = x % 10;
    mnum = x / d;

    /* Unequal, then we are done*/
    if (mnum != lnum)
        return 0;

    /* Strip the digits at the end */
    x %= d;
    x /= 10;

    /* Call the function recursively to check the remaining digits */
    return check_palindrome(x, c - 2, div_list);
}

/***********************************************************************/
/* Determine whether an integer is a palindrome. Do this without extra */
/* space.                                                              */
/*                                                                     */
/***********************************************************************/
int isPalindrome(int x)
{
    int num = x, c = 0;
    int div_list[31];
    int d = 1, i = 0;

    /* Ignore negative numbers */
    if (x < 0)
        return 0;

    /* Get the number of digits, also populate the divisor list */
    while (num)
    {
        num /= 10;
        d *= 10;
        div_list[i] = d;
        ++c;
        ++i;
    }

    /* Call the palindrome checker */
    return check_palindrome(x, c, div_list);
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int x = 1000011;
    printf("Palindrome Status = %d", isPalindrome(x));
    return 0;
}

