/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Character to Integer Conversion Macros */
#define CTONUM(x) ((x) - 48)
#define NUMTOC(x) ((x) + 48)

/***********************************************************************/
/* Given two numbers represented as strings, return multiplication of  */
/* the numbers as a string.                                            */
/*                                                                     */
/* Note:                                                               */
/*                                                                     */
/* •The numbers can be arbitrarily large and are non-negative.         */
/* •Converting the input string to integer is NOT allowed.             */
/* •You should NOT use internal library such as BigInteger.            */
/***********************************************************************/
char* multiply(char* num1, char* num2)
{
    char *ch1 = num1, *ch2 = num2, *cm, *sn, *ln, *cmc;
    int l1, l2, ls, lg, i, j, l4;

    /* Maintain Sanity */
    if (!ch1 || !ch2 || (ch1[0] == '\0') || (ch2[0] == '\0'))
        return NULL;

    /* Get the length of the strings */
    l1 = strlen(ch1);
    l2 = strlen(ch2);

    /* If either of the inputs are zero, then return the same */
    if ((ch1[0] == '0' && l1 == 1) || (ch2[0] == '0' && l2 == 1))
    {
        cm = malloc(sizeof(char) * 2);
        cm[0] = '0';
        cm[1] = '\0';
        return cm;
    }

    /* Calculate the length of the result, smaller and longer lengths */
    l4 = l1 + l2 + 1;
    ls = (l1 > l2) ? l2 : l1;
    lg  = (ls == l1) ? l2 : l1;

    /* Allocate array for the case where there is no carry */
    cmc = malloc(l4 * sizeof(char));
    if (!cmc)
        return NULL;

    /* Allocate memory for the case with carry */
    cm = calloc(l4, sizeof(char));
    if (!cm)
        return NULL;

    /* Assign the smaller and larger numbers */
    sn = (l2 > l1) ? ch1 : ch2;
    ln = (sn == ch1) ? ch2 : ch1;

    /* Multiplication loop */
    for (i = ls - 1; i >= 0; --i)
    {
        int c = 0, snum = CTONUM(sn[i]);

        /* Multiply the digit from the first number to
           each digit in the second one */
        for (j = lg - 1; j >= 0; --j)
        {
            int lnum = CTONUM(ln[j]), moff = i + j + 1;

            /* First instance needs initialization, after that addition */
            if (i == ls - 1)
                cm[moff] = (snum * lnum) + c;
            else
                cm[moff] = CTONUM(cm[moff]) + (snum * lnum) + c;

            /* Calculate the carry */
            c = cm[moff] / 10;
            cm[moff] %= 10;

            /* Save the character */
            cmc[moff - 1] = cm[moff] = NUMTOC(cm[moff]);
        }

        /* Store the final carry */
        cm[i] = NUMTOC(c);
    }

    /* If there was no final carry, then return the corresponding buffer */
    if (cm[0] == '0')
    {
        char *t = cm;
        cmc[l4 - 2] = '\0';
        cm = cmc;
        cmc = t;
    }

    /* Else simply NULL terminate*/
    else
        cm[l4 - 1] = '\0';

    /* Free one of the buffers and return the other */
    free(cmc);
    return cm;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char c1[] = "275485065762363579571460285849789549045";
    char c2[] = "219794283974447842783482931176910081510009563457827188601910822830183304372817619558310";
    char c3[] = "989";
    char c4[] = "199";
    char *cm1;

    printf("\n%s x \n%s\n", c1, c2);
    printf("-------------------------------------------\n");
    cm1 = multiply(c1, c2);
    if (cm1)
        printf("%s\n", cm1);
    free(cm1);

    printf("\n%s x \n%s\n", c3, c4);
    printf("-------------------------------------------\n");
    cm1 = multiply(c3, c4);
    if (cm1)
        printf("%s\n", cm1);
    free(cm1);
    return 0;
}
