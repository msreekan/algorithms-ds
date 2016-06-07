#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* generate_parentheses: Recursive generation of the combinations      */
/*                                                                     */
/***********************************************************************/
int generate_parentheses(char **ch, int *coff, int pos, int ocount,
                         int ccount, int len)
{
    /* If we are done with one combination, then save it */
    if ((ocount == 0) && (ccount == 0))
    {
        /* NULL termination */
        *(ch[*coff] + pos) = '\0';

        /* Increment the pointer */
        *coff += 1;

        /* Allocate the space for next combination */
        ch[*coff] = malloc(sizeof(char) * len);
        if (ch[*coff] == NULL)
            return -1;

        /* Copy the previous contents into the new buffer */
        memcpy(ch[*coff], ch[*coff - 1], pos);
        return 0;
    }

    /* Generate open braces if there is still a scope */
    if (ocount > 0)
    {
        *(ch[*coff] + pos) = '(';
        if (generate_parentheses(ch, coff, pos + 1, ocount - 1, ccount, len))
            return -1;
    }

    /* Generate closing braces only if there are matching open braces */
    if (ocount < ccount)
    {
        *(ch[*coff] + pos) = ')';
        if(generate_parentheses(ch, coff, pos + 1, ocount, ccount - 1,
                                len))
            return -1;
    }

    /* We are done */
    return 0;
}

/***********************************************************************/
/* Given n pairs of parentheses, write a function to generate all      */
/* combinations of well-formed parentheses.                            */
/* For example, given n = 3, a solution set is:                        */
/*                                                                     */
/* [                                                                   */
/*  "((()))",                                                          */
/*  "(()())",                                                          */
/*  "(())()",                                                          */
/*  "()(())",                                                          */
/*  "()()()"                                                           */
/* ].                                                                  */
/*                                                                     */
/* URL : https://leetcode.com/problems/generate-parentheses/           */
/***********************************************************************/
char** generateParenthesis(int n, int* returnSize)
{
    char **ch;
    int len = 2, i;

    /* Maintain sanity */
    if (!n || !returnSize)
        return NULL;

    /* Overestimate the number of combinations */
    for (i = 0; i < ((2 * n) - 2); ++i)
        len *= 2;

    /* Allocate the pointer array */
    ch = malloc(len * sizeof(char *));
    if (ch == NULL)
        return NULL;

    /* Allocate the space for the first string */
    ch[0] = malloc(sizeof(char) * (n * 2));
    if (ch[0] == NULL)
        return NULL;

    /* Reset the count and generate */
    *returnSize = 0;
    if (generate_parentheses(ch, returnSize, 0, n, n, (n * 2)))
    {
        /* If there is a failure, then wind up */
        for (i = 0; i <= *returnSize; ++i)
            free(ch[i]);
        free(ch);
        return NULL;
    }

    /* Free the redundant allocation */
    free(ch[*returnSize]);

    /* Return the string array */
    return ch;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int ret = 0, i;
    char **ch;
    int n = 3;
    ch = generateParenthesis(n, &ret);
    printf("\nGeneration Count = %d:\n", ret);

    for (i = 0; i < ret; i ++)
        printf("%s\n", ch[i]);

    return 0;
}

