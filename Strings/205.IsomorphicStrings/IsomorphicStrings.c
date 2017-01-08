/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************************************************/
/* Given two strings s and t, determine if they are isomorphic.        */
/* Two strings are isomorphic if the characters in s can be replaced   */
/* to get t.                                                           */
/* All occurrences of a character must be replaced with another        */
/* character while preserving the order of characters. No two          */
/* characters may map to the same character but a character may map to */
/* itself.                                                             */
/* For example,                                                        */
/* Given "egg", "add", return true.                                    */
/* Given "foo", "bar", return false.                                   */
/* Given "paper", "title", return true.                                */
/*                                                                     */
/* You may assume both s and t have the same length.                   */
/***********************************************************************/
bool isIsomorphic(char* s, char* t)
{
    char cmap[256] = {0}, crmap[256] = {0};
    int i;
    bool ret = true;

    /* Validate */
    if (!s || !t)
        return false;

    /* Loop seeking the match. */
    for (i = 0; s[i] != 0 && ret == true; ++i)
    {
        /* If the map is not established, then set the same. Maintain
        the reverse map also. We cannot have two characters mapping to
        the same value. */
        if (!cmap[s[i]] && !crmap[t[i]]) {
            cmap[s[i]] = t[i];
            crmap[t[i]] = s[i];
        }

        /* Else ensure the map is a match. */
        else if (cmap[s[i]] != t[i])
            ret = false;
    }

    /* Return the result. */
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "ab", t[] = "ca";
    printf("Isomorphic status : %s v/s %s = %d:\n", s, t,
           isIsomorphic(s, t));
    return 0;
}
