/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***************************************/
/* Interval data structure             */
/***************************************/
struct Interval
{
    int start;
    int end;
};

/***********************************************************************/
/* copy_interval: Copy interval                                        */
/*                                                                     */
/***********************************************************************/
void copy_interval(struct Interval* it1, struct Interval* it2)
{
    it1->start = it2->start;
    it1->end = it2->end;
}

/***********************************************************************/
/* insert: Insert interval                                             */
/*                                                                     */
/***********************************************************************/
struct Interval* insert(struct Interval* intervals, int intervalsSize,
                        struct Interval newInterval, int* returnSize)
{
    struct Interval *it = intervals, *nt = &newInterval;
    int len = intervalsSize, i, j;
    struct Interval *nit;

    /* Allocate space */
    nit = malloc(sizeof(struct Interval) * (len + 1));
    if (!nit)
        return NULL;

    /* Seek the interval start location. Also, while we are at it,
       copy the contents to the new array */
    for(i = 0; (i < len) && (it[i].end < nt->start); ++i)
        copy_interval(&nit[i], &it[i]);

    /* Traverse the array from the end seeking the interval
       end location */
    for (j = len - 1; j >= 0 && it[j].start > nt->end; --j);

    /* If there is a need to merge the ranges, then do the same. */
    if (j >= i)
    {
        /* Pick the smaller start offset */
        nt->start = (i < len && it[i].start > nt->start) ?
                     nt->start : it[i].start;

        /* Pick the greater end offset */
        nt->end = (j >= 0 && j < len && it[j].end > nt->end) ?
                   it[j].end : nt->end;
    }

    /* Update the offsets and copy the remaining elements */
    j = (j < i) ? i : j + 1;
    copy_interval(&nit[i++], nt);
    while (j < len)
        copy_interval(&nit[i++], &it[j++]);

    /* Set the return size */
    *returnSize = i;
    return nit;
}

/***********************************************************************/
/* prn_intervals: Print intervals!                                     */
/*                                                                     */
/***********************************************************************/
void prn_intervals(struct Interval *inval, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("[%d, %d], ", inval[i].start, inval[i].end);
    printf("\n");
}


/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct Interval intval1[] = {{1, 2}, {3, 5}, {6, 7}, {8, 10},
                                 {12, 16}};
    struct Interval nintval1 = {4, 9};
    struct Interval intval2[] = {{1, 3}, {6, 9}};
    struct Interval nintval2 = {2, 5};
    struct Interval intval3[] = {{1, 3}, {6, 9}};
    struct Interval nintval3 = {4, 5};
    struct Interval intval4[] = {{1, 5}};
    struct Interval nintval4 = {2, 3};
    int len1 = sizeof(intval1) / sizeof(struct Interval), retlen, i;
    int len2 = sizeof(intval2) / sizeof(struct Interval);
    int len3 = sizeof(intval3) / sizeof(struct Interval);
    int len4 = sizeof(intval4) / sizeof(struct Interval);
    int len[] = {len1, len2, len3, len4};
    struct Interval *intval[] = { intval1, intval2, intval3, intval4};
    struct Interval *nintval[] = { &nintval1, &nintval2, &nintval3, &nintval4};
    struct Interval *retval;
    int intlen = sizeof(intval) / sizeof(struct Interval *);

    for (i = 0; i < intlen; ++i)
    {
        printf("Intervals and new interval:\n");
        prn_intervals(intval[i], len[i]);
        prn_intervals(nintval[i], 1);
        retval = insert(intval[i], len[i], *nintval[i], &retlen);

        printf("Merged intervals:\n");
        prn_intervals(retval, retlen);
        printf("\n\n");
        free(retval);
    }
    return 0;
}
