/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**************************************/
/* Macros.                            */
/**************************************/
#define ASCII_TOINT(x) ((x) - '0')
#define INT_TOASCII(x) ((x) + '0')
#define SWAP_CHARS(c1, c2) {\
                             char t = c1;\
                             c1 = c2;\
                             c2 = t;\
                           }

/***********************************************************************/
/* GenSum: Generate sum of two strings.                                */
/*                                                                     */
/***********************************************************************/
void GenSum(char *n1, char *n2, char *sum)
{
    int l1 = strlen(n1), l2 = strlen(n2);
    int i = l1 - 1, j = l2 - 1, k = 0, c = 0, s;

    /* Loop adding the values. */
    while (i >= 0 && j >= 0)
    {
        c = (s = c + ASCII_TOINT(n1[i--]) + ASCII_TOINT(n2[j--])) / 10;
        sum[k++] = INT_TOASCII(s % 10);
    }

    /* Finish processing any remaining bytes. */
    if (i >= 0) {
        j = i;
        n2 = n1;
    }
    while(j >= 0)
    {
        c = (s = c + ASCII_TOINT(n2[j--])) / 10;
        sum[k++] = INT_TOASCII(s % 10);
    }

    /* Add any remaining carry. */
    if (c)
        sum[k++] = INT_TOASCII(c);
    sum[k] = 0; // null terminate

    /* Reverse the order. */
    for (i = 0, j = k - 1; i < j; ++i, --j)
        SWAP_CHARS(sum[i], sum[j]);
}

/***********************************************************************/
/* Additive: Recursively check for additive numbers!                   */
/*                                                                     */
/***********************************************************************/
int Additive(char *num, int len, int off, char *n1, char *n2)
{
    int i, ret = -1, j;
    char *s, *tn1 = n1, *tn2 = n2;

    /* If we have finished scanning the string, then return success. */
    if (!num[off])
        return 0;

    /* Return if allocation fails. */
    if  (!(s = malloc(sizeof(char) * (len / 2 + 1))))
        return -1;

    /* If we are looking for the first or second number, then
       generate the same.*/
    if (!n1 || !n2)
    {
        /* Scan from the beginning to the end. Avoid scanning if the
        remaining bytes are less than the digits in the number. */
        for (i = off; i - off + 1 < len - i; ++i)
        {
            /* Add the new value. */
            s[i - off] = num[i];
            s[i + 1 - off] = 0;

            /* Assign the memory. */
            if (!n1)
                tn1 = s;
            else
                tn2 = s;
            /* Recursively check for matches. If there was a hit, then
               break. */
            if (!(ret = Additive(num, len, i + 1, tn1, tn2)))
                break;
            /* Leading zero is not allowed. */
            if (i == off && num[i] == '0')
                break;
        }
    }

    /* Else we need to generate and verify the sum. */
    else
    {
        /* Generate the sum. */
        GenSum(n1, n2, s);

        /* Compare the sum with the string. */
        for (j = 0; s[j] && num[off + j]; ++j)
            if (s[j] != num[off + j])
                goto __AddExit;
        /* If the sum is larger than the remaining numbers, then
        exit. */
        if (!num[j] && s[j])
            goto __AddExit;

        /* If we have a hit, then continue the search. */
        tn1 = tn2;
        tn2 = s;
        ret = Additive(num, len, off + j, tn1, tn2);
    }

__AddExit:
    /* Free the memory and return the status. */
    free(s);
    return ret;
}

/***********************************************************************/
/* https://leetcode.com/problems/additive-number/#/description         */
/***********************************************************************/
bool isAdditiveNumber(char* num)
{
    int len = strlen(num);
    if (len < 3) return false;
    return !Additive(num, len, 0, NULL, NULL) ? true : false;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char s[] = "112358";
    #elif 0
    char s[] = "199100199";
    #elif   1
    char s[] = "1203";
    #elif 0
    char s[] = "111";
    #elif 1
    char s[] = "101";
    #endif
    printf("%s is Additive? = %d :\n", s, isAdditiveNumber(s));
    return 0;
}
