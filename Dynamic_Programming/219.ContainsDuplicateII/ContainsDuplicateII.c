/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**************************************/
/* Hash Bucket                        */
/**************************************/
struct hbucket
{
    int val;
    struct hbucket *bnext;
    struct hbucket *bprev;
};

/**************************************/
/* Node Queue                         */
/**************************************/
struct nodeq
{
    struct hbucket *nodes; /* Actual nodes */
    int off;               /* Next node to be deleted. */
};

/**************************************/
/* Hash Table                         */
/**************************************/
struct htable
{
    int bnum;            // number of buckets
    struct nodeq q;      // queues
    struct hbucket **hb; // buckets
};

/***********************************************************************/
/* InitDS: Initialize the hash table!                                  */
/*                                                                     */
/***********************************************************************/
void *InitDS(int k)
{
    struct htable *tbl;
    struct hbucket *node;

    /* Allocate the memory. */
    tbl = malloc(sizeof(struct htable) + (sizeof(struct hbucket) * k) +
                 (sizeof(struct hbucket *) * k));
    if (!tbl)
        return NULL;

    /* Initialize the buclet list. */
    tbl->hb = (struct hbucket **)(tbl + 1);
    memset(tbl->hb, 0, sizeof(struct hbucket *) * k);

    /* Initialize the node array. */
    tbl->q.nodes = node = (struct hbucket *)(tbl->hb + k);
    memset(tbl->q.nodes, 0, (sizeof(struct hbucket) * k));
    tbl->bnum = k;
    tbl->q.off = 0;

    /* Return the handle. */
    return tbl;
}

/***********************************************************************/
/* AddToDS: Add a value to the hash table!                             */
/*                                                                     */
/***********************************************************************/
void *AddToDS(struct htable *tbl, int val)
{
    struct hbucket *node, *nprev, *n;
    struct nodeq *q = &tbl->q;
    unsigned long long bucketnum;

    /* Generate the hash. */
    bucketnum = (val != 0x80000000) ? abs(val) % tbl->bnum : 0;

    /* Pick the first available node. */
    node = &q->nodes[q->off];
    q->off = (q->off + 1) % tbl->bnum;

    /* If the node is already a part of the list, then delete. */
    if (node->bprev)
        node->bprev->bnext = node->bnext;
    if (node->bnext)
        node->bnext->bprev = node->bprev;
    /* If the node is the head, then reset the list. */
    if (tbl->hb[abs(node->val) % tbl->bnum] == node)
        tbl->hb[abs(node->val) % tbl->bnum] =
        tbl->hb[abs(node->val) % tbl->bnum]->bnext;

    /* Set the new value. */
    node->val = val;

    /* If this is the first node in the bucket, then update the head. */
    if (!tbl->hb[bucketnum])
    {
        node->bnext = node->bprev = NULL;
        tbl->hb[bucketnum] = node;
    }

    /* Else run through the list, keep it sorted. */
    else
    {
        /* Pick the head of the list. */
        n = tbl->hb[bucketnum];
        nprev = NULL;

        /* Run through the list as long as the nodes are valid and their
        values are lesser than the new node. */
        while (n && n->val < val) {
            nprev = n;
            n = n->bnext;
        }

        /* If there is aduplicate, then return NULL. */
        if (n && n->val == val)
            return NULL;

        /* Insert the node. */
        if (nprev)
            nprev->bnext = node;
        /* We have a new head. */
        else
            tbl->hb[bucketnum] = node;
        node->bprev = nprev;
        node->bnext = n;

        /* If this is not the last node, then point the next node to the
        new node. */
        if (n)
            n->bprev = node;
    }

    /* Return the node . */
    return node;
}

/***********************************************************************/
/* Given an array of integers and an integer k, find out whether there */
/* are two distinct indices i and j in the array such that             */
/* nums[i] = nums[j] and the absolute difference between i and j is at */
/* most k.                                                             */
/*                                                                     */
/***********************************************************************/
bool containsNearbyDuplicate(int* nums, int numsSize, int k)
{
    void *ds;
    int i;
    bool ret = true;

    /* Validate the inputs. */
    if (!nums || numsSize < 1 || k < 1)
        return false;
    /* Rest k based on numssize */
    k = k > numsSize ? numsSize : k;

    /* Initialize the data structure. */
    if (!(ds = InitDS(k + 1)))
        return false;

    /* Keep adding numbers to the table. If there was a failure,
    then exit. */
    for (i = 0; i < numsSize; ++i)
        if (!AddToDS(ds, nums[i]))
            goto __func_exit;
    ret = false;
__func_exit:
    free(ds);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //           0,   1,   2,   3,   4,    5,   6  7
    #if 0
    int arr[] = {32, 64, 128, 256, 512, 1024, 512, 2048};
    int k = 2;
    #elif 0
    int arr[] = {13, 23, 1, 2, 3};
    int k = 5;
    #elif 0
    int arr[] = {2147483647, -2147483648, 2147483647, -2147483648};
    int k = 2;
    #elif 1
    int arr[] = {0, 1, 2, 3, 4, 0, 0, 7, 8, 9, 10, 11, 12, 0};
    int k = 1;
    #endif
    int len = sizeof(arr) / sizeof(int);
    printf("containsNearbyDuplicat = %d",
           containsNearbyDuplicate(arr, len, k));
    return 0;
}
