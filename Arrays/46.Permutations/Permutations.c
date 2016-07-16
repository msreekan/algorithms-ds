/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* swap_int: Swap integer pointers                                     */
/*                                                                     */
/***********************************************************************/
void swap_int(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

/***********************************************************************/
/* fact: Calculate factorial                                           */
/*                                                                     */
/***********************************************************************/
int fact(int num)
{
    int i, f = 1;
    for (i = 0; i < num; ++i)
        f *= (num - i);
    return f;
}

/***********************************************************************/
/* copy_arr: Copy the generated array                                  */
/*                                                                     */
/***********************************************************************/
int copy_arr(int **arr1, int *arr2, int len)
{
    int i;

    /* Allocate space for the new permutation */
    *arr1 = malloc(sizeof(int) * len);
    if (!*arr1)
      return -1;

    /* Copy contents */
    for (i = 0; i < len; ++i)
        *(*arr1 + i) = arr2[i];
    return 0;
}

/***********************************************************************/
/* genp: Generate permutations                                         */
/*                                                                     */
/***********************************************************************/
int genp(int *a, int len, int poffst, int **arr, int *aoff)
{
    int i = poffst;

    /* Finished generation of one sequence */
    if (poffst == len)
    {
        /* Copy permutation array */
        if (copy_arr(&arr[*aoff], a, len))
            return -1;

        /* Increment the array offset and return */
        (*aoff) += 1;
        return 0;
    }

    /* Loop generating the sequence for this offset location */
    while (i < len)
    {
        /* Pick a new value for the location. */
        swap_int(&a[poffst], &a[i]);

        /* Recursively generate permutations for the remaining
           locations. If the generation fails then return */
        if (genp(a, len, poffst + 1, arr, aoff))
           return -1;

        /* Reverse the change at that index */
        swap_int(&a[poffst], &a[i]);

        /* Assign the new offset */
        i++;
    }

    /* Return success */
    return 0;
}

/***********************************************************************/
/* free_arr: Free the generated array                                  */
/*                                                                     */
/***********************************************************************/
void free_arr(int **arr, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        free(arr[i]);
}

/***********************************************************************/
/* Given a collection of distinct numbers, return all possible         */
/* permutations.                                                       */
/*                                                                     */
/***********************************************************************/
int** permute(int* nums, int numsSize, int* returnSize)
{
    int f, n = numsSize;
    int **arr = NULL;
    int *a = nums;

    /* Maintain sanity */
    *returnSize = 0;
    if (!nums || !numsSize)
        return NULL;

    /* Allocate the return array */
    f = fact(n);
    arr = malloc(sizeof(int *) * f);
    if (!arr)
        return NULL;

    /* Does not matter if this fails, return the array anyway */
    genp(a, n, 0, arr, returnSize);
    return arr;
}

/***********************************************************************/
/* prn_arr: Print array!                                               */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *a, int num)
{
    int i;
    for (i = 0; i < num; ++i)
        printf("%d,", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a1[] = {1, 2, 3}, num, j;
    int a2[] = {3, 3, 0, 3};
    int *a[] = {a1, a2};
    int len[] = {sizeof(a1) / sizeof(int),
                 sizeof(a2) / sizeof(int)};
    int **arr;
    unsigned int i;

    for (i = 0; i < sizeof(a) / sizeof(int *); ++i)
    {
        arr = permute(a[i], len[i], &num);
        for (j = 0; j < num; ++j)
        {
            prn_arr(arr[j], len[i]);
            free(arr[j]);
        }
        free(arr);
    }
    return 0;
}
