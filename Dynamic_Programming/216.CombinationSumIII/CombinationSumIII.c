/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

/************************************/
/* Macros.                          */
/************************************/
#define MAX_VAL 10
#define MAX_COMBINATIONS 1024

/***********************************************************************/
/* GenCombinations: Generate Combinations!                             */
/*                                                                     */
/***********************************************************************/
void GenCombinations(int s, int tk, int k, int n, int sum, int **res,
                     int *rsize, int *arr, int *csizes)
{
    int i;

    /* Check whether we are done. */
    if (k == tk)
    {
        /* If the sum is equal to the target. then save. */
        if (sum == n)
        {
            int i;

            /* Allocate space for the array. */
            res[*rsize] = malloc(sizeof(int) * k);
            if (!res[*rsize])
                return;
            csizes[*rsize] = k;

            /* Copy contents. */
            for (i = 0; i < k; ++i)
                (res[*rsize])[i] = arr[i];
            /* Increment the return size. */
            (*rsize) += 1;
        }
        return;
    }

    /* Loop attempting different combinations. */
    for (i = s; i < MAX_VAL; ++i)
    {
        /* Save the present value. */
        arr[tk] = i;

        /* Recursively seek the next value. */
        GenCombinations(i + 1, tk + 1, k, n, sum + i, res, rsize, arr,
                        csizes);
    }
}

/***********************************************************************/
/* Find all possible combinations of k numbers that add up to a number */
/* n, given that only numbers from 1 to 9 can be used and each         */
/* combination should be a unique set of numbers.                      */
/*                                                                     */
/* Example 1:                                                          */
/* Input: k = 3, n = 7                                                 */
/* Output:                                                             */
/*                                                                     */
/* [[1,2,4]]                                                           */
/*                                                                     */
/*                                                                     */
/* Example 2:                                                          */
/* Input: k = 3, n = 9                                                 */
/* Output:                                                             */
/*                                                                     */
/* [[1,2,6], [1,3,5], [2,3,4]]                                         */
/***********************************************************************/
int** combinationSum3(int k, int n, int** columnSizes, int* returnSize)
{
    int **res;
    int *arr;

    /* Validate the parameters. */
    if (!returnSize || !columnSizes)
        return NULL;

    /* Allocate space for the combinations and array. */
    res = malloc(sizeof(int *) * MAX_COMBINATIONS);
    if (!res) return NULL;
    *returnSize = 0;

    /* Allocate space for column sizes and temporary stack. */
    *columnSizes = malloc(sizeof(int) * (MAX_COMBINATIONS + k));
    if (!*columnSizes) return res;

    /* Assign the stack. */
    arr = *columnSizes + MAX_COMBINATIONS;

    /* Generate Combinations. */
    GenCombinations(1, 0, k, n, 0, res, returnSize, arr, *columnSizes);
    return res;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int *csize;
    int **res;
    int rsize, k = 3, n = 9, i;

    /* Generate. */
    res = combinationSum3(k, n, &csize, &rsize);

    for (i = 0; i < rsize; ++i)
    {
        printf("%d:", i);
        PrintArray(res[i], csize[i]);
        printf("\n");
    }
    return 0;
}
