/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************/
/* Macros.                      */
/********************************/
#define MAX_ENTRIES     (4096 * 2)
#define ASCII_TO_INT(x) ((x) - 48)

/***********************************************************************/
/* Calc: Calculate an expression!                                      */
/*                                                                     */
/***********************************************************************/
long long Calc(char *gen, long long *arr)
{
    int i = 0, j = 0, opoff = 0;
    long long opernd[2] = {0};
    char sign = '+';

    /* Loop evaluating the expression. */
    while (gen[i])
    {
        /* If it's addition or subtraction, then add operand to array.*/
        if (gen[i] == '+' || gen[i] == '-')
        {
            /* If we have two operands, then multiply them. */
            if (opoff)
                opernd[0] *= opernd[1];
            arr[j++] = sign == '-' ? -opernd[0] : opernd[0];
            opoff = 0;
            opernd[0] = 0;
            sign = gen[i];
        }

        /* Else if it's a multiplication. */
        else if (gen[i] == '*')
        {
            /* If we have two operands, then multiply them. */
            if (opoff)
                opernd[0] *= opernd[1];
            /* Reset the state. */
            opernd[1] = 0;
            opoff = 1;
        }

        /* Else keep accumulating digits. */
        else
            opernd[opoff] = opernd[opoff] * 10 + ASCII_TO_INT(gen[i]);
        ++i;
    }

    /* Add any remaining operands to the array. */
    if (opoff)
        opernd[0] *= opernd[1];
    arr[j++] = sign == '-' ? -opernd[0] : opernd[0];

    /* Calculate the result. */
    for (i = 1; i < j; ++i)
        arr[0] += arr[i];

    /* Return the result. */
    return arr[0];
}

/***********************************************************************/
/* GenOp: Generate various string operations!                          */
/*                                                                     */
/***********************************************************************/
void GenOp(char *num, int noffst, int target, int *retsz, char **ops,
           char *gen, int goffst, long long *varr)
{
    /* If we have done generating, then evaluate. */
    if (!num[noffst])
    {
        /* Calculate the result. Ignore the trailing operand. */
        gen[goffst] = 0;
        long long val = Calc(gen, varr);

        /* If the value matches the target, then add to the solution. */
        if (val == target && *retsz < MAX_ENTRIES)
        {
            if (!((ops[*retsz]) = malloc(sizeof(char) * (goffst + 1))))
                return;
            memcpy(ops[*retsz], gen, goffst);
            (ops[*retsz])[goffst] = 0;
            ++*retsz;
        }
        return;
    }

    /* Avoid string of 0's as prefix for numbers. */
    if (goffst && gen[goffst - 1] == '0' &&
        (goffst == 1 || (gen[goffst - 2] == '-' ||
        gen[goffst - 2] == '+' || gen[goffst - 2] == '*')))
        return;
    /* Assign the value. */
    gen[goffst] = num[noffst];

    /* If this is the last operand, then avoid adding operands. */
    if (num[noffst + 1])
    {
        /* Insert all the possible tokens. */
        gen[goffst + 1] = '*';
        GenOp(num, noffst + 1, target, retsz, ops, gen, goffst + 2, varr);
        gen[goffst + 1] = '+';
        GenOp(num, noffst + 1, target, retsz, ops, gen, goffst + 2, varr);
        gen[goffst + 1] = '-';
        GenOp(num, noffst + 1, target, retsz, ops, gen, goffst + 2, varr);
    }
    GenOp(num, noffst + 1, target, retsz, ops, gen, goffst + 1, varr);
}

/***********************************************************************/
/* Given a string that contains only digits 0-9 and a target value,    */
/* return all possibilities to add binary operators (not unary) +, -,  */
/* or * between the digits so they evaluate to the target value.       */
/* Examples:                                                           */
/* "123", 6 -> ["1+2+3", "1*2*3"]                                      */
/* "232", 8 -> ["2*3+2", "2+3*2"]                                      */
/* "105", 5 -> ["1*0+5","10-5"]                                        */
/* "00", 0 -> ["0+0", "0-0", "0*0"]                                    */
/* "3456237490", 9191 -> []                                            */
/***********************************************************************/
char** addOperators(char* num, int target, int* retSize)
{
    char **ops;
    char *gen;
    long long *varr;
    int len = strlen(num);

    /* Validate the operands. */
    if (!num || !retSize)
        return NULL;
    *retSize = 0;

    /* Allocate memeory. */
    ops = malloc((sizeof(char **) * MAX_ENTRIES) +
                 (sizeof(long long) * len * 2) +
                 (sizeof(char) * len * 2));
    if (!ops) return NULL;

    /* Assign the integer array. */
    varr = (long long *)(ops + MAX_ENTRIES);
    gen = (char *) &varr[len];
    GenOp(num, 0, target, retSize, ops, gen, 0, varr);
    return ops;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "2147483648";
    int target = -2147483648, ret, i;
    char **ops;

    /* Get the operations. */
    ops = addOperators(s, target, &ret);

    /* Print. */
    for (i = 0; i < ret; ++i)
    {
        printf("%d : %s:\n", i + 1, ops[i]);
        free(ops[i]);
    }
    free(ops);
    return 0;
}
