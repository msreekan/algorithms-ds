/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************/
/* Data Structure                */
/*********************************/
typedef int bool;

/*********************************/
/* Macros                        */
/*********************************/
#define MAP_LEN   52
#define TRUE      1
#define FALSE     0
#define CTONUM(x) ((x) > 90 ? (x) - 97 : (x) - 65)

/***********************************************************************/
/* gen_map: Generate character map                                     */
/*                                                                     */
/***********************************************************************/
int gen_map(char *s1, char *s2, int len)
{
    int i;
    int map[MAP_LEN];

    /* Reset */
    memset(map, 0, MAP_LEN * sizeof(int));

    /* Generate */
    for (i = 0; i < len; ++i)
        map[CTONUM(s1[i])]++;

    /* Validate */
    for (i = 0; i < len; ++i)
        if (--map[CTONUM(s2[i])] < 0)
            return FALSE;

    /* Strings contain matching characters */
    return TRUE;
}

/***********************************************************************/
/* rscr: Recursive scramble                                            */
/*                                                                     */
/***********************************************************************/
int rscr(char *s1, char *s2, int slen, int len, int s1off, int s2off,
         char *dp)
{
    int i, dpoff = (s1off * slen * slen + s2off * slen + len - 1);

    /* If the result is cached, then return the same */
    if (dp[dpoff] != 2)
        return dp[dpoff];

    /* If it's the leaf node */
    if (len == 1)
        return dp[dpoff] = (s1[s1off] == s2[s2off]) ? TRUE : FALSE;

    /* Ensure the strings consist of same characters */
    if (!gen_map(&s1[s1off], &s2[s2off], len))
        return dp[dpoff] = FALSE;

    /* Generate different binary trees by splitting the string
       at various locations. First check without switching the left &
       right children, then with the switch */
    for (i = 1 ; i < len; ++i)
        if ((rscr(s1, s2, slen, len - i, s1off + i, s2off + i, dp) &&
             rscr(s1, s2, slen, i, s1off, s2off, dp)) || // no swap
            (rscr(s1, s2, slen, len - i, s1off + i, s2off, dp) &&
             rscr(s1, s2, slen, i, s1off, s2off + len - i, dp))) // swap
            return dp[dpoff] = TRUE;

    /* Fail */
    return FALSE;
}

/***********************************************************************/
/*  https://leetcode.com/problems/scramble-string/                     */
/***********************************************************************/
bool isScramble(char* s1, char* s2)
{
    unsigned int len = strlen(s1);
    char *dp;
    bool ret;

    /* Ensure string is of the same length */
    if (strlen(s2) != len)
        return FALSE;

    /* Allocate memoization array */
    dp = malloc(len * len * len * sizeof(char));
    if (!dp)
        return FALSE;
    memset(dp, 2, len * len * len * sizeof(char));

    /* Get the result */
    ret = rscr(s1, s2, len, len, 0, 0, dp);
    printf("%d %d %d %d %d", dp[0], dp[1], dp[2], dp[3], dp[4]);

    /* Free and return */
    free(dp);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s1[] = "great", s2[] = "regat";
    printf("%s v/s %s = %d", s1, s2, isScramble(s1, s2));
    return 0;
}
