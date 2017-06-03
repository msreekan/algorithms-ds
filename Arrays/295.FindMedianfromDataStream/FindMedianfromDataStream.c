/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************/
/* Macros                    */
/*****************************/
#define HEAP_SZ       1024
#define HEAP_LARGEST  1
#define HEAP_SMALLEST 0

/*****************************/
/* Heap structure            */
/*****************************/
struct heap
{
    int *arr;  // heap array
    int plen;  // present length
    int mlen;  // maximum length
    int order; // 1 for largest on top, else 0
};

/***********************************************************************/
/* SwapInt: Swap pointers!                                             */
/*                                                                     */
/***********************************************************************/
inline void SwapInt(int *val1, int *val2)
{
    int t = *val1;
    *val1 = *val2;
    *val2 = t;
}

/***********************************************************************/
/* HeapInit: Initialize the heap!                                      */
/*                                                                     */
/***********************************************************************/
void *HeapInit(int order)
{
    struct heap *h;

    /* Allocate the heap. */
    if (!(h = malloc(sizeof(struct heap))) ||
        !(h->arr = malloc(sizeof(int) * HEAP_SZ)))
    {
        if (h) free(h);
        return NULL;
    }

    /* Initizlize the values. */
    h->plen = 0;
    h->mlen = HEAP_SZ;
    h->order = order;
    return h;
}

/***********************************************************************/
/* HeapAdd: Add to the heap!                                           */
/*                                                                     */
/***********************************************************************/
void HeapAdd(struct heap *h, int val)
{
    int p, c1, c;

    /* If we do not have space, then realloc.*/
    if (h->plen == h->mlen)
    {
        if (!(h->arr = realloc(h->arr, (sizeof(int) * (h->mlen << 1)))))
            return;
        h->mlen <<= 1;
    }
    /* Add the value to the heap. */
    h->arr[h->plen] = val;

    /* Sift up the new entry. */
    p = (h->plen - 1) / 2;
    while (p >= 0)
    {
        /* Calculate the offset of the two children. */
        c = p * 2 + 1;
        c1 = p * 2 + 2;

        /* Pick the replacement. */
        if (c1 <= h->plen && c <= h->plen &&
           ((h->order == HEAP_LARGEST && h->arr[c1] > h->arr[c]) ||
            (h->order == HEAP_SMALLEST && h->arr[c1] < h->arr[c])))
            c = c1;

        /* Swap. */
        if (c <= h->plen &&
            ((h->order == HEAP_LARGEST && h->arr[c] > h->arr[p]) ||
             (h->order == HEAP_SMALLEST && h->arr[c] < h->arr[p])))
            SwapInt(&h->arr[p], &h->arr[c]);
        /* Else we are done. */
        else
            break;
        /* Move to the parent. */
        p = (p - 1) / 2;
    }
    /* Increment the size. */
    h->plen++;
}

/***********************************************************************/
/* HeapDel: Delete from the heap!                                      */
/*                                                                     */
/***********************************************************************/
void HeapDel(struct heap *h, int *val)
{
    int p = 0, c, c1;

    /* Ensure there are elements. */
    if (!h->plen)
        return;

    /* Select the root for deletion. */
    *val = h->arr[0];

    /* Replace with the last element. */
    h->arr[p] = h->arr[--h->plen];

    /* Sift down the new value. */
    while (p < h->plen)
    {
        /* Pick the children. */
        c = p * 2 + 1;
        c1 = p * 2 + 2;

         /* Pick the replacement. */
        if (c1 <= h->plen && c <= h->plen &&
           ((h->order == HEAP_LARGEST && h->arr[c1] > h->arr[c]) ||
            (h->order == HEAP_SMALLEST && h->arr[c1] < h->arr[c])))
            c = c1;

        /* Swap. */
        if (c < h->plen &&
            ((h->order == HEAP_LARGEST && h->arr[c] > h->arr[p]) ||
             (h->order == HEAP_SMALLEST && h->arr[c] < h->arr[p])))
            SwapInt(&h->arr[p], &h->arr[c]);
        p = c; // move to the child
    }
}

/***********************************************************************/
/* HeapFree: Free the heap!                                            */
/*                                                                     */
/***********************************************************************/
void HeapFree(struct heap *h)
{
    free(h->arr);
    free(h);
}

/***********************************************************************/
/* HeapSz: Returns the present heap size!                              */
/*                                                                     */
/***********************************************************************/
int HeapSz(struct heap *h)
{
    return h->plen;
}

/***********************************************************************/
/* HeapTop: Returns the present heap top!                              */
/*                                                                     */
/***********************************************************************/
int HeapTop(struct heap *h, int *val)
{
    int ret = h->plen ? 1 : 0;

    /* If there are elements in the array, then set the value to the
    top. */
    if (h->plen)
        *val = h->arr[0];
    return ret;
}

/***********************************************************************/
/* Median is the middle value in an ordered integer list. If the size  */
/* of the list is even, there is no middle value. So the median is the */
/* mean of the two middle value.                                       */
/*                                                                     */
/* Examples:                                                           */
/* [2,3,4] , the median is 3                                           */
/* [2,3], the median is (2 + 3) / 2 = 2.5                              */
/*                                                                     */
/* Design a data structure that supports the following two operations: */
/*                                                                     */
/* void addNum(int num) - Add a integer number from the data stream to */
/*                       the data structure.                           */
/* double findMedian() - Return the median of all elements so far.     */
/***********************************************************************/
typedef struct {
    void *heap1;
    void *heap2;
} MedianFinder;

/***********************************************************************/
/* Initialize your data structure here.                                */
/*                                                                     */
/***********************************************************************/
MedianFinder* medianFinderCreate()
{
    MedianFinder *m;

    /* Allocate memory. Initialize heaps. */
    if (!(m = malloc(sizeof(MedianFinder))) ||
        !(m->heap1 = HeapInit(HEAP_LARGEST)) ||
        !(m->heap2 = HeapInit(HEAP_SMALLEST)))
    {
        /* Wind up the allocations. */
        if (m && m->heap1)
            HeapFree(m->heap1);
        if (m)
            free(m);
        m = NULL;
    }

    /* Return a handle. */
    return m;
}

/***********************************************************************/
/* medianFinderAddNum : Add number to the structure                    */
/*                                                                     */
/***********************************************************************/
void medianFinderAddNum(MedianFinder* obj, int num)
{
    int top;
    struct heap *h;

    /* If first heap is free or if the value is less than the
    top, then add .*/
    if (!HeapTop(obj->heap1, &top) || top >= num)
        HeapAdd(obj->heap1, num);
    /* Else add to the second heap. */
    else
        HeapAdd(obj->heap2, num);

    /* Balance the two heaps. The difference between the number of
       elements in these heaps cannot exceed 1. */
    if (abs(HeapSz(obj->heap1) - HeapSz(obj->heap2)) > 1)
    {
        /* Pick the heap with more elements. */
        h = HeapSz(obj->heap1) > HeapSz(obj->heap2) ?
            obj->heap1 : obj->heap2;

        /* Delete the top element from the larger heap. */
        HeapDel(h, &top);

        /* Push the value into the other heap. */
        h = obj->heap1 == h ? obj->heap2 : obj->heap1;
        HeapAdd(h, top);
    }
}

/***********************************************************************/
/* medianFinderFindMedian: Get the median.                             */
/*                                                                     */
/***********************************************************************/
double medianFinderFindMedian(MedianFinder* obj)
{
    int n1 = HeapSz(obj->heap1), n2 = HeapSz(obj->heap2);
    int top1, top2;
    double val;

    /* If the heaps do not have equal number of elements, then pick
       the larger one. */
    if (n1 != n2)
    {
        /* Get the top value from the largr heap. */
        if (n1 > n2)
            HeapTop(obj->heap1, &top1);
        else
            HeapTop(obj->heap2, &top1);
        val = top1;
    }

    /* Else do an average of the top values. */
    else
    {
        HeapTop(obj->heap1, &top1);
        HeapTop(obj->heap2, &top2);
        val = ((double)top1 + (double)top2) / 2;
    }

    /* Return the median. */
    return val;
}

/***********************************************************************/
/* medianFinderFree: Free the median structure.                        */
/*                                                                     */
/***********************************************************************/
void medianFinderFree(MedianFinder* obj)
{
    HeapFree(obj->heap1);
    HeapFree(obj->heap2);
    free(obj);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
