/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************/
/* Macros.                          */
/************************************/
#define LEFT_INDEX 0
#define RIGHT_INDEX 1
#define HEIGHT_INDEX 2
#define LIST_METHOD 0
#define QUICK_SORT  1

/************************************/
/* Transition Points.               */
/************************************/
struct tp
{
    int xy;  /* Left/Right coordinates. */
    int off; /* Offset within the main array. */
};

/***********************************************************************/
/* SwapTP: Swap transition points!                                     */
/*                                                                     */
/***********************************************************************/
void SwapTP(struct tp *t1, struct tp *t2)
{
    struct tp t = *t1;
    t1->xy = t2->xy;
    t1->off = t2->off;
    t2->xy = t.xy;
    t2->off = t.off;
}

#if QUICK_SORT
/***********************************************************************/
/* GetPivot: Get pivot for transition points!                          */
/*                                                                     */
/***********************************************************************/
int GetPivot(struct tp *tparr, int start, int end)
{
    int i = start, j = end - 1, pivot = end;

    /* Loop seeking the correct location for the piviot. */
    while (i <= j)
    {
        /* Move the indices to locate elements for swapping. */
        while (i < end && tparr[i].xy <= tparr[pivot].xy)
            i++;
        while (j >= start && tparr[j].xy > tparr[pivot].xy)
            j--;

        /* Swap if there is a need. */
        if (i < j)
            SwapTP(&tparr[i], &tparr[j]);
    }

    /* Swap pivot into place and return. */
    if (i != pivot)
        SwapTP(&tparr[i], &tparr[pivot]);
    return i;
}

/***********************************************************************/
/* SortTP: Sort transition points!                                     */
/*                                                                     */
/***********************************************************************/
void SortTP(struct tp *tparr, int start, int end)
{
    int pivot;

    /* If the start greater than or equal to end, return. */
    if (start >= end)
        return;

    pivot = GetPivot(tparr, start, end);
    SortTP(tparr, start, pivot - 1);
    SortTP(tparr, pivot + 1, end);
}
#else
/***********************************************************************/
/* SortTP: Sort transition points!                                     */
/*                                                                     */
/***********************************************************************/
void SortTP(struct tp *tparr, int start, int end)
{
    int i, j, flag, len = end - start + 1;
    struct tp *s = &tparr[start];

    /* Bubble sort loop. Pick the next element. */
    for (i = 0; i < len - 1; ++i)
    {
        /* Move the greatest value to the correct location. */
        for (flag = 0, j = 0; j < len - i - 1; ++j)
        {
            if (s[j].xy > s[j + 1].xy)
            {
                SwapTP(&s[j], &s[j + 1]);
                flag = 1;
            }
        }
        /* If there were no swaps, then array is sorted. */
        if (!flag)
            break;
    }
}
#endif

#if LIST_METHOD
/************************************/
/* Building Coordinates list node.  */
/************************************/
struct bc
{
    int *arr;
    struct bc *prev; // prev node
    struct bc *next; // next node
};

/*******************************************/
/* Building Coordinate Double Linked List. */
/*******************************************/
struct BCList
{
    struct bc *base;  // node array base
    struct bc *start; // list start
    struct bc *end;   // list end
    struct tp *tparr; // transition points
    int blen;         // number of nodes
};

/***********************************************************************/
/* InitDS: Initialize the data structure!                              */
/*                                                                     */
/***********************************************************************/
void *InitDS(int **b, int brsz, int bcsz, struct tp **tparr)
{
    struct BCList *bl;
    struct bc *bn;
    int i, j = 0, k = 0, l = brsz + 1;
    struct tp *tarr;

    /* Allocate the memory. */
    bl = malloc((sizeof(struct BCList)) + (sizeof(struct bc) * brsz) +
                (sizeof(struct tp) * ((brsz * 2) + 2)));
    if (!bl)
        return NULL;
    bl->base = bn = (struct bc *)(bl + 1); // assign the node array base.
    bl->tparr = tarr = *tparr = (struct tp *)&bn[brsz];

    /* Loop assigning values to the node. */
    for (i = 0; i < brsz; ++i)
    {
        /* If buildings share the height and they overlap, then
        merge them into one entry. */
        if (i && (b[i - 1])[RIGHT_INDEX] >= (b[i])[LEFT_INDEX] &&
            (b[i - 1])[HEIGHT_INDEX] == (b[i])[HEIGHT_INDEX])
        {
            bn[j - 1].arr[RIGHT_INDEX] = (b[i])[RIGHT_INDEX];
            tarr[l - 1].xy = (b[i])[RIGHT_INDEX];
        }
        else
        {
            bn[j].arr = b[i];
            bn[j].prev = bn[j].next = NULL;

            /* Initialize the transition points. */
            tarr[k].xy = bn[j].arr[LEFT_INDEX];
            tarr[k++].off = j;
            tarr[l].xy = bn[j].arr[RIGHT_INDEX];
            tarr[l++].off = j;
            j += 1; // increment counter
        }
    }

    /* Sort right coordinates of transition points. Left is already
    sorted. */
    SortTP(tarr, brsz + 1, l - 1);

    /* Terminating entry. */
    tarr[l].xy = tarr[l].off = tarr[k].xy = tarr[k].off = -1;

    /* Initialize the stack. */
    bl->start = bl->end = NULL;
    bl->base = bn;
    bl->blen = j;

    /* Return the List. */
    return bl;
}

/***********************************************************************/
/* AddToDS: Add a coordinate to the list!                              */
/*                                                                     */
/***********************************************************************/
int AddToDS(struct BCList *bcs, int offst, int *x, int *y)
{
    struct bc *node = bcs->start, *enode = bcs->end, *ennode = NULL;
    struct bc *pnode = NULL, *new_node;

    /* Ensure the offset is valid and node is not already in the list.
    The check against start node ensures that we do not add the same
    start node twice.*/
    if (bcs->base[offst].prev || bcs->base[offst].next ||
        offst > bcs->blen || node == &bcs->base[offst])
        return -1;
    new_node = &bcs->base[offst];

    /* If this is the first node, insert it here. */
    if (!node)
        bcs->start = bcs->end = new_node;
    else {
        /* Seek to the correct location. Run the list from start and end,
        this reduces comparisons in the O(n) lookup. */
        while (node && node->arr[HEIGHT_INDEX] > new_node->arr[HEIGHT_INDEX]
               && enode->arr[HEIGHT_INDEX] < new_node->arr[HEIGHT_INDEX]) {
            pnode = node;
            node = node->next;
            ennode = enode;
            enode = enode->prev;
        }

        /* If there was a hit with reverse lookup, then use that for
        insertion.*/
        if (enode && enode->arr[HEIGHT_INDEX] >= new_node->arr[HEIGHT_INDEX]) {
            pnode = enode;
            node = ennode;
        }

        /* Insert the new node. */
        if (pnode)
            pnode->next = new_node;
        /* If there is no previous node, then this is head. */
        else
            bcs->start = new_node;
        new_node->prev = pnode;
        new_node->next = node;
        if (node)
            node->prev = new_node;
        else
            bcs->end = new_node;
    }

    /* If this is the new head, then assign the coordinates. */
    if (!pnode) {
        *x = new_node->arr[LEFT_INDEX];
        *y = new_node->arr[HEIGHT_INDEX];
    }

    /* Return 0 if there is new head. */
    return !pnode ? 0 : 1;
}

/***********************************************************************/
/* DelFromDS: Delete a coordinate from the list!                       */
/*                                                                     */
/***********************************************************************/
int DelFromDS(struct BCList *bcs, int offst, int *x, int *y)
{
    struct bc *del_node;
    int ret = 1;

    /* Ensure the offset is valid.*/
    if (offst > bcs->blen)
        return -1;
    del_node = &bcs->base[offst];

    /* Delete the node. Set the previous node to point to the next. */
    if (del_node->prev)
        del_node->prev->next = del_node->next;

    /* Set the next node previous pointer to previous node. */
    if (del_node->next)
        del_node->next->prev = del_node->prev;

    /* If needed, update the start. */
    if (del_node == bcs->start)
    {
        bcs->start = del_node->next;
        ret = 0;
        *x = del_node->arr[RIGHT_INDEX];
        if (del_node->next)
            *y = del_node->next->arr[HEIGHT_INDEX];
        else
            *y  = 0;
    }
    /* If needed, update the end. */
    if (del_node == bcs->end)
        bcs->end = del_node->prev;
    del_node->prev = del_node->next = NULL;

    /* Return the status. */
    return ret;
}
#else
/************************************/
/* Building coordinate structure.   */
/************************************/
struct bc
{
    int *arr; /* coordinate array offset. */
    int hoff; /* heap array offset. */
};

/************************************/
/* Heap for building coordinates.   */
/************************************/
struct BcHeap
{
    struct bc **harr; /* Heap array. */
    struct bc *arr;   /* Building coordinate array. */
    struct tp *tparr; /* Transition points array. */
    int plen;         /* Present length. */
    int len;          /* Total length. */
};

/***********************************************************************/
/* InitDS: Initialize the heap!                                        */
/*                                                                     */
/***********************************************************************/
void *InitDS(int **b, int brsz, int bcsz, struct tp **tparr)
{
    struct BcHeap *bh;
    struct bc *bn;
    int i, j = 0, k = 0, l = brsz + 1;
    struct tp *tarr;

    /* Allocate the memory. And initialize the heap structure. */
    bh = malloc((sizeof(struct BcHeap)) + ((sizeof(struct bc *) +
                 sizeof(struct bc)) * brsz) +
                (sizeof(struct tp) * ((brsz * 2) + 2)));
    if (!bh) return NULL;
    bn = (struct bc *)(bh + 1);
    bh->arr = bn;

    /* Initialize the heap pointer array. */
    bh->harr = (struct bc **)&bn[brsz];
    memset(bh->harr, 0, brsz * sizeof(struct bc *));

    /* Assign transition points array. */
    bh->tparr = (struct tp *)&bh->harr[brsz];
    tarr = *tparr = bh->tparr ;

    /* Loop assigning values to the node. */
    for (i = 0; i < brsz; ++i)
    {
        /* If buildings share the height and they overlap, then
        merge them into one entry. */
        if (i && (b[i - 1])[RIGHT_INDEX] >= (b[i])[LEFT_INDEX] &&
            (b[i - 1])[HEIGHT_INDEX] == (b[i])[HEIGHT_INDEX])
        {
            bn[j - 1].arr[RIGHT_INDEX] = (b[i])[RIGHT_INDEX];
            tarr[l - 1].xy = (b[i])[RIGHT_INDEX];
        }
        else
        {
            /* Assign the array pointer and the offset. */
            bn[j++] = (struct bc){b[i], -1};

            /* Initialize the transition points. */
            tarr[k++] = (struct tp){(b[i])[LEFT_INDEX], j - 1};
            tarr[l++] = (struct tp){(b[i])[RIGHT_INDEX], j - 1};
        }
    }

    /* Sort right coordinates. */
    SortTP(tarr, brsz + 1, l - 1);

    /* Terminating entry. */
    tarr[l].xy = tarr[l].off = tarr[k].xy = tarr[k].off = -1;

    /* Initialize the heap length. */
    bh->len = j;
    bh->plen = 0;

    /* Return the heap. */
    return bh;
}

/***********************************************************************/
/* AddToDS: Add a coordinate to the heap!                              */
/*                                                                     */
/***********************************************************************/
int AddToDS(struct BcHeap *bch, int offst, int *x, int *y)
{
    int c, p, ret = 1, hlen = bch->len - 1;
    struct bc *t;

    /* Validate the offset. */
    if ((offst > hlen) || (bch->arr[offst].hoff != -1))
        return -1;

    /* Add the value to the end of the heap. */
    bch->harr[bch->plen] = &bch->arr[offst];
    bch->arr[offst].hoff = bch->plen;
    bch->plen++;   // increment the count

    /* Allow the value to sift up.*/
    for (c = bch->plen - 1; c > 0; c = p)
    {
        /* Select the parent offset. */
        p = (c - 1) / 2;

        /* If the parent is less than the child, then swap. */
        if (bch->harr[c]->arr[HEIGHT_INDEX] >
            bch->harr[p]->arr[HEIGHT_INDEX])
        {
            /* Track the location of the modified offsets. */
            bch->harr[p]->hoff = c;
            bch->harr[c]->hoff = p;

            /* Swap the pointers. */
            t = bch->harr[c];
            bch->harr[c] = bch->harr[p];
            bch->harr[p] = t;
        }

        /* Else we are done. */
        else
            break;
    }

    /* If we have a new top value, then set coordinates. */
    if (!c)
    {
        *x = bch->harr[c]->arr[LEFT_INDEX];
        *y = bch->harr[c]->arr[HEIGHT_INDEX];
        ret = 0;
    }

    /* Return the status. */
    return ret;
}

/***********************************************************************/
/* DelFromDS: Delete a value from the heap!                            */
/*                                                                     */
/***********************************************************************/
int DelFromDS(struct BcHeap *bch, int offst, int *x, int *y)
{
    int p, c1, c2, c = 0, ret = 1;
    struct bc *t;

    /* Validate the offset. */
    if ((offst >= bch->len) || (bch->arr[offst].hoff == -1))
        return -1;

    /* Get the location of the node, reset the heap offset. */
    p = bch->arr[offst].hoff;
    bch->harr[p]->hoff = -1;

    /* If this is the root, then set the new x-coordinate. */
    if (p == 0)
    {
        *x = bch->arr[offst].arr[RIGHT_INDEX];
        ret = 0;
    }

    /* Replace the value with the last node. */
    bch->harr[bch->plen - 1]->hoff = p;
    bch->harr[p] = bch->harr[bch->plen - 1];
    bch->harr[bch->plen - 1] = NULL;
    bch->plen--;

    /* Loop allowing the new value to sift down. */
    while (p < bch->plen)
    {
        /* Get the child offsets. */
        c1 = p * 2 + 1;
        c2 = c1 + 1;
        c = -1;

        /* Pick the larger child. */
        if (c2 < bch->plen && bch->harr[c2]->arr[HEIGHT_INDEX] >
                              bch->harr[c1]->arr[HEIGHT_INDEX])
            c = c2;
        else if (c1 < bch->plen)
            c = c1;
        else
            break;

        /* Swap the parent with the larger child. */
        if (bch->harr[p]->arr[HEIGHT_INDEX] <
            bch->harr[c]->arr[HEIGHT_INDEX])
        {
            /* Track the location of the modified offsets. */
            bch->harr[p]->hoff = c;
            bch->harr[c]->hoff = p;

            /* Swap the pointers. */
            t = bch->harr[c];
            bch->harr[c] = bch->harr[p];
            bch->harr[p] = t;

            p = c; // Old child is the new parent
        }
        else
            break;
    }

    /* If we have displaced the root, then set the y-coordinate.*/
    if (!ret)
         *y = (!bch->plen) ? 0 : bch->harr[0]->arr[HEIGHT_INDEX];
    return ret;
}
#endif

/***********************************************************************/
/* The Skyline!                                                        */
/*                                                                     */
/***********************************************************************/
int** getSkyline(int** bldgs, int brsz, int bcolsz, int* returnSize)
{
    void *bcs = NULL;
    struct tp *larr = NULL, *rarr;
    int **retarr = NULL;
    int i, j;

    /* Initialize return size. */
    if (returnSize) *returnSize = 0;

    /* Validate the parameters. */
    if (!bldgs || brsz < 1 || bcolsz < 1 || !returnSize)
        return retarr;

    /* Allocate the maximum possible size for return array. */
    retarr = malloc(sizeof(int *) * (brsz * 2));
    if (!retarr)
        return NULL;

    /* Initialize the data structure for the SkyLine array. */
    if (!(bcs = InitDS(bldgs, brsz, bcolsz, &larr)))
        return retarr;
    rarr = &larr[brsz + 1];

    /* Loop through the transition points. */
    j = i = 0;
    while (rarr[j].xy != -1)
    {
        int loc, x, y;

        /* If the smaller coordinate is on the left, then add the building. */
        if (larr[i].xy != -1 && (larr[i].xy < rarr[j].xy)) {
            if ((loc = AddToDS(bcs, larr[i++].off, &x, &y)) < 0)
              goto __SkyExit;
        }

        /* Else, remove the building. */
        else if ((loc = DelFromDS(bcs, rarr[j++].off, &x, &y)) < 0)
                goto __SkyExit;

        /* If there is a new highest building, then save the
        coordinates.*/
        if (!loc) {
            /* If the building walls are adjacent, then simply update the
            previous entry. Eg : [9, 0] && [9, 12] */
            if (*returnSize && x == (retarr[*returnSize - 1])[0])
                (retarr[*returnSize - 1])[1] = y;
            else {
                /* Allocate pointer array to store coordinates. */
                retarr[*returnSize] = malloc(sizeof(int) * 2);
                if (!retarr[*returnSize])
                    goto __SkyExit;
                (retarr[*returnSize])[0] = x;
                (retarr[*returnSize])[1] = y;
                (*returnSize) += 1;
            }
        }
    }
__SkyExit:
    if (bcs)
        free(bcs);
    return retarr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int r1[] = {2, 9, 10}, r2[] = {3, 7, 15}, r3[] = {5, 12, 12};
    int r4[] = {15, 20, 10}, r5[] = {19, 24, 8};
    int *mat[] = {r1, r2, r3, r4, r5};
    #elif 1
    int r1[] = {0, 2, 3}, r2[] = {2, 5, 3};
    int *mat[] = {r1, r2};
    #elif 0
    int r1[] = {2, 9, 10}, r2[] = {9, 12, 15};
    int *mat[] = {r1, r2};
    #elif 0
    int r1[] = {2, 13, 10}, r2[] = {10, 17, 25}, r3[] = {12, 20, 14};
    int *mat[] = {r1, r2, r3};
    #elif 0
    int r1[] = {0, 5, 7}, r2[] = {5, 10, 7}, r3[] = {5, 10, 12}, r4[] = {10, 15, 7};
    int r5[] = {15, 20, 7}, r6[] = {15, 20, 12}, r7[] = {20, 25, 7};
    int *mat[] = {r1, r2, r3, r4, r5, r6, r7};
    #elif 1
    int r1[] = {2, 9, 10}, r2[] = {3, 7, 15}, r3[] = {5, 12, 12}, r4[] = {15, 20, 10};
    int r5[] = {19, 24, 8};
    int *mat[] = {r1, r2, r3, r4, r5};
    #endif
    int rsz = sizeof(mat) / sizeof(int *);
    int csize = sizeof(r1) / sizeof(int);
    int retsz, i;
    int **retarr;

    /* Get the skyline and print. */
    retarr = getSkyline(mat, rsz, csize, &retsz);

    /* Print and free. */
    for (i = 0; i < retsz; ++i)
    {
        printf("[%d, %d] ", (retarr[i])[0], (retarr[i])[1]);
        free(retarr[i]);
    }

    /* Free the main array. */
    free(retarr);
    return 0;
}
