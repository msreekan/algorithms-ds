/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************/
/* Basic macros                 */
/********************************/
#define ATOINT(x) ((x) - 48)
#define MAX_INT   0x7FFFFFFF
#define MIN_INT   0x80000000

/***********************************************************************/
/* myAtoi : Implement atoi to convert a string to an integer.          */
/***********************************************************************/
int myAtoi(char* str)
{
    char *s = str;
    char sign = '+';
    int val = 0;
    long long tval = 0;

    /* Maintain sanity */
    if (!s)
        return 0;

    /* Ignore white space */
    while (*s == ' ')
        ++s;

    /* Account for the sign */
    sign = (*s == '-') || (*s == '+') ?  *s++ : '+';

    /* Loop creating the integer while the character is valid and
       the value is within the bounds */
    while ((*s >= 48 && *s <= 57) && (tval < MAX_INT))
    {
        tval *= 10;
        tval += ATOINT(*s);
        ++s;
    }

    /* Handle any possible overflow/underflow */
    if (tval > MAX_INT)
        val = (sign == '+') ? MAX_INT : MIN_INT;
    else
    {
        val = tval;
        val = (sign == '-') ? -val : val;
    }

    /* Return the integer */
    return val;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *s[] = {
                "        1234",
                "12345   6",
                "-12345   6",
                "+12345   6",
                "::+12345   6",
                "2147483648",
                "-2147483648",
                "2147483647",
                "-2147483647",
                "-2147483649",
                "99999999999999999909999"};
    unsigned int i;

    for (i = 0; i < sizeof(s) / sizeof(char *); ++i)
        printf("Atoi %s = %d\n", s[i], myAtoi(s[i]));
    return 0;
}
