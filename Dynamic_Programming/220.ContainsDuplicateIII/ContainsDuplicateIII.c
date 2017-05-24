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
/* Macros                             */
/**************************************/
#define INT_MIN -0x80000000
#define INT_MAX  0x7FFFFFFF

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
    struct hbucket *nodes; /* Ciurcular buffer of nodes */
    int off;               /* Next node to be picked/deleted. */
};

/**************************************/
/* Hash Table                         */
/**************************************/
struct htable
{
    int bnum;            // number of buckets
    int t;               // max diff
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

    /* Initialize the bucket list. */
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
/* SearchDS: Search for a range within the bucket!                     */
/*                                                                     */
/***********************************************************************/
int SearchDS(struct htable *tbl, int val, int key, int t)
{
    int bnum;
    struct hbucket *node;
    unsigned long long tdiff;

    /* Get the bucket number and get the starting node. */
    bnum = key % tbl->bnum;
    node = tbl->hb[bnum];

    /* Look for a node withing the range in this bucket. */
    while (node)
    {
        /* Get the difference, can exceed 32 bit. */
        tdiff = node->val > val ? node->val - val: val - node->val;
        if (tdiff <= t)
            break;
        node = node->bnext;
    }

    /* If the value is within the range, then return true. */
    if (node)
        return true;
    /* Value not present. */
    return false;
}

/***********************************************************************/
/* AddToDS: Add a value to the hash table!                             */
/*                                                                     */
/***********************************************************************/
void AddToDS(struct htable *tbl, int val, int key, int t)
{
    struct hbucket *node;
    struct nodeq *q = &tbl->q;
    int bucketnum, bnum;

    /* Get the bucket number. */
    bucketnum = key % tbl->bnum;

    /* Pick the first available node. */
    node = &q->nodes[q->off];
    q->off = (q->off + 1) % tbl->bnum;

    /* If the node is already a part of the list, then delete. */
    if (node->bprev)
        node->bprev->bnext = node->bnext;
    if (node->bnext)
        node->bnext->bprev = node->bprev;

    /* If the node is a head, then reset the same. */
    bnum = (((node->val != INT_MIN) ? abs(node->val) : INT_MAX) /
           (t ? t : 1)) % tbl->bnum;
    if (tbl->hb[bnum] == node)
        tbl->hb[bnum] = tbl->hb[bnum]->bnext;

    /* Set the new value. */
    node->val = val;

    /* If there are nodes in the bucket, then adjust the pointers of the
    head. */
    node->bnext = tbl->hb[bucketnum];
    if (tbl->hb[bucketnum])
        tbl->hb[bucketnum]->bprev = node;

    /* Set the node as the new head. */
    node->bprev = NULL;
    tbl->hb[bucketnum] = node;
}

/***********************************************************************/
/* BKeyGen: Generate key to the bucket!                                */
/*                                                                     */
/***********************************************************************/
void BKeyGen(int val, int t, int *Key1, int *Key2, int *Key3)
{
    int max_key = INT_MAX / t;

    /* Get the first key. */
    *Key1 = ((val != INT_MIN) ? abs(val) : INT_MAX) / t;
    *Key2 = *Key3 = max_key; // Saturate the other two keys

    /* If there will be no underflow, then simply subtract 't' and
    divide. */
    if (val > -INT_MAX + (t - 1))
        *Key2 = abs(val - t) / t;
    /* If there will be no overflow, then simply add 't' and divide. */
    if (val <= INT_MAX - t)
        *Key3 = abs(val + t) / t;
}

/***********************************************************************/
/* Given an array of integers, find out whether there are two distinct */
/* indices i and j in the array such that the absolute difference      */
/* between nums[i] and nums[j] is at most t and the absolute difference*/
/* between i and j is at most k.                                       */
/*                                                                     */
/***********************************************************************/
bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t)
{
    void *ds;
    int i, Key1, Key2, Key3;
    bool ret = true;

    /* Validate the inputs. */
    if (!nums || numsSize < 1 || k < 1 || t < 0)
        return false;

    /* Rest k based on numssize */
    k = k > numsSize ? numsSize : k;

    /* Initialize the data structure. */
    if (!(ds = InitDS(k)))
        return false;

    /* Keep adding numbers to the table. If there was a failure,
    then exit. */
    for (i = 0; i < numsSize; ++i)
    {
        /* If t is not zero, then generate and search for all the three
        keys. */
        if (t)
        {
            /* Search the two buckets for val - t and val + t range
            values. */
            BKeyGen(nums[i], t, &Key1, &Key2, &Key3);
            if (SearchDS(ds, nums[i], Key2, t) ||
                SearchDS(ds, nums[i], Key3, t))
                goto __func_exit;
        }

        /* Else simply use the value itself as the key. */
        else
            Key1 = (nums[i] != INT_MIN) ? abs(nums[i]) : INT_MAX;
        /* Search in the remaining bucket. */
        if (SearchDS(ds, nums[i], Key1, t))
            goto __func_exit;

        /* Add the value to buckets. */
        AddToDS(ds, nums[i], Key1, t);
    }
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
    int arr[] = {-1, -1};
    int k = 1, t = 0;
    #elif 0
    int arr[] = {-1, -5, -0x80000000, 0x7FFFFFFF, -0x7FFFFFFF, -1};
    int k = 1, t = 2;
    #elif 0
    int arr[] = {-1, 2147483647};
    int k = 1, t = 2147483647;
    #elif 0
    int arr[] = {2147483647, -2147483647};
    int k = 1, t = 2147483647;
    #elif 1
    int arr[] = {0, 10, 22, 15, 0, 5, 22, 12, 1, 5};
    int k = 3, t = 3;
    #endif
    int len = sizeof(arr) / sizeof(int);
    printf("containsNearbyAlmostDuplicate = %d",
           containsNearbyAlmostDuplicate(arr, len, k, t));
    return 0;
}
