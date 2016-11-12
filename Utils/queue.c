/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/****************************************/
/* Queue Data Structure                 */
/****************************************/
struct ___queue
{
    unsigned char *ptr;
    int start;
    int end;
    int qsize;
    int entsz;
};

/***********************************************************************/
/* QueueAlloc: Initialize Queue                                        */
/*             size = Queue size -- maximum number of entries          */
/*             entry_size = Size of the entry                          */
/*                                                                     */
/***********************************************************************/
void *QueueAlloc(unsigned int size, unsigned int esize)
{
    struct ___queue *p;
    unsigned int slen = size * esize;

    /* Allocate queue memory. */
    p = malloc(sizeof(struct ___queue) + (slen * sizeof(unsigned char)));
    if (!p)
        return NULL;
    p->ptr = (unsigned char *)(p + 1);
    p->end = p->start = 0;
    p->qsize = slen;
    p->entsz = esize;

    /* Return the queue handle */
    return p;
}

/***********************************************************************/
/* QueueFree: Free Queue                                               */
/*            handle = Queue handle                                    */
/*                                                                     */
/***********************************************************************/
void QueueFree(void *handle)
{
    free(handle);
}

/***********************************************************************/
/*  QueueAdd: Queue add                                                */
/*            handle = Queue handle                                    */
/*            ptr = Entry to be pushed                                 */
/*                                                                     */
/***********************************************************************/
int QueueAdd(void *handle, void *ptr)
{
    struct ___queue *p = handle;

    /* Validate inputs. If the queue is full, then return failure */
    if ((!p || !ptr) || ((p->end + p->entsz) % p->qsize) == p->start)
        return -1;

    /* Copy and increment the top */
    memcpy(&p->ptr[p->end], ptr, p->entsz);
    p->end = (p->end + p->entsz) % p->qsize;

    /* Success */
    return 0;
}

/***********************************************************************/
/* QueueDel: Queue delete                                              */
/*           handle = Stack handle                                     */
/*           ptr = Memory to pop                                       */
/*                                                                     */
/***********************************************************************/
int QueueDel(void *handle, void *ptr)
{
    struct ___queue *p = handle;

    /* Validate inputs. If the queue is empty, then return error. */
    if (!handle || !ptr || (p->start == p->end))
        return -1;

    /* Copy and the top */
    memcpy(ptr, &p->ptr[p->start], p->entsz);
    p->start = (p->entsz + p->start) % p->qsize;

    /* Success */
    return 0;
}

/***********************************************************************/
/* QueueEmpty: Check queue status                                      */
/*             handle = Queue handle                                   */
/*                                                                     */
/***********************************************************************/
int QueueEmpty(void *handle)
{
    struct ___queue *p = handle;

    /* Validate inputs */
    if (!handle)
        return -1;

    /* Return 1 if it's empty */
    return (p->start == p->end) ? 1 : 0;
}

/***********************************************************************/
/* QueueSzGet: Get used queue size in bytes                            */
/*             handle = Queue handle                                   */
/*                                                                     */
/***********************************************************************/
int QueueSzGet(void *handle)
{
    struct ___queue *p = handle;

    /* Validate inputs */
    if (!handle)
        return -1;

    /* Return used stack size in bytes. */
    return (p->end >= p->start) ? p->end - p->start :
                                  p->qsize - p->start + p->end;
}

/***********************************************************************/
/* QueueSearch: Search for an entry in the queue                       */
/*              handle = Queue handle                                  */
/*                                                                     */
/***********************************************************************/
int QueueSearch(void *handle, void *ptr)
{
    struct ___queue *p = handle;
    int ret = -1, s, e;

    /* Validate */
    if (!handle || !p)
        return ret;

    /* Search the queue */
    s = p->start;
    e = p->end;

    /* Start from the beginning and loop till the end */
    while (s != e)
    {
        /* If there is a match, then set return offset and break */
        if (!memcmp(&p->ptr[s], ptr, p->entsz)) {
            ret = p->start > s ? p->qsize - p->start + s :
                                 s - p->start;
            ret /= p->entsz;
            break;
        }
        s = (s + p->entsz) % p->qsize; // increment/loop back
    }

    /* Return offset */
    return ret;
}
