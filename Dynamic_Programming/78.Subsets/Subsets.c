/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ENTRY_COUNT (8 * 1024)

/***********************************************************************/
/* subsetc: Create subsets!                                            */
/*                                                                     */
/***********************************************************************/
void subsetc(int *arr, int *nums, int **sets, int offst, int alen,
             int size, int** columnSizes, int *rsize)
{
    int i;

    /* Allocate space for the subset */
    sets[*rsize] = malloc(sizeof(int) * alen);
    if (!sets[*rsize])
        exit(-1);

    /* Copy the values */
    for (i = 0; i < alen; ++i)
        *(sets[*rsize] + i) = arr[i];
    (*columnSizes)[*rsize] = alen;
    (*rsize)++;

    /* Loop through the values picking one at a time */
    for (i = offst; i < size; ++i)
    {
        arr[alen] = nums[i];
        subsetc(arr, nums, sets, i + 1, alen + 1, size, columnSizes,
                rsize);
    }
}

/***********************************************************************/
/*Given a set of distinct integers, nums, return all possible subsets. */
/*                                                                     */
/* Note: The solution set must not contain duplicate subsets.          */
/*                                                                     */
/* For example,                                                        */
/* If nums = [1,2,3], a solution is:                                   */
/* [                                                                   */
/*  [3],                                                               */
/*  [1],                                                               */
/*  [2],                                                               */
/*  [1,2,3],                                                           */
/*  [1,3],                                                             */
/*  [2,3],                                                             */
/*  [1,2],                                                             */
/*  []                                                                 */
/*]                                                                    */
/***********************************************************************/
int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize)
{
    int **sets;
    int *arr;

    /* Allocate the space for array */
    sets = malloc(sizeof(int *) * ENTRY_COUNT);
    if (!sets)
        return NULL;

    /* Allocate memory for column size array */
    *columnSizes = malloc(sizeof(int) * ENTRY_COUNT);
    if (!*columnSizes)
    {
        free(sets);
        return NULL;
    }

    /* Allocate space for array */
    arr = malloc(sizeof(int) * numsSize);
    if (!arr)
    {
        free(sets);
        free(columnSizes);
        return NULL;
    }

    /* Generate subsets */
    *returnSize = 0;
    subsetc(arr, nums, sets, 0, 0, numsSize, columnSizes, returnSize);
    free(arr);
    return sets;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {1, 2, 3};
    int i, j, **sets, *csizes, rets;
    unsigned int len = sizeof(arr) / sizeof(int);
    sets = subsets(arr, len, &csizes, &rets);
    for (i = 0; i < rets; ++i)
    {
        printf("[");
        for (j = 0; j < csizes[i] - 1; ++j)
            printf("%d, ", *(sets[i] + j));
        if (j < csizes[i]) printf("%d", *(sets[i] + j));
        printf("]\n");
        free(sets[i]);
    }
    free(csizes);
    return 0;
}
