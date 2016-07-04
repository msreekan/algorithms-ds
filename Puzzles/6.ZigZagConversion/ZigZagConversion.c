#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* The string "PAYPALISHIRING" is written in a zigzag pattern on a     */
/* given number of rows like this: (you may want to display this       */
/* pattern in a fixed font for better legibility)                      */
/* P   A   H   N                                                       */
/* A P L S I I G                                                       */
/* Y   I   R                                                           */
/*                                                                     */
/* And then read line by line: "PAHNAPLSIIGYIR"                        */
/*                                                                     */
/* Write the code that will take a string and make this conversion     */
/* given a number of rows:                                             */
/* string convert(string text, int nRows);                             */
/* convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".        */
/***********************************************************************/
char* convert(char* s, int numRows)
{
    int len, w = (numRows - 2) * 2 + 2, i, t1, t2, r = numRows;
    int cnt = (2 * r) - 3, c, j;
    char *ns;

    /* Maintain Sanity */
    if (!s || !r)
        return NULL;

    /* Get the length */
    len = strlen(s);

    /* If the number of rows less than two or is equal to or greater than
       length, then there is no scope for conversion */
    if ((r >= len) || (r < 2))
        return s;

    /* Allocate the buffer */
    ns = malloc(sizeof(char) * len);
    if (!ns)
        return NULL;

    /* First set of mapped characters are separated by the offset
       difference calculated by the equation (row - 2) * 2 + 2.

       0 1 2 3 4 5 6 7 8 9 10 11 12 13    < Old Offsets
       P A Y P A L I S H I R  I  N  G
       0       1       2         3        < New Mapped Offsets

       PAHN                               < Partially converted string

    */
    for (i = 0, j = 0; i < len; i += w, ++j)
        ns[j] = s[i];

    /* Subsequent characters can be derived by scanning towards the
       middle of these offset windows set by the above equation

       0 1 2 3 4 5 6 7 8 9 10 11 12 13    < Old Offsets
       P A Y P A L I S H I R  I  N  G
       0       1       2         3        < Boundary Offsets
       t1 <->  t2                         < Scan Window 0 - 4
               t1 <->  t2                 < Scan Window 4 - 8
                       t1  <->   t2       < Scan Window 8 - 12
                                 t1       < Scan Window 12 -13
       ------------------------------------------------------
       0 4   5 1 6   7 2 8    9  3  10    < Offsets (Iteration 0)
       P A Y P A L I S H I R  I  N  G     < t1 + 1 & t2 - 1

       "PAHNAPLSIIG"                      < Partially converted string

       ------------------------------------------------------
       0 4 11 5 1 6 12 7 2 8 13 9  3  10    < Offsets (Iteration 1)
       P A Y  P A L I  S H I  R I  N  G     < t1 + 2 & t2 - 2

       "PAHNAPLSIIGYIR"                     < Final Converted String
    */
    for (i = 0, c = 1; i < cnt; i += 2, ++c)
    {
        /* Initialize the scan window boundaries */
        t1 = 0;
        t2 = t1 + w;

        /* Scan */
        while ((t1 < len) || (t2 < len))
        {
            /* If the character is valid, then swap */
            if ((t1 + c) < len)
                ns[j++] = s[t1 + c];

            if ((t1 + c) != (t2 - c) && ((t2 - c) < len))
                ns[j++] = s[t2 - c];

            /* Advance the scan window */
            t1 = t2;
            t2 = t2 + w;
        }
    }

    /* Return Converted String */
    memcpy(s, ns, len);
    free(ns);
    return s;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s1[] = "PAYPALISHIRING";
    char s2[] = "A";
    char s3[] = "AB";

    printf("Convert %s = ", s1);
    printf("%s:\n",convert(s1, 3));

    printf("Convert %s = ", s2);
    printf("%s:\n",convert(s2, 1));

    printf("Convert %s = ", s3);
    printf("%s:\n",convert(s3, 1));
    return 0;
}
