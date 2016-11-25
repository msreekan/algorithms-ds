/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/****************************************/
/* Data Structure                       */
/****************************************/
/*
** Simple Allocator Structure
*/
struct SAllocInf
{
    int off;               // offset within the block
    int bsz;               // block size
    unsigned char *buf;    // block pointer
    void *stack;           // stack for storing blocks
};

/***********************************************************************/
/* InitSAlloc: Initialize simple allocator!                            */
/*                                                                     */
/***********************************************************************/
void *InitSAlloc(int bsz, int block_count)
{
    struct SAllocInf *salloc = NULL;

    /* Validate inputs, allocate stack and the simple structure */
    if (bsz > 1 && block_count > 1 &&
        (salloc = calloc(1, sizeof(struct SAllocInf))) &&
        (salloc->stack = StackAlloc(block_count, sizeof(char *))) &&
        (salloc->buf = calloc(bsz, sizeof(char))))
        salloc->bsz = bsz;     // block size

    /* Else in case of a failure, free up the allocations */
    else if (salloc) {
        if (salloc->stack)
            StackFree(salloc->stack);
        if (salloc->buf)
            free(salloc->buf);
        free(salloc);
        salloc = NULL;
    }

    /* Return the handle */
    return salloc;
}

/***********************************************************************/
/* GetSAlloc: Get a segment from the allocator!                        */
/*                                                                     */
/***********************************************************************/
void *GetSAlloc(void *handle, int val)
{
    struct SAllocInf *salloc = handle;

    /* Validate the input */
    if (!handle || val < 1)
        return NULL;

    /* If the present block has exhausted, then allocate new */
    if (salloc->off + val >= salloc->bsz) {
        /* Push the older pointer to the stack */
        if (StackPush(salloc->stack, &salloc->buf))
            return NULL;

        /* Allocate a new block */
        if (!(salloc->buf = calloc(salloc->bsz, sizeof(char))))
            return NULL;
        salloc->off = 0;
    }

    /* Increment the segment allocation offset */
    salloc->off += val;
    return &salloc->buf[salloc->off - val];
}

/***********************************************************************/
/* FreeSAlloc: Free the simple allocator!                              */
/*                                                                     */
/***********************************************************************/
void FreeSAlloc(void *handle)
{
    void *ptr;
    struct SAllocInf *salloc = handle;

    /* Validate the input */
    if (!handle) return;

    /* Free all the blocks */
    while (!StackEmpty(salloc->stack)) {
        StackPop(salloc->stack, &ptr);
        free(ptr);
    }

    /* Free the last remaining buffer and the handle. */
    if (salloc->buf)
        free(salloc->buf);
    free(salloc);
}
