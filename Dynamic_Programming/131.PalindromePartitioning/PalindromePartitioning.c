/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************/
/* Macros                                  */
/*******************************************/
#define MAX_COUNT 1024

/***********************************************************************/
/* ChkPalindrom: Check for palindrome!                                 */
/*                                                                     */
/***********************************************************************/
int ChkPalindrom(char *str, int len)
{
    int off1 = len / 2 - 1, off2 = (len & 1) ? len / 2 + 1 : len / 2;

    if (len <= 0) return 0; // empty string
    if (len == 1) return 1; // one character

    /* Move the offsets while the characters are equal */
    while(off1 >= 0 && str[off1] == str[off2]) {
        --off1;
        ++off2;
    }
    return off1 >= 0 ? 0 : 1; // return TRUE if whole string was scanned
}

/***********************************************************************/
/* PalindromeGen: Recursively generate palindromes!                    */
/*                                                                     */
/***********************************************************************/
void PalindromeGen(char *str, int off, int len, int strcnt, char ***ch,
                   int *csizes, int *rsize)
{
    int i = 1, tlen = len - off;

    /* If we are done, then process the solution. */
    if (off >= len)
    {
        csizes[*rsize] = strcnt; // assign the count
        /* Allocate space for next solution */
        if ((ch[++(*rsize)] = malloc(sizeof(char *) * len)) == NULL)
            return;

        /* Copy the previously generated strings. We are building
        on top of the previous solutions */
        for (i = 0; i < strcnt; ++i)
            (ch[*rsize])[i] = (ch[*rsize - 1])[i];
        return;
    }

    /* Loop generating palindromes of up to length len */
    for (i = 1; i <= tlen; ++i)
    {
        /* Find a palindrome */
        while (!ChkPalindrom(&str[off], i)) {
            ++i;
            if (i > tlen) // if there was no palindrome, then return */
                return;
        }

        /* Allocate space for the generated palindrome */
        if (((ch[*rsize])[strcnt] = malloc((i + 1) *
              sizeof(unsigned char))) == NULL)
            return;

        /* Copy and NULL terminate string */
        memcpy((ch[*rsize])[strcnt], &str[off], i);
        ((ch[*rsize])[strcnt])[i] = 0; // null terminate

        /* Generate the rest of the palindromes */
        PalindromeGen(str, off + i, len, strcnt + 1, ch, csizes, rsize);
    }
}

/***********************************************************************/
/* Given a string s, partition s such that every substring of the      */
/* partition is a palindrome.                                          */
/* Return all possible palindrome partitioning of s.                   */
/* For example, given s = "aab",                                       */
/* Return                                                              */
/* [                                                                   */
/*  ["aa","b"],                                                         */
/*  ["a","a","b"]                                                       */
/* ]                                                                   */
/***********************************************************************/
char*** partition(char* s, int** columnSizes, int* returnSize)
{
    char ***ch = NULL;
    int len = strlen(s);

    /* Validate the parameters */
    if (!s || !columnSizes || !returnSize)
        return NULL;
    *columnSizes = NULL;
    *returnSize = 0;

    /* Allocate space */
    if (((ch = malloc(sizeof(char **) * MAX_COUNT)) == NULL) ||
        ((*columnSizes = calloc(MAX_COUNT, sizeof(int))) == NULL) ||
        ((ch[0] = malloc(sizeof(char*) * len)) == NULL))
        goto __error_exit;

    /* Generate palindromes */
    PalindromeGen(s, 0, len, 0, ch, *columnSizes, returnSize);
    free(ch[*returnSize]); // free the last allocation.
    return ch;

__error_exit:
    if (*columnSizes){
            if (ch[0]) free(ch[0]);
            free(*columnSizes);
    }
    if (ch)
        free(ch);
    return NULL;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char a[] = "aab";
    int rsize, i, j;
    int *csize;
    char ***ch;

    /* Partition */
    ch = partition(a, &csize, &rsize);
    if (!ch)
        return -1;

    /* Print the solution */
    for (i = 0; i < rsize; ++i) {
        for (j = 0; j < csize[i]; ++j)
            printf("%s ", (ch[i])[j]);
        printf("\n");
    }

    /* Free the memory */
    for (i = 0; i < rsize; ++i) {
        for (j = 0; j < csize[i]; ++j)
            free((ch[i])[j]);
        free(ch[i]);
    }
    /* Done */
    return 0;
}
