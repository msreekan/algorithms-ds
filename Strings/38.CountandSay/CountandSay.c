/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* cas : Count and say                                                 */
/*                                                                     */
/***********************************************************************/
int cas(char *c1, char *c2, int len)
{
    int i = 0, j = 0;

    /* Process the string in a loop */
    while (c1[i] !='\0')
    {
        char c = c1[i];
        int count = 0;

        /* Count the number of repeating characters */
        while ((c1[i] != '\0') && (c1[i] == c))
        {
            ++count;
            ++i;
        }

        /* Set the count and the character */
        c2[j++] = count + 48;
        c2[j++] = c;

        /* Just a sanity check */
        if (j > len)
            return -1;
    }

    /* Null terminate the string */
    c2[j] = '\0';
    return 0;
}

/***********************************************************************/
/* The count-and-say sequence is the sequence of integers beginning as */
/* follows:                                                            */
/* 1, 11, 21, 1211, 111221, ...                                        */
/*                                                                     */
/* 1 is read off as "one 1" or 11.                                     */
/* 11 is read off as "two 1s" or 21.                                   */
/* 21 is read off as "one 2, then one 1" or 1211.                      */
/*                                                                     */
/* Given an integer n, generate the nth sequence.                      */
/* Note: The sequence of integers will be represented as a string.     */
/***********************************************************************/
char* countAndSay(int n)
{
    char *ch1, *ch2, *ch1p, *ch2p;
    int i = 0, c = 1;

    /* Calculate the size of the final string  */
    while (i < ((n / 2) + 1))
    {
        c *= 2;
        ++i;
    }
    ++c;

    /* Allocate the ping pong buffers */
    ch1 = malloc(sizeof(char) * c);
    if (!ch1)
        return NULL;

    /* Initialize the array to "1" */
    ch1[0] = '1';
    ch1[1] = '\0';

    /* If the request is less than 2 then, return */
    if (n < 2)
        return ch1;

    /* Allocate the second string */
    ch2 = malloc(sizeof(char) * c);
    if (!ch2)
    {
        free(ch1);
        return NULL;
    }

    /* Reset the counter and initialize the pointers */
    i = 0;
    ch1p = ch1;
    ch2p = ch2;

    /* Process th string n - 1 times */
    while (i < (n - 1))
    {
        char *chp;

        /* Call the helper function to process ch1 and copy to ch2 */
        if (cas(ch1p, ch2p, c))
            break;
        ++i;

        /* Swap the pointers */
        chp = ch1p;
        ch1p = ch2p;
        ch2p = chp;
    }

    /* Return the final array */
    free(ch2p);
    return ch1p;
}

int main()
{
    char *ch;

    ch = countAndSay(1);
    printf("CAS 1 = %s \n", ch);
    free(ch);

    ch = countAndSay(2);
    printf("CAS 2 = %s\n", ch);
    free(ch);

    ch = countAndSay(5);
    printf("CAS 5 = %s\n", ch);
    free(ch);

    return 0;
}
