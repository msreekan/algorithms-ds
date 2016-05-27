#include <stdio.h>
#include <stdlib.h>

/********************************/
/* Interval                     */
/********************************/
struct Interval
{
    int start;
    int end;
};

/********************************/
/* Stack                        */
/********************************/
 struct stack
{
    struct Interval *si;
    int top;
    int sz;
};

/***********************************************************************/
/* spush: Push                                                         */
/*                                                                     */
/***********************************************************************/
int spush(struct stack *s, struct Interval *it)
{
    if (s->top >= s->sz)
        return -1;

    s->si[s->top].start = it->start;
    s->si[s->top].end = it->end;
    s->top++;
    return 0;
}

/***********************************************************************/
/* spop: Pop the stack                                                 */
/*                                                                     */
/***********************************************************************/
int spop(struct stack *s, struct Interval *it)
{
    if (s->top == 0)
        return 0;
    s->top--;
    it->start = s->si[s->top].start;
    it->end = s->si[s->top].end;
    return 1;
}

/***********************************************************************/
/* swap_interval: Swap interval structures                             */
/*                                                                     */
/***********************************************************************/
void swap_interval(struct Interval* it1, struct Interval* it2)
{
    struct Interval it = *it1;
    it1->start =  it2->start;
    it1->end =  it2->end;
    it2->start =  it.start;
    it2->end =  it.end;
}

/***********************************************************************/
/* get_pivot: Get pivot                                                */
/*                                                                     */
/***********************************************************************/
int get_pivot(struct Interval* itvl, int start, int end)
{
    int pivot = end;
    int i = start, j = end - 1;

    /* Pick the center as the pivot */
    swap_interval(&itvl[(start + ((end - start) / 2))], &itvl[end]);

    /* Partition the array */
    while (i <= j)
    {
        /* Find the first element greater than pivot */
        while ((i < end) && (itvl[i].start <= itvl[pivot].start))
            i++;

        /* Find the first element smaller than pivot */
        while ((j >= start) && (itvl[j].start > itvl[pivot].start))
            j--;

        /* Swap */
        if (i < j)
            swap_interval(&itvl[i], &itvl[j]);
    }
    /* Place the pivot into place */
    swap_interval(&itvl[i], &itvl[pivot]);
    return i;
}

/***********************************************************************/
/* quick_sort: Quick sort                                              */
/*                                                                     */
/***********************************************************************/
void quick_sort(struct Interval* itvl, int start, int end)
{
    int pivot;

    /* Recursion ends */
    if (start > end)
        return;

    /* Get pivot */
    pivot = get_pivot(itvl, start, end);

    /* Quick sort */
    quick_sort(itvl, start, pivot - 1);
    quick_sort(itvl, pivot + 1, end);
}

/***********************************************************************/
/* check_interval: Check if the array is already sorted                */
/*                                                                     */
/***********************************************************************/
int check_interval(struct Interval* itvl, int len)
{
    int i;
    for (i = 1 ; i < len; ++i)
    {
        if (itvl[i - 1].start > itvl[i].start)
            return 0;
    }
    return 1;
}

/***********************************************************************/
/* Given a collection of intervals, merge all overlapping intervals.   */
/* For example,                                                        */
/* Given [1,3],[2,6],[8,10],[15,18],                                   */
/* return [1,6],[8,10],[15,18].                                        */
/***********************************************************************/
struct Interval* merge(struct Interval* intervals, int intervalsSize,
                       int* returnSize)
{
    int i, len = intervalsSize;
    struct stack s = {NULL, 0, len};
    struct Interval itemp;

    /* Maintain sanity */
    if (!intervals || !intervalsSize || !returnSize)
        return NULL;

    /* Check if the array needs sorting */
    if (!check_interval(intervals, len))
        quick_sort(intervals, 0, len - 1);

    /* Allocate the stack */
    s.si = malloc(sizeof(struct Interval) * len);
    if(s.si == NULL)
        goto err_exit;

    /* Push the first interval onto the stack */
    if (spush(&s, &intervals[0]) == -1)
        goto err_exit;

    /* Save the stack top */
    itemp.start = intervals[0].start;
    itemp.end = intervals[0].end;

    /* Loop merging the intervals */
    for (i = 1; i < len; ++i)
    {
        /* If needed, merge the interval */
        if ((itemp.end >= intervals[i].start) && (intervals[i].end > itemp.end))
        {
            /* Stack POP */
            if (!spop(&s, &itemp))
                goto err_exit;

            /* Update the end, and push */
            itemp.end = intervals[i].end;
            if (spush(&s, &itemp) == -1)
                goto err_exit;
        }

        /* Else merely push the interval into the stack */
        else if (itemp.end < intervals[i].start)
        {
            if (spush(&s, &intervals[i]) == -1)
                goto err_exit;
            itemp.start = intervals[i].start;
            itemp.end = intervals[i].end;
        }
    }

    /* Size of the merged intervals */
    *returnSize = s.top;
    return s.si;

    /* Error */
err_exit:
    if (s.si)
        free(s.si);
    return NULL;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct Interval it[] = { {2, 3}, {2, 2}, {3, 3}, {1, 3}, {5, 7}, {2, 2}, {4, 6 }};
    struct Interval *ri;
    int len = sizeof(it) / sizeof(struct Interval), ri_len = 0, i;

    ri = merge(&it[0], len, &ri_len);
    if (!ri || !ri_len)
        exit(-1);

    for (i = 0; i < ri_len; ++i)
        printf("[%d, %d] ", ri[i].start, ri[i].end);
    printf("\n");
    free(ri);
    return 0;
}

