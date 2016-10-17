/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************/
/* Macros                               */
/****************************************/
#define MAX_INT 0x7FFFFFFF
#define DP_ON 1

#if DP_ON
/***********************************************************************/
/* isPalindrome: Check whether a string is palindrome                  */
/*                                                                     */
/***********************************************************************/
static inline int isPalindrome(char *s, int off, int len)
{
    int off1 = len / 2 - 1, off2 = (len & 1) ? len / 2 + 1 : len / 2;
    while(s[off + off1] == s[off + off2] && --off1 >= 0 && ++off2);
    return (off1 < 0) ? 1 : 0; // palidrome check
}

/***********************************************************************/
/* MinPalindrome: Find the minimum number of cuts required for         */
/*                palindrome sub-strings!                              */
/*                                                                     */
/***********************************************************************/
int MinPalindrome(char *s, int off, int len, int *dp)
{
    int min = 1, i = len - off;

    if (dp[off]) // Check for a cached solution
        return dp[off];

    /* Start searching with longest string, stop as soon as the minimum
       cut is <= 1. Note, MinPalindrome return min cut + 1*/
    for (i = len - off, dp[off] = MAX_INT; i > 0 && dp[off] > 2; --i) {
        /* Identify longest palindrome of length <= i starting at "off".*/
        while (i > 1 && !isPalindrome(s, off, i)) --i;

        /* Continue searching only if whole string is not a palindrome */
        min = off + i < len ? MinPalindrome(s, off + i, len, dp) + 1 : 1;
        dp[off] = dp[off] > min ? min : dp[off]; //update minimum
    }
    /* Return the minimum cut at offset "off" + 1*/
    return dp[off];
}

/***********************************************************************/
/* Given a string s, partition s such that every substring of the      */
/* partition is a palindrome.                                          */
/* Return the minimum cuts needed for a palindrome partitioning of s.  */
/* For example, given s = "aab",                                       */
/* Return 1 since the palindrome partitioning ["aa","b"] could be      */
/* produced using 1 cut.                                               */
/***********************************************************************/
int minCut(char* s)
{
    int min_count, len = strlen(s), *dp;

    if ((dp = calloc(len, sizeof(int))) == NULL) return -1;
    min_count = MinPalindrome(s, 0, len, dp);
    free(dp);
    return min_count - 1;
}
#else
/***********************************************************************/
/* isPalindrome: Check whether a string is palindrome                  */
/*                                                                     */
/***********************************************************************/
static inline int isPalindrome(char *s, int off, int len)
{
    int off1 = len / 2 - 1, off2 = (len & 1) ? len / 2 + 1 : len / 2;
    while(s[off + off1] == s[off + off2] && --off1 >= 0 && ++off2);
    return (off1 < 0) ? 1 : 0; // palidrome check
}
/***********************************************************************/
/* MinPalindrome: Find the minimum number of cuts required for         */
/*                palindrome sub-strings!                              */
/*                                                                     */
/***********************************************************************/
int MinPalindrome(char *s, int off, int len)
{
    int min, i = len - off, omin = MAX_INT;

    /* Start searching with longest string, stop as soon as the minimum
       cut is <= 1. Note, MinPalindrome return min cut + 1*/
    for (i = len - off; i > 0 && omin > 1; --i) {
        /* Identify longest palindrome of length <= i starting at "off".*/
        while (i > 1 && !isPalindrome(s, off, i)) --i;

        /* Continue searching only if whole string is not a palindrome */
        min = off + i < len ? MinPalindrome(s, off + i, len) + 1 : 0;
        omin = omin > min ? min : omin; //update minimum
    }
    /* Return the minimum cut + 1 at offset "off"*/
    return omin;
}

/***********************************************************************/
/* Given a string s, partition s such that every substring of the      */
/* partition is a palindrome.                                          */
/* Return the minimum cuts needed for a palindrome partitioning of s.  */
/* For example, given s = "aab",                                       */
/* Return 1 since the palindrome partitioning ["aa","b"] could be      */
/* produced using 1 cut.                                               */
/***********************************************************************/
int minCut(char* s)
{
    int min_count, len = strlen(s);
    min_count = MinPalindrome(s, 0, len);
    return min_count;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char a[] = "fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi";
    #elif 0
    char a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    #elif 0
    char a[] = "aab";
    #elif 0
    char a[] = "cdd";
    #elif 1
    char a[] = "fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi";
    #elif 0
    char a[] = "aabbaaabb";
    #endif
    printf("Min Cut = %d", minCut(a));
    return 0;
}
