/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* Given a string S, you are allowed to convert it to a palindrome by  */
/* adding characters in front of it. Find and return the shortest      */
/* palindrome you can find by performing this transformation.          */
/* For example:                                                        */
/* Given "aacecaaa", return "aaacecaaa".                               */
/* Given "abcd", return "dcbabcd".                                     */
/***********************************************************************/
char* shortestPalindrome(char* s)
{
    int n = 0, i, j, k, len = strlen(s), m, z;
    char *rs;

    /* Allocate space for the new array. */
    rs = malloc((2 * len) * sizeof(char));
    if (!rs) return NULL;

    /* Look for the palindrome pattern, start from the end. */

    for (i = len - 1; i >= 0; i = m) {
        /* Move indices from both the ends seeking a palindrome. */
        m = i - 1;
        for (j = 0, k = i; j < k; ++j, --k) {
            if (s[j] != s[k])
                break;
            if (k < m && s[k] == s[0])
                m = k;
        }
        /* If we have a palindrome, then break. */
        if (j >= k)
            break;

        /* Keep copying the bytes. */
        for (z = i; z > m; --z)
            rs[n++] = s[z];
    }
    strcpy(&rs[n], s); // copy rest of the string

    /* Return the result. */
    return rs;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char str[] = "aacecaaa";
    #else
    char str[] = "babbbabbaba";
    #endif
    char *rs = shortestPalindrome(str);
    printf("Shortest = %s :\n", rs);
    free(rs);
    return 0;
}
