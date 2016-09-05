/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*************************************/
/* Macros                            */
/*************************************/
#define SET_SZ (2 * 1024)

/***********************************************************************/
/* get_pivot: Get pivot!                                               */
/*                                                                     */
/***********************************************************************/
int get_pivot(int *a, int s, int e)
{
    int i = s, j = e - 1, pivot = e, t;

    /* Loop seeking the pivot */
    while (i <= j)
    {
        while (i < e && a[i] <= a[pivot])
            i++;

        while (j >= s && a[j] > a[pivot])
            j--;

        /* Swap only if i < j */
        if (i < j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    /* Swap pivot into place */
    t = a[i];
    a[i] = a[pivot];
    a[pivot] = t;
    return i;
}

/***********************************************************************/
/* quick_sort: Quick sort!                                             */
/*                                                                     */
/***********************************************************************/
void quick_sort(int *a, int s, int e)
{
    int pivot;
    if (s >= e)
        return;
    pivot = get_pivot(a, s, e);
    quick_sort(a, s, pivot - 1);
    quick_sort(a, pivot + 1, e);
}

/***********************************************************************/
/* gen_sets: Generate sets!                                            */
/*                                                                     */
/***********************************************************************/
void gen_sets(int *arr, int alen, int *nums, int off, int len,
              int **sets, int *csizes, int *retsize)
{
    int i;

    /* Avoid overflows */
    if (*retsize == SET_SZ)
        exit(-1);

    /* Save the generated set */
    sets[*retsize] = malloc(sizeof(int) * alen);
    if(!sets[*retsize])
        return;
    for (i = 0; i < alen; ++i)
        *(sets[*retsize] + i) = arr[i];
    csizes[*retsize] = alen;
    (*retsize) += 1;

    /* Continue set generation */
    i = off;
    while (i < len)
    {
        /* Recursively generate the next set. */
        arr[alen] = nums[i];
        gen_sets(arr, alen + 1, nums, ++i, len, sets, csizes, retsize);

        /* Avoid duplicates */
        while(i < len && (nums[i - 1] == nums[i]))
            ++i;
    }
}

/***********************************************************************/
/* Given a collection of integers that might contain duplicates, nums, */
/*                                                                     */
/* return all possible subsets.                                        */
/*                                                                     */
/* Note: The solution set must not contain duplicate subsets.          */
/*                                                                     */
/* For example,                                                        */
/* If nums = [1,2,2], a solution is:                                   */
/* [                                                                   */
/*  [2],                                                               */
/*  [1],                                                               */
/*  [1,2,2],                                                           */
/*  [2,2],                                                             */
/*  [1,2],                                                             */
/*  []                                                                 */
/* ]                                                                   */
/***********************************************************************/
int** subsetsWithDup(int* nums, int numsz, int** csizes, int* retsize)
{
    int **sets;
    int *arr;

    /* Sort */
    quick_sort(nums, 0, numsz - 1);

    /* Allocate space for column sizes and sets */
    *csizes = malloc(sizeof(int) * (SET_SZ + numsz));
    if (!*csizes)
        return NULL;
    arr = *csizes + SET_SZ; // temporary array
    *retsize = 0;

    /* Sets */
    sets = malloc(sizeof(int *) * SET_SZ);
    if (!sets)
    {
        free(*csizes);
        return NULL;
    }

    /* Generate sets */
    gen_sets(arr, 0, nums, 0, numsz, sets, *csizes, retsize);
    return sets;
}

/***********************************************************************/
/* prn_arr: Print array!                                               */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *arr, int len)
{
    int i;
    printf("[");
    for (i = 0; i < len - 1; ++i)
        printf("%d, ", arr[i]);
    if (len)
        printf("%d", arr[i]);
    printf("]\n");
    free(arr);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 2, 2, 1};
    int len = sizeof(a) / sizeof(int), ret_sz = 0, i;
    int **sets;
    int *csizes = NULL;
    sets = subsetsWithDup(a, len, &csizes, &ret_sz);
    for (i = 0; i < ret_sz; ++i)
        prn_arr(sets[i], csizes[i]);
    free(sets);
    free(csizes);
    return 0;
}
