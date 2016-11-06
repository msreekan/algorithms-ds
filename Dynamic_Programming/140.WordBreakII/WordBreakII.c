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
#define MAX_STRINGS  256
#define STRING_STACK 256

/***********************************************************************/
/* wordScan: Scan a string for dictionary words!                       */
/*                                                                     */
/***********************************************************************/
void wordScan(char *str, char **dict, int off, void *trie,
              unsigned char *dp, int r, int c, int *retSz, int *strOff,
              int strTop, char **strRet)
{
    int i, status, tret;
    void *node = NULL;

    /* If the requested string is terminating character, then save the
    string and return */
    if (str[off] == '\0') {
        /* Allocate space for the combination string */
        if (!(strRet[*retSz] = malloc(sizeof(char) * (r + c))))
            return;

        /* Copy the first string */
        strcpy(strRet[*retSz], dict[strOff[0]]);
        for (i = 1; i < strTop; ++i) {
            strcat(strRet[*retSz], " "); // append " "
            strcat(strRet[*retSz], dict[strOff[i]]);
        }
        (*retSz) += 1; // increment count
        return;
    }

    /* Scan from the beginning */
    for (i = off + 1; str[i - 1]; ++i)
    {
        /* If get a hit, then continue DFS. */
        if ((node = SearchLenTrie(trie, node, &str[i - 1], 1, &status)) &&
            status >= 0 && dp[DP_OFF(i - 1, status, c)] == 0)
        {
            /* Start scanning from the next location */
            strOff[strTop] = status; // save the present index
            tret = *retSz; // make a copy
            wordScan(str, dict, i, trie, dp, r, c, retSz, strOff,
                     strTop + 1, strRet);

            /* If this combination does not yield any result,
            mark to avoid future traversals. */
            if (tret == *retSz)
                dp[DP_OFF(i - 1, status, c)] = 1;
        }

        /* If there is no match, then return false */
        if (!node) break;
    }
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
char **wordBreak(char* s, char** wordDict, int wordDictSize,
                 int* returnSize)
{
    void *trie = NULL;
    unsigned char *dp = NULL;
    int *strOffs = NULL;
    int strTop = 0, slen = strlen(s), i;
    char **strRet = NULL;

    /* Validate the parameters */
    if (!s || !wordDict || wordDictSize < 0 || !returnSize)
        return false;

    /* Allocate the DP array */
    if (!(dp = calloc((slen * wordDictSize), sizeof(char))) ||
        !(strOffs = malloc(sizeof(int) * STRING_STACK)) ||
        !(strRet = malloc(sizeof(char *) * MAX_STRINGS)) ||
        !(trie = InitTrie()))
        goto __exit;

    /* Add the words to the dictionary */
    for (i = 0; i < wordDictSize; ++i) {
        if (AddToTrie(trie, wordDict[i]))
            goto __exit;
    }

    /* Scan for the dictionary words */
    *returnSize = 0;
    wordScan(s, wordDict, 0, trie, dp, slen, wordDictSize, returnSize,
             strOffs, strTop, strRet);

__exit:
    /* Free the memory */
    FreeTrie(trie);
    if (dp) free(dp);
    if (strOffs) free(strOffs);
    return strRet; // return character string
}


/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "aaaaaaa";
    char *d[] = {"aaaa","aa","a"};
    //char s[] = "catsanddoghell";
    //char *d[] = {"cat", "cats", "and", "sand", "dog"};
    int len = sizeof(d) / sizeof(char *), ret, i;
    char **str;

    /* Check for the dictionary words */
    str = wordBreak(s, d, len, &ret);
    for (i = 0; i < ret; ++i) {
        printf("%s \n", str[i]);
        free(str[i]);
    }
    free(str);
    return 0;
}
