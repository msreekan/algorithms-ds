/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************/
/* Basic Macros            */
/***************************/
#define MIN_INT(a, b, c) ((a) > ((b) > (c) ? (c) : (b))\
                         ? ((b) > (c) ? (c) : (b)) : (a))
#define MAX_CHAR 0xFF

/***********************************************************************/
/* ml: Recursively seek the minimum distance!                          */
/*                                                                     */
/***********************************************************************/
void ml(char* w1, int o1, int l1, char* w2, int o2, int l2,
        unsigned char *dp)
{
    int offst = (o1 * (l2 + 1)) + o2, od = ((o1 + 1) * (l2 + 1)) + o2;
    int oi = (o1 * (l2 + 1)) + o2 + 1, r = 0;

    /* End of the string, return the number of remaining characters
    in the other string */
    if (o1 == l1 || o2 == l2)
        dp[offst] = (o1 == l1) ? l2 - o2 : l1 - o1;

    /* If the minimum distance for strings at [o1..l1] & [o2..l2] is
       not already calculated, then figure out the same */
    else if (dp[offst] == MAX_CHAR)
    {
        /* Characters are unequal, try insert and delete */
        if (w1[o1] != w2[o2])
        {
            ml(w1, o1 + 1, l1, w2, o2, l2, dp);
            ml(w1, o1, l1, w2, o2 + 1, l2, dp);
            r++;
        }

        /* Replace and the case where characters are equal */
        ml(w1, o1 + 1, l1, w2, o2 + 1, l2, dp);

        /* Set the minimum */
        dp[offst] = (r > 0) ? (MIN_INT(dp[od + 1] + r, dp[od] + r,
                    dp[oi] + r)) : dp[od + 1];
    }
}

/***********************************************************************/
/* Given two words word1 and word2, find the minimum number of steps   */
/* required to convert word1 to word2. (each operation is counted as 1 */
/* step.)                                                              */
/*                                                                     */
/* You have the following 3 operations permitted on a word:            */
/*                                                                     */
/* a) Insert a character                                               */
/* b) Delete a character                                               */
/* c) Replace a character                                              */
/***********************************************************************/
int minDistance(char *word1, char * word2)
{
    int l1 = strlen(word1), l2 = strlen(word2), md = 0;
    unsigned char *dp = malloc((l1 + 1) * (l2 + 1) * sizeof(unsigned char));

    /* Validate */
    if (!dp) return 0;

    /* Initialize buffer */
    memset(dp, MAX_CHAR, (l1 + 1) * (l2 + 1));

    /* Get the minimum distance */
    ml(word1, 0, l1, word2, 0, l2, dp);
    md = dp[0];
    free(dp);
    return md;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char ch1[] = "zoologicoarchaeologist";
    char ch2[] = "zoopathologist";
    printf("Min Distance = %d :\n", minDistance(ch1, ch2));
    return 0;
}
