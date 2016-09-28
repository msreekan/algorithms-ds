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
#define DPOFF(x, y) ((x) * (tlen + 1) + (y))
#define RECURSIVE_MODE 0

#if RECURSIVE_MODE
/***********************************************************************/
/* numDistinct: Number of distinct values!                             */
/*                                                                     */
/***********************************************************************/
int numseq(char* s, char* t, int *num, int slen, int tlen, int soff,
            int toff, int *dp)
{
    int i, dpoff = soff * tlen + toff, tnum = *num;

    /* If we are done parsing, then increment counter */
    if (tlen == toff)
        (*num) += 1;
    /* If the result is cached, then return the same. */
    else if (dp[dpoff] != -1)
        (*num) += dp[dpoff];
    /* Loop attempting to match the first character of 't' */
    else    {
        for (i = soff; i + (tlen - toff) <= slen; ++i)
            if (s[i] == t[toff] &&
                (numseq(s, t, num, slen, tlen, i + 1, toff + 1, dp) ||
                (*num == tnum)))
                break;
        dp[dpoff] = *num - tnum;
    }
    return 0;
}


/***********************************************************************/
/* Given a string S and a string T, count the number of distinct       */
/* subsequences of T in S.                                             */
/* A subsequence of a string is a new string which is formed from the  */
/* original string by deleting some (can be none) of the characters    */
/* without disturbing the relative positions of the remaining          */
/* characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is   */
/* not).                                                               */
/* Here is an example:                                                 */
/* S = "rabbbit", T = "rabbit"                                         */
/* Return 3.                                                           */
/***********************************************************************/
int numDistinct(char* s, char* t)
{
    int num = 0, slen = strlen(s), tlen = strlen(t), i;
    int *dp;
    int dlen = slen * tlen;

    if (tlen > slen)
    return 0;

    /* Allocate and initialize DP. */
    dp = malloc(dlen * sizeof(int));
    if (!dp) return 0;
    for (i = 0; i < dlen; ++i)
        dp[i] = -1;

    /* Count the sequence */
    numseq(s, t, &num, slen, tlen, 0, 0, dp);
    free(dp);
    return num;
}
#else
/***********************************************************************/
/* prn_matrix: Print matrix!                                           */
/*                                                                     */
/***********************************************************************/
void prn_matrix(int *dp, int row, int col)
{
    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j)
            printf("%d ", dp[i * col + j]);
        printf("\n");
    }
}


/****************************************/
/* Macros                               */
/****************************************/
#define DPOFF(x, y) ((x) * (tlen + 1) + (y))

/***********************************************************************/
/* numDistinct: Number of distinct values!                             */
/*                                                                     */
/***********************************************************************/
int numseq(char* s, char* t, int slen, int tlen, int *dp)
{
    int i, j;
    for (i = 1; i <= slen; ++i) {
        dp[DPOFF(i - 1, 0)] = 1;
        for (j = 1; j <= tlen; ++j)
            dp[DPOFF(i, j)] = (s[i - 1] == t[j - 1]) ?
            dp[DPOFF(i - 1, j - 1)] + dp[DPOFF(i - 1, j)] :
            dp[DPOFF(i - 1, j)];
    }
    return dp[DPOFF(slen, tlen)];
}

/***********************************************************************/
/* Given a string S and a string T, count the number of distinct       */
/* subsequences of T in S.                                             */
/* A subsequence of a string is a new string which is formed from the  */
/* original string by deleting some (can be none) of the characters    */
/* without disturbing the relative positions of the remaining          */
/* characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is   */
/* not).                                                               */
/* Here is an example:                                                 */
/* S = "rabbbit", T = "rabbit"                                         */
/* Return 3.                                                           */
/***********************************************************************/
int numDistinct(char* s, char* t)
{
    int num = 0, slen = strlen(s), tlen = strlen(t);
    int dlen = (slen + 1) * (tlen + 1);
    int *dp;

    /* Validate */
    if (slen < tlen) return 0;

    /* Allocate and initialize DP. */
    dp = calloc(dlen, sizeof(int));
    if (!dp) return 0;

    /* Count the sequence */
    num = numseq(s, t, slen, tlen, dp);
    free(dp);
    return num;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char S[] = "rabbbit", T[] = "rabbit";
#if OTHER_STRINGS
    char S[] = "ddd", T[] = "dd"; // 3
    char S[] = "", T[] = "a";     // 0
    char S[] = "ccc", T[] = "c";  // 3
#endif
    printf("Number of Distinct sequences %s %s = %d :\n", S, T,
           numDistinct(S, T));
    return 0;
}
