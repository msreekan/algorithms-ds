/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*************************************/
/* Queue Data Structure              */
/*************************************/
typedef struct
{
    int *arr;
    int sz;
    int start;
    int end;
    int max;
} Queue;

/***********************************************************************/
/* QInit: Initialize the queue!                                        */
/*                                                                     */
/***********************************************************************/
void *QInit(int sz)
{
    Queue *q;

    /* Allocate memory. */
    q = malloc(sizeof(Queue) + (sizeof(int) * (sz + 1)));
    if (!q)
        return NULL;

    /* Initialize and return. */
    q->arr = (int *)&q[1];
    q->sz = sz  +1;
    q->end = q->start = 0;
    q->max = -1;
    return q;
}

/***********************************************************************/
/* QMax: Get the maximum!                                              */
/*                                                                     */
/***********************************************************************/
int QMax(Queue *q)
{
    return q->arr[q->max];
}

/***********************************************************************/
/* QAdd: Add to the queue!                                             */
/*                                                                     */
/***********************************************************************/
void QAdd(Queue *q, int val)
{
    int i, l;

    /* If there is not space, we need to trim the queue and get
    the new max. */
    if ((q->end + 1) % q->sz == q->start)
    {
        q->start = (q->start + 1) % q->sz; // delete
        /* Find the new max and trim the queue. */
        for (l = i = q->start; i != q->end; i = (i + 1) % q->sz)
            l = (q->arr[l] <= q->arr[i]) ? i : l;
        q->max = q->start = l;
    }

    /* If the new value is greater than max, then delete all entries. */
    if (q->max == -1 || val >= q->arr[q->max])
        q->max = q->start = q->end;

    /* Add the new value. */
    q->arr[q->end] = val;
    q->end = (q->end + 1) % q->sz;
}

/***********************************************************************/
/* Given an array nums, there is a sliding window of size k which is   */
/* moving from the very left of the array to the very right. You can   */
/* only see the k numbers in the window. Each time the sliding window  */
/* moves right by one position.                                        */
/* For example:                                                        */
/* https://leetcode.com/problems/sliding-window-maximum/#/description  */
/***********************************************************************/
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    void *q;
    int *arr;
    int i, l = 0;

    /* Validate the parameters. */
    if (!nums || numsSize <= 0 || k <= 0 || !returnSize)
        return NULL;

    /* Initialize the queue. */
    q = QInit(k);
    if (!q) return NULL;

    /* Allocate the return arry. */
    arr = malloc(sizeof(int) * numsSize - (k - 1));
    if (!arr)
        return NULL;

    /* Queue the elements while picking the maximum. */
    for (i = 0; i < numsSize; ++i)
    {
        QAdd(q, nums[i]);
        if (i >= k - 1)
            arr[l++] = QMax(q);
    }
    *returnSize = l;

    /* Delete the Q. */
    free(q);
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int a[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    #elif 1
    int a[] = {2, -1, -4, 1, -4, -1, 1, 2, 2, 3, 3, 9};
    int k = 3;
    #endif

    int len = sizeof(a) / sizeof(int), ret, i;
    int *arr;

    arr = maxSlidingWindow(a, len, k, &ret);
    for (i = 0; i < ret; ++i)
        printf("%d ", arr[i]);
    free(arr);
    return 0;
}
