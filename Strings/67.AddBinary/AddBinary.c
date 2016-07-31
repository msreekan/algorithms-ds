/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CTONUM(x) ((x) - 48)
#define NUMTOC(x) ((x) + 48)

/***********************************************************************/
/* Given two binary strings, return their sum (also a binary string).  */
/*                                                                     */
/* For example,                                                        */
/* a = "11"                                                            */
/* b = "1"                                                             */
/* Return "100".                                                       */
/***********************************************************************/
char* addBinary(char* a, char* b)
{
    int s[] = {0, 1, 0, 1}, c[] = {0, 0, 1, 1}; // hash map for sum and carry
    int alen = strlen(a), blen = strlen(b), sum;
    int len = alen > blen ? alen : blen, i, cr = 0, j, k = len - 1;
    char *ab = (len == alen) ? a : b;

    /* Add the binary */
    for (i = alen - 1, j = blen - 1; i >= 0 || j >= 0; --i, --j)
    {
        /* calculate the sum only if the indices are valid */
        sum = (i >= 0) ? CTONUM(a[i]) + cr : cr;
        sum = (j >= 0) ? CTONUM(b[j]) + sum : sum;

        /* Get the sum and carry using the map */
        ab[k--] = NUMTOC(s[sum]);
        cr = c[sum];
    }

    /* If there is a carry, then we need to allocate new memory. */
    if (cr)
    {
        /* Allocate, NULL terminate and copy contents */
        char *ab1 = malloc(sizeof(char) * (len + 2));
        if (!ab1)
            return ab;
        memcpy(&ab1[1], ab, len + 1);
        ab1[0] = NUMTOC(cr);
        ab = ab1;
    }

    /* Return the array */
    return ab;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char a1[] = "11", a2[] = "11";
    char b1[] = "1", b2[] = "11";
    char *a[] = {a1, a2};
    char *b[] = {b1, b2};
    int len = sizeof(a) / sizeof(char *), i;
    char *c;

    for (i = 0; i < len; ++i)
    {
        printf("%s + %s = ", a[i], b[i]);
        c = addBinary(a[i], b[i]);
        printf("%s\n", c);
        if (c != a[i] && c != b[i])
            free(c);
    }
    return 0;
}
