/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
/****************************************/
/* Stack Data Structure                 */
/****************************************/
struct ___stack
{
    unsigned char *ptr;
    unsigned char *top;
    unsigned char *end;
    int ent_sz;
};

/***********************************************************************/
/* StackAlloc: Initialize Stack                                        */
/*             size = Stack size -- maximum number of entries          */
/*             entry_size = Size of the entry                          */
/*                                                                     */
/***********************************************************************/
void *StackAlloc(unsigned int size, unsigned int esize)
{
    struct ___stack *p;
    unsigned int slen = size * esize;

    /* Allocate stack memory. */
    p = malloc(sizeof(struct ___stack) + (slen * sizeof(unsigned char)));
    if (!p)
        return NULL;
    p->ptr = (unsigned char *)(p + 1);
    p->top = p->ptr;
    p->end = p->ptr + slen;
    p->ent_sz = esize;

    /* Return the stack handle */
    return p;
}

/***********************************************************************/
/* StackFree: Free Stack                                               */
/*            handle = Stack handle                                    */
/*                                                                     */
/***********************************************************************/
void StackFree(void *handle)
{
    free(handle);
}

/***********************************************************************/
/* StackPush: Stack Push                                               */
/*            handle = Stack handle                                    */
/*            ptr = Entry to be pushed                                 */
/*                                                                     */
/***********************************************************************/
int StackPush(void *handle, void *ptr)
{
    struct ___stack *p = handle;

    /* Validate inputs */
    if ((!handle || !ptr) || (p->top + p->ent_sz > p->end))
        return -1;

    /* Copy and increment the top */
    memcpy(p->top, ptr, p->ent_sz);
    p->top += p->ent_sz;

    /* Success */
    return 0;
}

/***********************************************************************/
/* StackPop: Stack Pop                                                 */
/*           handle = Stack handle                                     */
/*           ptr = Memory to pop                                       */
/*                                                                     */
/***********************************************************************/
int StackPop(void *handle, void *ptr)
{
    struct ___stack *p = handle;

    /* Validate inputs */
    if (!handle || !ptr || (p->top == p->ptr))
        return -1;

    /* Copy and decrement the top */
    p->top -= p->ent_sz;
    memcpy(ptr, p->top, p->ent_sz);

    /* Success */
    return 0;
}

/***********************************************************************/
/* StackEmpty: Check Stack status                                      */
/*           handle = Stack handle                                     */
/*                                                                     */
/***********************************************************************/
int StackEmpty(void *handle)
{
    struct ___stack *p = handle;

    /* Validate inputs */
    if (!handle)
        return -1;

    /* Return 1 if it's empty */
    return (p->top == p->ptr) ? 1 : 0;
}

/***********************************************************************/
/* StackGet: Get used stack size in bytes                              */
/*           handle = Stack handle                                     */
/*                                                                     */
/***********************************************************************/
int StackGet(void *handle)
{
    struct ___stack *p = handle;

    /* Validate inputs */
    if (!handle)
        return -1;

    /* Return used stack size in bytes. */
    return (p->top - p->ptr) / p->ent_sz;
}

/***********************************************************************/
/* StackCopy: Copy stack contents                                      */
/*           handle = Stack handle                                     */
/*                                                                     */
/***********************************************************************/
int StackCopy(void *handle, unsigned char *buf)
{
    struct ___stack *p = handle;

    /* Validate inputs */
    if (!handle)
        return -1;

    /* Return used stack size in bytes. */
    memcpy(buf, p->ptr, p->top - p->ptr);
    return 0;
}
