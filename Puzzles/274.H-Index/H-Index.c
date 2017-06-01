/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of citations (each citation is a non-negative        */
/* integer) of a researcher, write a function to compute the           */
/* researcher's h-index.                                               */
/* According to the definition of h-index on Wikipedia: "A scientist   */
/* has index h if h of his/her N papers have at least h citations each,*/
/* and the other N − h papers have no more than h citations each."     */
/* For example, given citations = [3, 0, 6, 1, 5], which means the     */
/* researcher has 5 papers in total and each of them had received 3, 0,*/
/* 6, 1, 5 citations respectively. Since the researcher has 3 papers   */
/* with at least 3 citations each and the remaining two with no more   */
/* than 3 citations each, his h-index is 3.                            */
/* Note: If there are several possible values for h, the maximum one is*/
/* taken as the h-index.                                               */
/***********************************************************************/
int hIndex(int* cts, int ctsz)
{
    int i, sum;
    int *c;

    /* Allocate space for counting the citations. */
    c = calloc((ctsz + 2), sizeof(int));
    if (!c) return 0;

    /* Count the elements in the bucket. H-Index cannot be
    greater than the number of papers or less than than 1.
    We divide the papers into 'n + 1' buckets, every paper with
    more than n citations would go into bucket 'n + 1'.
    */
    for (i = 0; i < ctsz; ++i)
        c[cts[i] > ctsz ? ctsz + 1 : cts[i]]++;

    /* Get the H- Index. Scanning the buckets in reverse
    looking for the condition paper count greater than or
    equal to citation count gives the H-Index.*/
    sum = c[ctsz + 1];
    for (i = ctsz; i > 0; --i) {
        sum += c[i];
        if (sum >= i) break;
    }

    /* Free the memory. */
    free(c);
    return i;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 6, 7, 100, 101};
    int len = sizeof(a) / sizeof(int);
    printf("H- Index = %d :\n", hIndex(a, len));
    return 0;
}
