#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************/
/* Basic Macros                        */
/***************************************/
#define TRUE 1
#define FALSE 0
#define FAILED 2
#define SUCCESS 1

/***********************************************************************/
/* is_match: Recursively search for a match!                           */
/*                                                                     */
/***********************************************************************/
int is_match(char *str, int soff, char *exp, int eoff, int slen,
             int elen, unsigned char *m_arr)
{
    char s = str[soff], e = exp[eoff];
    int aoff = (eoff * slen) + soff, el = elen - 1, sl = slen - 1;

    /* We are done processing */
    if ((soff == sl) && (eoff == el))
        return SUCCESS;

    /* If we have the result cached, then return the same */
    if (m_arr[aoff] != 0)
        return m_arr[aoff];

    /* Simple case where there is no wildcard '*' after this character */
    if (((e == '.') && (soff != sl) && (exp[eoff + 1] != '*')) ||
        ((e == s) && (exp[eoff + 1] != '*')))
        m_arr[aoff] = is_match(str, soff + 1, exp, eoff + 1, slen, elen,
                               m_arr);

    /* When there is a '*' after a character, then we can parse by either
       ignoring the character or by accounting for it */
    else if ((eoff != el) && (exp[eoff + 1] == '*'))
    {
        /* If the characters match, then we can automatically attempt to
           parse it both ways.
           1. First by ignoring the character preceding '*'.
           2. Then by accounting for that character.

           Note that the case where there is a wild-card '.' preceding a
           '*', we can search by accounting for the string character only
           if its valid.
        */
        if (((e == '.') && (soff != sl)) || (e == s))
        {
            /* If both the paths failed, then set status to the same */
            if ((is_match(str, soff, exp, eoff + 2, slen, elen, m_arr) == 2) &&
                (is_match(str, soff + 1, exp, eoff, slen, elen, m_arr) == 2))
                m_arr[aoff] = FAILED;
            /* Else we have a winner */
            else
                m_arr[aoff] = SUCCESS;
        }


        /* If the characters do not match, then we can anyway ignore
           it based on wild-card '*' */
        else if (e != s)
            m_arr[aoff] = is_match(str, soff, exp, eoff + 2, slen, elen,
                                   m_arr);
    }

    /* If the result is still 0, then set to failure */
    if (m_arr[aoff] == 0)
        m_arr[aoff] = FAILED;

    /* Return status */
    return m_arr[aoff];
}

/***********************************************************************/
/* '.' Matches any single character.                                   */
/* '*' Matches zero or more of the preceding element.                  */
/*                                                                     */
/* The matching should cover the entire input string (not partial).    */
/*                                                                     */
/* The function prototype should be:                                   */
/* bool isMatch(const char *s, const char *p)                          */
/*                                                                     */
/* Some examples:                                                      */
/* isMatch("aa","a") → false                                           */
/* isMatch("aa","aa") → true                                           */
/* isMatch("aaa","aa") → false                                         */
/* isMatch("aa", "a*") → true                                          */
/* isMatch("aa", ".*") → true                                          */
/* isMatch("ab", ".*") → true                                          */
/* isMatch("aab", "c*a*b") → true                                      */
/***********************************************************************/
int isMatch(char *str, char *exp)
{
    int slen, elen, ret;
    unsigned char *m_arr;

    /* Maintain Sanity */
    if (!str || !exp)
        return 0;

    /* Calculate the length, account for empty strings */
    slen = strlen(str) + 1;
    elen = strlen(exp) + 1 ;

    /* Allocate the memoization array, initialized with zeros */
    m_arr = calloc(slen * elen, sizeof(unsigned char));
    if (!m_arr)
        return 0;

    /* Evaluate the expression */
    ret = is_match(str, 0, exp, 0, slen, elen, m_arr);

    /* Map actual failure code 2 to zero */
    if (ret == FAILED)
        ret = FALSE;

    /* Free the array and return */
    free(m_arr);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    if(isMatch("bbabacccbcbbcaaab","a*b*a*a*c*aa*c*bc*") != FALSE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aa","aa") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aaa","aa") != FALSE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aa", "a*") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aa", ".*") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("ab", ".*") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aab", "c*a*b") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("aaa", "a*a") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("a", ".*") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("a", "*") != FALSE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("ab", ".*..") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("", ".*") != TRUE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");

    if (isMatch("bbabacccbcbbcaaab", "a*b*a*a*c*aa*c*bc*") != FALSE)
        printf("FAILURE\n");
    else
        printf("SUCCESS\n");
    return 0;
}
