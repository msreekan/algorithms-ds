/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************/
/* Macros.                     */
/*******************************/
#define MAX_COMBINATIONS     1024
#define ASCII_TO_INT(x)      ((x) - 48)

#if DP
/***********************************************************************/
/* compute: Different ways to compute!                                 */
/*                                                                     */
/***********************************************************************/
int *compute(char *exp, int soff, int eoff, int *retsz, int **dp,
             int *dplen, int dlen)
{
    int i, k, j, oper = 0, num1, num2, ocnt = 0, rcnt = 0;
    int *arr, *retarr1 = NULL, *retarr2 = NULL;

    /* Check the DP Array. */
    *retsz = dplen[(soff * dlen) + eoff];
    if (dp[(soff * dlen) + eoff])
        return dp[(soff * dlen) + eoff];

    /* Allocate array to store the results. */
    arr = malloc(sizeof(int) * MAX_COMBINATIONS);
    if (!arr)
        return NULL;

    /* Loop evaluating the expression. */
    for (i = soff; i <= eoff; ++i)
    {
        /* If this is an operand, then get all the result combinations. */
        if (exp[i] == '*' || exp[i] == '+' || exp[i] == '-')
        {
            retarr1 = compute(exp, soff, i - 1, &num1, dp, dplen, dlen);
            retarr2 = compute(exp, i + 1, eoff, &num2, dp, dplen, dlen);
            ocnt++;

            /* If we have combinations, then add them to the array. */
            /* Generate all possible combination results. */
            for (k = 0; k < num1; ++k)
                for (j = 0; j < num2; ++j)
                {
                    /* Avoid overflow. */
                    if ((rcnt == MAX_COMBINATIONS &&
                        !(arr = realloc(arr, sizeof(int) * MAX_COMBINATIONS * 2))) ||
                        rcnt == MAX_COMBINATIONS * 2)
                    {
                        free(arr);
                        return NULL;
                    }

                    /* Evaluate based on the operation. */
                    if (exp[i] == '*')
                        arr[rcnt++] = retarr1[k] * retarr2[j];
                    else if (exp[i] == '+')
                        arr[rcnt++] = retarr1[k] + retarr2[j];
                    else
                        arr[rcnt++] = retarr1[k] - retarr2[j];
                }
        }
        /* If there are no operators, then accumulate the operand. */
        else if (!ocnt && exp[i] >= '0' && exp[i] <= '9')
            oper = oper * 10 + ASCII_TO_INT(exp[i]);
    }

    /* If there were no operators, then assign the operand. */
    if (!ocnt) {
        arr[0] = oper;
        rcnt = 1;
    }

    /* Set the size and return. */
    *retsz = rcnt;
    dp[(soff * dlen) + eoff] = arr;
    dplen[(soff * dlen) + eoff] = rcnt;
    return arr;
}

/***********************************************************************/
/* Given a string of numbers and operators, return all possible results*/
/* from computing all the different possible ways to group numbers and */
/* operators. The valid operators are +, - and *.                      */
/***********************************************************************/
int* diffWaysToCompute(char* input, int* returnSize)
{
    int len = strlen(input), i;
    int *arr;
    int **dp;
    int *dplen;

    /* Validate. */
    if (!input || !returnSize)
        return NULL;
    *returnSize = 0;

    /* Allocate DP Array. */
    dp = calloc(len * len, sizeof(int **) + sizeof(int));
    if (!dp)
        return NULL;
    dplen = (int *)(dp + (len * len));

    /* Get the combinations. */
    arr = compute(input, 0, len -1, returnSize, dp, dplen, len);

    /* Free the DP. */
    for (i = 0; i < len * len; ++i)
        if (i != len - 1 && dp[i])
            free(dp[i]);
    free(dp);
    return arr;
}
#else
/***********************************************************************/
/* compute: Different ways to compute!                                 */
/*                                                                     */
/***********************************************************************/
int *compute(char *exp, int soff, int eoff, int *retsz)
{
    int i, k, j, oper = 0, num1, num2, ocnt = 0, rcnt = 0;
    int *arr, *retarr1 = NULL, *retarr2 = NULL;

    /* Allocate array to store the results. */
    arr = malloc(sizeof(int) * MAX_COMBINATIONS);
    if (!arr)
        return NULL;

    /* Loop evaluating the expression. */
    for (i = soff; i <= eoff; ++i)
    {
        /* If this is an operand, then recursively get all the result
        combinations. */
        if (exp[i] == '*' || exp[i] == '+' || exp[i] == '-')
        {
            retarr1 = compute(exp, soff, i - 1, &num1);
            retarr2 = compute(exp, i + 1, eoff, &num2);
            ocnt++;

            /* If we have combinations, then add them to the array. */
            /* Generate all possible combination results. */
            for (k = 0; k < num1; ++k)
                for (j = 0; j < num2; ++j)
                {
                    /* Avoid overflow. */
                    if ((rcnt == MAX_COMBINATIONS &&
                        !(arr = realloc(arr, sizeof(int) * MAX_COMBINATIONS * 2))) ||
                        rcnt == MAX_COMBINATIONS * 2)
                    {
                        free(arr);
                        return NULL;
                    }

                    /* Evaluate based on the operation. */
                    if (exp[i] == '*')
                        arr[rcnt++] = retarr1[k] * retarr2[j];
                    else if (exp[i] == '+')
                        arr[rcnt++] = retarr1[k] + retarr2[j];
                    else
                        arr[rcnt++] = retarr1[k] - retarr2[j];
                }
            free(retarr1);
            free(retarr2);
        }
        /* If there are no operators, then accumulate the operand. */
        else if (!ocnt && exp[i] >= '0' && exp[i] <= '9')
            oper = oper * 10 + ASCII_TO_INT(exp[i]);
    }

    /* If there were no operators, then assign the operand. */
    if (!ocnt) {
        arr[0] = oper;
        rcnt = 1;
    }

    /* Set the size and return. */
    *retsz = rcnt;
    return arr;
}

/***********************************************************************/
/* Given a string of numbers and operators, return all possible results*/
/* from computing all the different possible ways to group numbers and */
/* operators. The valid operators are +, - and *.                      */
/***********************************************************************/
int* diffWaysToCompute(char* input, int* returnSize)
{
    int len = strlen(input);
    int *arr;

    /* Validate. */
    if (!input || !returnSize)
        return NULL;
    *returnSize = 0;

    /* Get the combinations. */
    arr = compute(input, 0, len - 1, returnSize);
    return arr;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "1-2+3*4-5*6-7+8*9";
    int retsz, i;
    int *arr;

    /* Get the different ways. */
    arr = diffWaysToCompute(s, &retsz);

    for (i = 0; i < retsz; ++i)
        printf("%d, ", arr[i]);

    return 0;
}
