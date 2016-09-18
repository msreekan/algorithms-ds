#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************/
/* Data Structures                   */
/*************************************/
typedef enum
{
    false,
    true
} bool;

/*************************************/
/* Macros                            */
/*************************************/
#define DPOFF(x, yl, y) ((x) * (yl) + (y))
#define MAP_LEN 52
#define CTONUM(x) ((x) > 90 ? (x) - 97 : (x) - 65)

/***********************************************************************/
/* gen_map: Generate character map                                     */
/*                                                                     */
/***********************************************************************/
int gen_map(char *s1, char *s2, char *s3, int *l1, int *l2, int *l3)
{
    int i;
    int map[MAP_LEN];

    /* Reset */
    memset(map, 0, MAP_LEN * sizeof(int));

    /* Generate */
    for (i = 0; s1[i]; ++i)
        map[CTONUM(s1[i])]++;
    *l1 = i;

    /* Generate */
    for (i = 0; s2[i]; ++i)
        map[CTONUM(s2[i])]++;
    *l2 = i;

    /* Validate */
    for (i = 0; s3[i]; ++i)
        if (--map[CTONUM(s3[i])] < 0)
            return false;
    *l3 = i;
    /* Strings contain matching characters */
    return true;
}


/***********************************************************************/
/* intCheck: Check string interleave!                                  */
/*                                                                     */
/***********************************************************************/
bool intCheck(char *s1, int s1off, int sl1, char *s2, int s2off, int sl2,
              char *s3, int s3off, int sl3, int *dp)
{
    int doff = DPOFF(s1off, sl2 + 1, s2off);

    /* If the solution is cached, then return */
    if (dp[doff] != 2)
        return dp[doff];

    /* If we have exhausted all the strings, then return true */
    if (!(sl1 - s1off) && !(sl2 - s2off) && !(sl3 - s3off))
        return dp[doff] = true;

    /* Reset status and attempt to advance the first string */
    dp[doff] = 0;
    if (sl1 != s1off && s1[s1off] == s3[s3off])
        dp[doff] = intCheck(s1, s1off + 1, sl1, s2, s2off, sl2, s3,
                            s3off + 1, sl3, dp);

    /* Now the second string */
    if (!dp[doff] && sl2 != s2off && s2[s2off] == s3[s3off])
        dp[doff] = intCheck(s1, s1off, sl1, s2, s2off + 1, sl2, s3,
                            s3off + 1, sl3, dp);
    /* Return the result */
    return dp[doff];
}

/***********************************************************************/
/* Given s1, s2, s3, find whether s3 is formed by the interleaving of  */
/* s1 nd s2.                                                           */
/* For example,                                                        */
/* Given:                                                              */
/* s1 = "aabcc",                                                       */
/* s2 = "dbbca",                                                       */
/* When s3 = "aadbbcbcac", return true.                                */
/* When s3 = "aadbbbaccc", return false.                               */
/*                                                                     */
/***********************************************************************/
bool isInterleave(char* s1, char* s2, char* s3)
{
    int sl1, sl2, sl3, ret, i, sz;
    int *dp;

    /* If the characters counts mismatch, return false */
    if (!gen_map(s1, s2, s3, &sl1, &sl2, &sl3) || (sl1 + sl2 != sl3))
        return false;
    sz = (sl1 + 1) * (sl2 + 1);

    /* Allocate dp */
    dp = malloc(sz * sizeof(int));
    if (!dp)
        return false;

    /* Initialize the array */
    for (i = 0; i < sz; ++i)
        dp[i] = 2;

    /* Check interleaving */
    ret = intCheck(s1, 0, sl1, s2, 0, sl2, s3, 0, sl3, dp);

    /* Free memoization */
    free(dp);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //char s1[] = "aabcc", s2[] = "dbbca", s3[] = "aadbbcbcac";
    char s1[] = "a", s2[] = "", s3[] = "a";
    printf("%s %s v/s %s = %d :\n", s1, s2, s3, isInterleave(s1, s2, s3));
    return 0;
}
