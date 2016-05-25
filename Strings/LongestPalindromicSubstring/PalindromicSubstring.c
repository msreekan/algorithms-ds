/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* get_palindrome: Get even and odd palindrome at an offset            */
/*                                                                     */
/***********************************************************************/
void get_palindrome(char *s, int offst, int *soff, int *len)
{
    int k, l, odd_len, odd_offst;
    int even_len = 0, even_offst;

    /* Palindrome string can be of odd or even length, first we look
       for ODD, then even */
    k = 1;
    while (((offst - k) >= 0) && (s[offst - k] == s[offst + k]))
        k++;

    /* Set the odd palindrome offset and length */
    k--;
    odd_offst = offst - k;
    odd_len =  k * 2 + 1;

    /* Seek for an even palindrome */
    k = 0;
    l = 1;
    while (((offst - k) >= 0) && (s[offst - k] == s[offst + l]))
    {
        ++k;
        ++l;
    }

    /* If there was an even palindrome, then set the offset and length */
    if (k)
    {
        --k;
        --l;
        even_offst = offst - k;
        even_len = (offst + l) - (offst - k) + 1;
    }

    /* Pick the longest palindrome */
    if (odd_len > even_len)
    {
        *soff = odd_offst;
        *len = odd_len;
    }
    else
    {
        *soff = even_offst;
        *len = even_len;
    }
}

/***********************************************************************/
/* Given a string S, find the longest palindromic substring in S. You  */
/* may assume that the maximum length of S is 1000, and there exists   */
/* one unique longest palindromic substring.                           */
/*                                                                     */
/* URL : https://leetcode.com/problems/longest-palindromic-substring/  */
/***********************************************************************/
char *longestPalindrome(char* s)
{
    int i;
    int longest_offset = 0, longest_len = 1, mid;
    int poff, plen, slen;

    /* Ensure Sanity */
    if (!s)
        return NULL;

    /* Calculate the center of the string */
    slen = strlen(s);
    mid = slen / 2;
    if (!(slen & 1))
        mid -= 1;

    /* Look for palindrome at the center */
    get_palindrome(s, mid, &poff, &plen);
    if (plen > longest_len)
    {
        longest_offset = poff;
        longest_len = plen;
    }

    /* If the string is a palindrome, return the same */
    if (longest_len == slen)
        return s;

    /* Continue scanning for palindromes while moving the
    index towards both the ends */
    i = 1;
    while (((mid - i) >= 0) && (s[mid + i] != '\0'))
    {
        /* Scan for palindromes on the left half */
        get_palindrome(s, mid - i, &poff, &plen);
        if (plen > longest_len)
        {
            longest_offset = poff;
            longest_len = plen;
            if ((((mid - i) * 2) + 1) < longest_len)
                break;
        }

        /* Scan for palindromes on the right half */
        get_palindrome(s, mid + i, &poff, &plen);
        if (plen > longest_len)
        {
            longest_offset = poff;
            longest_len = plen;
            if ((((mid - i) * 2) + 1) < longest_len)
                break;
        }
        ++i;
    }

    /* Return the string */
    s[longest_offset + longest_len] = '\0';
    return &s[longest_offset];
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *p;
    int slen;

    slen = strlen("ccd");
    p = malloc(slen + 1);
    if (p == NULL)
        return -1;
    strcpy(p, "ccd");
    printf("%s \n", longestPalindrome(p));
    free(p);

    slen = strlen("a");
    p = malloc(slen + 1);
    if (p == NULL)
        return -1;
    strcpy(p, "a");
    printf("%s \n", longestPalindrome(p));
    free(p);

    slen = strlen("bb");
    p = malloc(slen + 1);
    if (p == NULL)
        return -1;
    strcpy(p, "bb");
    printf("%s \n", longestPalindrome(p));
    free(p);
    return 0;
}

