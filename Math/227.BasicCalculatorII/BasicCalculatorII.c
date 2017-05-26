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
/* Macros.                                 */
/*******************************************/
#define ASCII_TO_INT(x) ((x) - 48)

/***********************************************************************/
/* tcal: Evaluate all the division/multiplication!                     */
/*                                                                     */
/***********************************************************************/
int tcal(char* s, long long *arr)
{
    int i, off = 0;
    int opoff = 0;
    long long oprnd[2] = {0};
    char opsign = '+', oper;

    /* Loop adding all the tokens to the array. */
    for (i = 0; s[i]; ++i)
    {
        /* If it's addition or subtraction, then add the previous
        operand to array. */
        if (s[i] == '+' || s[i] == '-')
        {
            /* Complete any pending operation. */
            if (opoff)
                oprnd[0] = (oper == '/') ? oprnd[0] / oprnd[1]:
                                           oprnd[0] * oprnd[1];
            /* Assign the sign for the operand. */
            if (opsign == '-')
                oprnd[0] = -oprnd[0];
            arr[off++] = oprnd[0]; // add the operand to the list
            opoff = oprnd[0] = 0;
            opsign = s[i]; // new operand sign
        }

        /* Else if it's division on multiplication. */
        else if (s[i] == '/' || s[i] == '*')
        {
            /* Accumulate the result of any previous
            division/multiplication. */
            if (opoff)
                oprnd[0] = (oper == '/') ? oprnd[0] / oprnd[1]:
                                           oprnd[0] * oprnd[1];
            /* Seek the next operand. */
            opoff = 1;
            oprnd[1] = 0;
            oper = s[i];
        }

        /* Else accumulate operands. */
        else if (s[i] >= '0' && s[i] <= '9')
            oprnd[opoff] =  oprnd[opoff] * 10 + ASCII_TO_INT(s[i]);
    }

    /* Complete any pending division/multiplication. */
    if (opoff)
        oprnd[0] = (oper == '/') ? oprnd[0] / oprnd[1]:
                                   oprnd[0] * oprnd[1];
    /* Assign the sign for the operand. */
    if (opsign == '-')
        oprnd[0] = -oprnd[0];

    /* Add the last value to the stack. */
    arr[off++] = oprnd[0];
    return off;
}

/***********************************************************************/
/* Implement a basic calculator to evaluate a simple expression string.*/
/* The expression string contains only non-negative integers,          */
/* +, -, *, / operators and empty spaces. The integer division should  */
/* truncate toward zero. You may assume that the given expression is   */
/* always valid.                                                       */
/***********************************************************************/
int calculate(char* s)
{
    int len = strlen(s), alen, i;
    long long *arr;
    long long res = 0;

    /* Allocate the array. */
    arr = malloc(sizeof(long long) * len);
    if (!arr)
        return -1;

    /* Evaluate all the division/multiplication. */
    alen = tcal(s, arr);

    /* Now evaluate addition/subtraction. */
    for (i = 0; i < alen; ++i)
        res += arr[i];
    return (int) res;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char s[] = "2 * 2 / 3";
    #elif 0
    char s[] = "1 + 2 - 2 * 2 / 3";
    #elif 0
    char s[] = "  1 + 2 - 2 * 2 / 3 * 10 / 20 + 10 - 45";
    #elif 1
    char s[] = "2*3 + 4";
    #endif
    printf("%s = %d:\n", s, calculate(s));
    return 0;
}
