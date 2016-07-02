/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SOL_SZ 1024

/********************************/
/* Stack                        */
/********************************/
struct stack
{
    int *s;
    int sz;
    int top;
};

/***********************************************************************/
/* spush: Stack push                                                   */
/*                                                                     */
/***********************************************************************/
int spush(struct stack *s, int val)
{
    /* Avoid stack overflow */
    if (s->top == s->sz)
        return -1;

    /* Push the value */
    s->s[s->top] = val;
    s->top++;
    return 0;
}

/***********************************************************************/
/* spop: Stack pop                                                     */
/*                                                                     */
/***********************************************************************/
int spop(struct stack *s)
{
    /* Avoid stack underflow */
    if (s->top == 0)
        return -1;

    /* Pop the value */
    s->top--;
    return s->s[s->top];
}

/***********************************************************************/
/* scopy: Copy the stack contents into another buffer                  */
/*                                                                     */
/***********************************************************************/
int *scopy(struct stack *s, int *sz)
{
    int i;
    int *mem;

    /* Check for stack empty case */
    if (s->top == 0)
        return NULL;

    /* Allocate the buffer */
    mem = malloc(sizeof(int) * s->top);
    if (!mem)
        return NULL;

    /* Copy the contents */
    for (i = 0; i < s->top; ++i)
        mem[i] = s->s[i];

    /* Assign the size */
    *sz = s->top;

    /* Return the buffer */
    return mem;
}

/***********************************************************************/
/* swap_int: Swap integer pointers                                     */
/*                                                                     */
/***********************************************************************/
void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/***********************************************************************/
/* get_pivot: Get the pivot                                            */
/*                                                                     */
/***********************************************************************/
int get_pivot(int *a, int s, int e)
{
    int i = s, j = e - 1, pivot = e;

    /* Swap the center element into the pivot */
    swap_int(&a[s + ((e - s) / 2)], &a[pivot]);

    /* Loop to place the pivot element in the correct
       location */
    while (i <= j)
    {
        /* Scan for the first element greater than pivot */
        while ((i < e) && (a[i] <= a[pivot]))
            ++i;

        /* Scan for the first element from the back which is
        less than pivot */
        while ((j >= 0) && (a[j] > a[pivot]))
            --j;

        /* Swap the elements */
        if (i < j)
            swap_int(&a[i], &a[j]);
    }

    /* Swap the pivot value into its place and return */
    swap_int(&a[i], &a[pivot]);
    return i;
}

/***********************************************************************/
/* quick_sort: Quick Sort                                              */
/*                                                                     */
/***********************************************************************/
void quick_sort(int *a, int s, int e)
{
    int pivot;

    /* Terminating condition */
    if (s >= e)
        return;

    /* Get the pivot */
    pivot = get_pivot(a, s, e);

    /* Recursively sort the sub-arrays */
    quick_sort(a, s, pivot - 1);
    quick_sort(a, pivot + 1, e);
}

/***********************************************************************/
/* gen_combinations: Generate the combinations                         */
/*                                                                     */
/***********************************************************************/
int gen_combinations(int *a, int offst, int alen, int psum, int target,
                     int **sol, int *cs, int *scount, struct stack *s)
{
    int i = offst;

    /* If we have a solution, then save the array */
    if (psum == target)
    {
        int sz;

        /* Cannot exceed the allocated memory */
        if (*scount >= MAX_SOL_SZ)
            return -1;

        /* Get the buffer pointer with the stack contents */
        sol[*scount] = scopy(s, &sz);
        if (!sol[*scount])
            return -1;

        /* Save the size of the array */
        cs[*scount] = sz;

        /* Increment the size of the solution count */
        *scount += 1;

        /* Return success */
        return 0;
    }

    /* Loop while generating the combinations */
    while(i < alen)
    {
        /* Increase the sum */
        psum += a[i];

        /* If the sum exceeds the target, then return */
        if (psum > target)
            return 0;

        /* Push the value into the stack */
        if (spush(s, a[i]))
            return -1;

        /* Continue generating combinations */
        if (gen_combinations(a, i, alen, psum, target, sol, cs, scount, s))
            return -1;

        /* Decrease the sum */
        psum -= a[i];

        /* Pop the value from the stack */
        if (spop(s) == -1)
            return -1;

        /* Figure out the next value */
        do
            ++i;
        while ((i < alen) && (a[i - 1] == a[i]));
    }

    /* Done */
    return 0;
}

/***********************************************************************/
/* Given a set of candidate numbers (C) and a target number (T), find  */
/* all unique combinations in C where the candidate numbers sums to T. */
/*                                                                     */
/* The same repeated number may be chosen from C unlimited number of   */
/* times.                                                              */
/*                                                                     */
/* Note:                                                               */
/*                                                                     */
/* •All numbers (including target) will be positive integers.          */
/* •The solution set must not contain duplicate combinations.          */
/*                                                                     */
/* For example, given candidate set [2, 3, 6, 7] and target 7,         */
/* A solution set is:                                                  */
/* [                                                                   */
/*  [7],                                                               */
/*  [2, 2, 3]                                                          */
/* ]                                                                   */
/***********************************************************************/
int** combinationSum(int* candidates, int candidatesSize, int target,
                     int** columnSizes, int* returnSize)
{
    struct stack s = {NULL, 0, 0};
    int **sol;
    int scount = 0, cs = candidatesSize, i;
    int *c = candidates;

    /* Validate the parameters */
    if (!c || !cs || !target)
        return NULL;

    /* Initialize to zero */
    *returnSize = 0;

    /* Sort the candidates */
    quick_sort(c, 0, cs - 1);

    /* If the target is smaller than the smallest element in the
       array, then return */
    if (candidates[0] > target)
        return NULL;

    /* Calculate the maximum possible size of the column array,
       allocate the stack */
    s.sz = (target / c[0]) + 1;
    s.s = malloc(sizeof(int) * s.sz);
    if (!s.s)
        return NULL;

    /* Allocate memory for the pointer array */
    sol = malloc(sizeof(int *) * MAX_SOL_SZ);
    *columnSizes = malloc(sizeof(int) * MAX_SOL_SZ);

    /* If there was a failure, then return error */
    if (gen_combinations(c, 0, cs, 0, target, sol, *columnSizes, &scount,
                         &s))
    {
        /* Free all the allocated arrays */
        for (i = 0; i < scount; ++i)
            free(sol[i]);

        /* Free the array pointers */
        free(sol);
        free(*columnSizes);
        free(s.s);
        *columnSizes = 0;
        return NULL;
    }

    /* Assign the array size and return */
    free(s.s);
    *returnSize = scount;
    return sol;
}

/***********************************************************************/
/* prn_arr: Print the array!                                           */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *a, int len)
{
   int i;
   for (i = 0; i < len - 1; ++i)
        printf("%d, ", a[i]);
   printf("%d\n", a[i]);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2, 3, 6, 7};
    int len = sizeof(a) / sizeof(int), t = 7, retSize, i;
    int a1[] = {8, 7, 4, 3};
    int len1 = sizeof(a1) / sizeof(int), t1 = 11;
    int **s, *alen;

    printf("\nCombination Sum:");
    prn_arr(a, len);
    printf("Target = %d\n", t);
    s = combinationSum(a, len, t, &alen, &retSize);
    if (s)
    {
        /* Loop through all the entries printing each column */
        for (i = 0; i < retSize; ++i)
        {
            /* Print the column */
            prn_arr(s[i], alen[i]);

            /* Free the array */
            free(s[i]);
        }

        free(s);
        free(alen);
    }

    printf("\nCombination Sum:");
    prn_arr(a1, len1);
    printf("Target = %d\n", t1);
    s = combinationSum(a1, len1, t1, &alen, &retSize);
    if (s)
    {
        /* Loop through all the entries printing each column */
        for (i = 0; i < retSize; ++i)
        {
            /* Print the column */
            prn_arr(s[i], alen[i]);

            /* Free the array */
            free(s[i]);
        }

        free(s);
        free(alen);
    }
    return 0;
}
