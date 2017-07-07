/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************/
/* Macros                         */
/**********************************/
#define ACOUNT            26
#define ATOFF(x) ((x) - 'a')
#define OFTOA(x) ((x) + 'a')

/***********************************************************************/
/* Given a string which contains only lowercase letters, remove        */
/* duplicate letters so that every letter appear once and only once.   */
/* You must make sure your result is the smallest in lexicographical   */
/* order among all possible results.                                   */
/* Example:                                                            */
/* Given "bcabc"                                                       */
/* Return "abc"                                                        */
/* Given "cbacdcbc"                                                    */
/* Return "acdb"                                                       */
/***********************************************************************/
char* removeDuplicateLetters(char* s)
{
    char *rs;
    char fmap[ACOUNT] = {0};
    int l = strlen(s), i, c = 0, k = -1;
    int sl[ACOUNT] = {0};

    /* Validate.*/
    if (!s) return NULL;

    /* Allocate space for the return string. */
    if (!(rs = calloc((ACOUNT + 1), sizeof(char) )))
        return NULL;

    /* Find the last instance of all the characters. */
    for (i = l - 1; i >= 0 && c < ACOUNT; --i)
        if (!sl[ATOFF(s[i])]) {
            sl[ATOFF(s[i])] = i + 1;
            ++c;
        }

    /* Loop generating the most lexicographically small sequence. */
    for (i = 0; i < l; ++i)
    {
        /* Scan backwards seeking correct location for character at
           s[i] as long it's not already in the list and
           following conditions are true:
           1. Existing characters at rs[k] is greater.
           2. There are more instances of the character at rs[k]. */
        if (!fmap[ATOFF(s[i])]) {
            while (k >= 0 && rs[k] > s[i] && sl[ATOFF(rs[k])] - 1 > i) {
                /* Reset the map and decrement the count. */
                fmap[ATOFF(rs[k])] = 0;
                --k;
            }

            /* Place the character. */
            rs[++k] = s[i];
            fmap[ATOFF(s[i])] = 1; // reset map
        }
    }

    /* Null terminate, free and return. */
    rs[++k] = 0;
    return rs;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
#if 0
    char *a = "cbacdcbc";
#elif 1
    char *a = "cbaddabaa";
#elif 1
    char *a= "abacb";
#endif
    char *ra = removeDuplicateLetters(a);
    printf("Character = %s:\n", ra);
    free(ra);
    return 0;
}
