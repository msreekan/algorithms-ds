/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a string s consists of upper/lower-case alphabets and empty   */
/* space characters ' ', return the length of last word in the string. */
/*                                                                     */
/* If the last word does not exist, return 0.                          */
/*                                                                     */
/* Note: A word is defined as a character sequence consists of         */
/* non-space characters only.                                          */
/*                                                                     */
/* For example,                                                        */
/* Given s = "Hello World",                                            */
/* return 5.                                                           */
/***********************************************************************/
int lengthOfLastWord(char* s)
{
    int i, cnt = (*s != ' ' && *s != 0) ? 1 : 0;

    /* Loop while the string is valid */
    for (i = 1; s[i] != 0; ++i)
        if (s[i] != ' ')
            cnt = (s[i - 1] == ' ') ? 1 : cnt + 1;

    /* Return the count */
    return cnt;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s1[] = "Hello World";
    char s2[] = "        ";
    char s3[] = "a";
    char s4[] = "a  ";
    char *s[] = {s1, s2, s3, s4};
    int len = sizeof(s) / sizeof(char *), i;

    for (i = 0; i < len; ++i)
        printf("Last word length = %d\n", lengthOfLastWord(s[i]));
    return 0;
}
