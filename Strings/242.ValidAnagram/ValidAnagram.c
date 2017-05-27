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

/*************************************/
/* Macros.                           */
/*************************************/
#define ASCII_TO_INT(x) (((x) >= 'a' && (x) <= 'z') ? (x) - 97 : 0)

/***********************************************************************/
/* Given two strings s and t, write a function to determine if t is an */
/* anagram of s.                                                       */
/* For example,                                                        */
/* s = "anagram", t = "nagaram", return true.                          */
/* s = "rat", t = "car", return false.                                 */
/* Note:                                                               */
/* You may assume the string contains only lowercase alphabets.        */
/***********************************************************************/
bool isAnagram(char* s, char* t)
{
    int map1[26] = {0}, map2[26] = {0};
    int i;
    bool ret = false;

    /* Validate the parameters. */
    if (!s || !t)
        return ret;

    /* Set the map. */
    for (i = 0; s[i] && t[i]; ++i)
    {
        map1[ASCII_TO_INT(s[i])]++;
        map2[ASCII_TO_INT(t[i])]++;
    }

    /* If both the strings are exhausted, then check the map. */
    if (!s[i] && !t[i] && !memcmp(map1, map2, sizeof(map1)))
        ret = true;

    /* Return status. */
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Hello world!\n");
    return 0;
}
