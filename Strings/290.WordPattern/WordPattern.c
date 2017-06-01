/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************/
/* Macros                                */
/*****************************************/
#define ASCII_TO_OFFST(x) ((x)- 97)

/***********************************************************************/
/* strscmp: Compare two strings!                                       */
/*                                                                     */
/***********************************************************************/
int strscmp(char *s1, char *s2)
{
    int i;

    /* Loop comparing the characters, return in case of a mismatch. */
    for (i = 0; s1[i] != ' ' && s2[i] && s2[i] != ' '; ++i)
        if (s1[i] != s2[i])
            return 0;

    /* If strings comparison was complete, then return length, else 0. */
    return (s1[i] == ' ') && (!s2[i] || s2[i] == ' ') ? i: 0;
}

/***********************************************************************/
/* Given a pattern and a string str, find if str follows the same      */
/* pattern.                                                            */
/* Here follow means a full match, such that there is a bijection      */
/* between a letter in pattern and a non-empty word in str.            */
/* Examples:                                                           */
/* pattern = "abba", str = "dog cat cat dog" should return true.       */
/* pattern = "abba", str = "dog cat cat fish" should return false.     */
/* pattern = "aaaa", str = "dog cat cat dog" should return false.      */
/* pattern = "abba", str = "dog dog dog dog" should return false.      */
/*                                                                     */
/* Notes:                                                              */
/* You may assume pattern contains only lowercase letters, and str     */
/* contains lowercase letters separated by a single space.             */
/***********************************************************************/
bool wordPattern(char* pattern, char* str)
{
    char *map[26] = {NULL};
    int i, j, len, k;

    /* Loop through the pattern and the string. */
    for (i = 0, j = 0; pattern[i] && str[j]; ++i)
    {
        /* If this is a new pattern, then assign the map. */
        if (!map[ASCII_TO_OFFST(pattern[i])])
        {
            /* Avoid duplicate maps. */
            for (k = 0; k < 26; ++k)
                if ((map[k]) && strscmp(map[k], &str[j]))
                    return false;
            /* Assign. */
            map[ASCII_TO_OFFST(pattern[i])] = &str[j];

            /* Move to the next word. */
            while (str[j + 1] && str[j] != ' ')
                ++j;
        }

        /* Else compare the map. */
        else
        {
            /* If they match, then length is returned. */
            if (!(len = strscmp(map[ASCII_TO_OFFST(pattern[i])],
                                &str[j])))
                return false;
            j += len; // increment the pointer.
        }
        /* Increment only if character is valid. */
        if (str[j]) ++j;
    }

    /* If the pattern match, then return true. */
    return !pattern[i] && !str[j] ? true : false;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char p[] = "abc";
    char str[] = "b c a";
    //char p[] = "adda";
    //char str[] = "dog dog cat cat";
    //char str[] = "dog cat cat cat";
    //char str[] = "dog cat cat dog";
    printf("Pattern match = %d:\n", wordPattern(p, str));
    return 0;
}
