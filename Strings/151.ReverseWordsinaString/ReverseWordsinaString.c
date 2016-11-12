/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/generic.h"

/***********************************************************************/
/* Given an input string, reverse the string word by word.             */
/*                                                                     */
/* For example,                                                        */
/* Given s = "the sky is blue",                                        */
/* return "blue is sky the".                                           */
/*                                                                     */
/* Update (2015-02-12):                                                */
/* For C programmers: Try to solve it in-place in O(1) space.          */
/***********************************************************************/
void reverseWords(char *str)
{
    char *s, *e = str + strlen(str) - 1, *t, *te;

    /* Reverse the string */
    for (s = str; s < e; ++s, --e)
        SwapChars(s, e);

    /* Skip leading spaces */
    e = te = str;
    while (*te == ' ') ++te; // find the first non-space character

    /* Shift the non-space characters to left */
    for (;te != str && *(te - 1) != 0; ++te, ++e)
        *e = *te;

    /* Reverse all the words */
    for (e = str, s = str; *e != 0;)
    {
        /* Find the end of the word */
        while (*e != ' ' && *e != 0) ++e;

        /* Reverse the word */
        for (t = e - 1; t > s; ++s, --t)
          SwapChars(s, t);

        /* Seek beyond the consecutive spaces */
        if (*e) {

            /* Find the first non-space character. */
            te = e + 1;
            while (*te == ' ') ++te;

            /* Shift the characters to the left */
            for (t = e + 1; *e && te != t; ++te, ++t) {
                *t = *te;
                if (*te == 0 || *te == ' ') break;
                *te = ' ';
            }
            ++e;
            s = e; // move to the next word
        }
    }

    /* Remove any trailing spaces */
    if (*(e - 1) == ' ')
        *(e - 1) = 0;
}
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "   there  is   skies    bluesy ";
    //char s[] = "   1   ";;
    printf("Original Word = %s :\n", s);
    reverseWords(s);
    printf("Reversed = %s:\n",s);
    return 0;
}
