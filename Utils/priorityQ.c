/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityQ.h"

/******************************************/
/* Macros                                 */
/******************************************/
#define INT_MIN -0x7FFFFFFF

/******************************************/
/* Data Structures                        */
/******************************************/
struct PQNode
{
    int priority;
    void *buf;   // buffer pointer
};

/*
** Priority Queue Handle
*/
struct PQueue
{
    int tlen;             // total heap length
    int plen;             // present heap count
    int esize;            // entry size
    struct PQNode *heap;  // array implementation
    unsigned char *buf;   // buffer
    int (*pcb)(void *);   // app callback to get priority
};

/***********************************************************************/
/* PQAlloc: Initialize a priority queue!                               */
/*                                                                     */
/***********************************************************************/
void *PQAlloc(int len, int esize, int (*pcb)(void *))
{
    struct PQueue *pq = NULL;
    int i;

    /* Validate the inputs */
    if (len < 1 || esize < 1 || !pcb)
        return NULL;

    /* Allocate the priority queue structure and the buffers. */
    if (!(pq = malloc(sizeof(struct PQueue))) ||
        !(pq->heap = malloc((sizeof(struct PQNode) * len) +
                            (esize * len))))
    {
        /* If priority Q is valid, then heap allocation failed */
        if (pq) free(pq->heap);
        return NULL;
    }

    /* Initialize the fields */
    pq->tlen = len;
    pq->plen = 0;
    pq->esize = esize;
    pq->pcb = pcb;
    pq->buf = (unsigned char *)(pq->heap + len);
    for (i = 0; i < len; ++i) {
        pq->heap[i].priority = INT_MIN;
        pq->heap[i].buf = &pq->buf[i * pq->esize];
    }

    /* Return the handle */
    return pq;
}

/***********************************************************************/
/* AddToPriorityQ: Add an element to the priority queue!               */
/*                                                                     */
/***********************************************************************/
int AddToPQ(void *handle, void *buf)
{
    struct PQueue *pq = handle;
    int off = 0, c1, c2, c, tlen = pq ? pq->tlen : 0, priority;
    int (*pcb)(void *) = pq ? pq->pcb : NULL;
    struct PQNode *heap = pq ? pq->heap : NULL;
    void *tptr;

    /* Validate */
    if (!handle || !buf)
        return -1;

    /* Update the length */
    if (pq->plen < pq->tlen)
        pq->plen += 1;

    /* If the present element greater than the smallest node,
    then replace. */
    if (heap[0].priority < pcb(buf))
    {
        /* Replace, the contents. */
        heap[0].priority = pcb(buf);
        memcpy(heap[0].buf, buf, pq->esize);

        /* Sift the new element down the heap. */
        do {
            /* Calculate the children offsets */
            c1 = (off * 2) + 1, c2 = (off * 2) + 2;

            /* Pick the smaller child. */
            c = (c2 < tlen && heap[c1].priority > heap[c2].priority) ?
                 c2 : c1;

            /* SWAP if the new child is valid and less than the parent. */
            if (c < tlen && heap[c].priority < heap[off].priority) {
                priority = heap[off].priority;
                tptr = heap[off].buf;
                heap[off].priority = heap[c].priority;
                heap[off].buf = heap[c].buf;
                heap[c].priority = priority;
                heap[c].buf = tptr;
                off = c;
            }
            /* Else we are done. */
            else
                break;
        } while (off < tlen);
    }

    /* Return success. */
    return 0;
}

/***********************************************************************/
/* GetPQArr: Return the array and the length!                          */
/*                                                                     */
/***********************************************************************/
int GetPQArr(void *handle, void **arr)
{
    struct PQueue *pq = handle;
    unsigned char *buf;
    int i, j = 0;

    /* Validate the parameters */
    if (!handle || !arr)
        return -1;

    /* Allocate memory for the output. */
    if (!(buf = malloc(pq->esize * pq->plen)))
        return 0;

    /* Loop seeking all the valid entries. */
    for (i = 0; i < pq->tlen; i++)
        if (pq->heap[i].priority != INT_MIN) {
            memcpy(&buf[j * pq->esize], pq->heap[i].buf, pq->esize);
            j++;
        }

    /* Return the size of the output array. */
    *arr = buf;
    return pq->plen;
}

/***********************************************************************/
/* FreePQ: Free priority queue!                                        */
/*                                                                     */
/***********************************************************************/
void FreePQ(void *handle)
{
    if (handle) {
        free(((struct PQueue *)handle)->heap);
        free(handle);
    }
}
