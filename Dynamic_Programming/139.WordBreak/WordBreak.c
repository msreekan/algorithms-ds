/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Utils/trie.h"

/**************************************/
/* Macros                             */
/**************************************/
#define DP_OFF(r, c, cz) (((r) * (cz)) + (c))

/***********************************************************************/
/* wordScan: Scan a string for dictionary words!                       */
/*                                                                     */
/***********************************************************************/
bool wordScan(char *str, int off, void *trie, unsigned char *dp, int r, int c)
{
    int i, status;
    void *node = NULL;

    /* If the requested string is terminating character, then return
    SUCCESS */
    if (str[off] == '\0')
        return true;

    /* Scan from the beginning */
    for (i = off + 1; str[i - 1]; ++i)
    {
        /* If get a hit, then delete the word and continue scanning */
        if ((node = SearchLenTrie(trie, node, &str[i - 1], 1, &status))
            && status >= 0 && dp[DP_OFF(i - 1, status, c)] == 0)
        {
            /* Continue scanning from the next location */
            if (wordScan(str, i, trie, dp, r, c) == 1)
                return true;
            dp[DP_OFF(i - 1, status, c)] = 1;
        }
        /* If there is no match, then return false */
        if (!node) return false;
    }

    /* We fell off the string, return failure */
    return false;
}

/***********************************************************************/
/* Given a string s and a dictionary of words dict, determine if s can */
/* be segmented into a space-separated sequence of one or more         */
/* dictionary words.                                                   */
/*                                                                     */
/* For example, given                                                  */
/* s = "leetcode",                                                     */
/* dict = ["leet", "code"].                                            */
/*                                                                     */
/* Return true because "leetcode" can be segmented as "leet code"./    */
/***********************************************************************/
bool wordBreak(char* s, char** wordDict, int wordDictSize)
{
    void *trie;
    int i;
    unsigned char *dp;
    bool status = false;
    int slen = strlen(s);

    /* Validate the parameters */
    if (!s && !wordDict && wordDictSize < 0)
        return false;

    /* Allocate the DP array */
    dp = calloc(slen * wordDictSize, sizeof(char));
    if (!dp) return false;

    /* Create a trie to store the dictionary */
    if (!(trie = InitTrie()))
        return NULL;

    /* Add the words to the dictionary */
    for (i = 0; i < wordDictSize; ++i) {
        if (AddToTrie(trie, wordDict[i])) {
            FreeTrie(trie);
            return false;
        }
    }

    /* Scan for the dictionary words */
    status = wordScan(s, 0, trie, dp, slen, wordDictSize);

    /* Free the memory */
    FreeTrie(trie);
    free(dp);
    return status; // return status
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char s[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    char *d[] = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    #elif 1
    char s[] = "leetcode";
    char *d[] = {"leet", "code"};
    #endif
    int len = sizeof(d) / sizeof(char *);
    /* Check for the dictionary words */
    if (wordBreak(s, d, len))
        printf("SUCCESS:\n");
    else
        printf("FAILURE:\n");
    return 0;
}
