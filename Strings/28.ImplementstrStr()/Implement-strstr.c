/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*********************************/
/* Status Macro                  */
/*********************************/
#define FAIL -1

/***********************************************************************/
/* strn_cmp: Compare a substring                              `         */
/*                                                                     */
/***********************************************************************/
int strn_cmp(char *s, char *c)
{
    int i = 0;

    /* Loop and compare the characters */
    for (i = 0; c[i] && s[i]; ++i)
        if (s[i] != c[i])
            return 1;

    /* If the main string has ended, then return that status */
    if (c[i])
        return 2;

    /* Else return SUCCESS */
    return 0;
}

/***********************************************************************/
/* strStr: Returns the index of the first occurrence of needle in      */
/*         haystack, or -1 if needle is not part of haystack.          */
/*                                                                     */
/***********************************************************************/
int strStr(char* haystack, char* needle)
{
    char *h = haystack, *n = needle;
    int i = 0, ret = -1;

    /* Maintain sanity */
    if (!h || !n || (*h == 0 && *n != 0))
        return -1;

    /* Simple case */
    if ((*h != 0 && *n == 0) || (*h == 0 && *n == 0))
        return 0;

    /* Loop while the haystack is valid */
    while (h[i] != 0)
    {
        /* If the characters match, then compare */
        if ((h[i] == *n) && ((ret = strn_cmp(&h[i], n)) != 1))
            break;
        ++i;
    }

    /* If the string is valid, check the return status */
    if (ret == 0)
        return i;

    /* Return FAILURE */
    return FAIL;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *s[] = {"This is a simple string",
                 "",
                 "a",
                 ""};
    char *n[] = {"simple",
                 "a",
                 "",
                 ""};
    unsigned int i;

    for (i = 0; i < sizeof(s) / sizeof(char *); ++i)
        printf("\"%s\" at the offset %d in \"%s\". \n", n[i],
               strStr(s[i], n[i]), s[i]);
    return 0;
}
