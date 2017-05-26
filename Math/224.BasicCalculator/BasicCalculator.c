/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************/
/* Macros                         */
/**********************************/
#define ASCII_TO_NUM(x) ((x) - 48)

/***********************************************************************/
/* tcal: Evaluate an expression!                                       */
/*                                                                     */
/***********************************************************************/
int tcal(char* s, int *i)
{
    long long opernd[2] = {0};
    int opoff = 0;
    char oper;

    /* Loop evaluating the expression. */
    while (s[*i])
    {
        /* If this is an open parenthesis, then recursively evaluate
           the expression within the braces. */
        if (s[*i] == '(')
        {
            /* Recursive call to get the value. */
            ++*i;
            opernd[1] = tcal(s, i);

            /* If we are looking for operand 2, then evaluate the
            expression. */
            if (opoff)
                opernd[0] = oper == '+' ? opernd[0] + opernd[1] :
                                          opernd[0] - opernd[1];
            else opernd[0] = opernd[1];
            opernd[1] = 0; // reset operand2 and state
            opoff = 1;
        }

        /* If this is a close parenthesis, then if needed evaluate and
           return. */
        else if (s[*i] == ')')
        {
            /* If we have two operands, then complete the operation and
            then return. */
            if (opoff)
                opernd[0] =  (oper == '+') ? opernd[0] + opernd[1] :
                                             opernd[0] - opernd[1];
            return opernd[0];
        }

        /* Add the operator. */
        else if (s[*i] == '-' || s[*i] == '+')
        {
            /* If the present state was seeking operand 2, then complete
            previous operation. */
            opernd[0] = (opoff) ? ((oper == '+') ? opernd[0] + opernd[1] :
                         opernd[0] - opernd[1]) : opernd[0];
            oper = s[*i];
            opoff = 1;
            opernd[1] = 0; // reset state
        }

        /* Else accumulate the operands. */
        else if (s[*i] >= '0' && s[*i] <= '9')
            opernd[opoff] = (opernd[opoff] * 10) + ASCII_TO_NUM(s[*i]);
        ++*i;
    }

    /* Complete any pending operations. */
    if (opoff)
        opernd[0] = (oper == '+') ? opernd[0] + opernd[1] :
                                    opernd[0] - opernd[1];
    return opernd[0];
}

/***********************************************************************/
/* Implement a basic calculator to evaluate a simple expression string.*/
/* The expression string may contain open (and closing parentheses),   */
/* the plus + or minus sign -, non-negative integers and empty spaces. */
/* You may assume that the given expression is always valid.           */
/* Some examples:                                                      */
/* "1 + 1" = 2                                                         */
/* " 2-1 + 2 " = 3                                                     */
/* "(1+(4+5+2)-3)+(6+8)" = 23!                                         */
/*                                                                     */
/***********************************************************************/
int calculate(char* s)
{
    int i = 0;

    /* Verify the parameter. */
    if (!s)
        return 0;
    /* Return the result. */
    return tcal(s, &i);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char s[] = "1 + 1";
    int val = 2;
    #elif 0
    char s[] = "2-1 + 2 ";
    int val = 3;
    #elif 0
    char s[] = "(1+(4+5+2)-3)+(6+8)";
    int val = 23;
    #elif 0
    char s[] = "  (  3 ) ";
    int val = 3;
    #elif 0
    char s[] = " 1-(5)";
    int val = -4;
    #elif 1
    char s[] = "(7)-(0)-(4)";
    int val = 3;
    #endif
    int res;
    if ((res = calculate(s)) != val)
        printf("%s = %d not %d ?:\n", s, res, val);
    else
        printf("%s = %d", s, res);
    return 0;
}
