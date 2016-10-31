/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hasht.h"

/****************************************/
/* Hash Table Data Structure             */
/****************************************/
/*
** Hash Table Entry Header
*/
struct ___entry_header
{
    struct ___entry_header *next;
    struct ___entry_header *prev;
};

/*
** Bucket Entry
*/
struct ___bucket_entry
{
    struct ___entry_header *start;
};

/*
** Bucket List Header
*/
struct ___bucket_header
{
    int bcount;                    // bucket count
    int esize;                     // entry size
    int (*hash_fn)(void *);        // hash function
    int (*cmp_fn)(void *, void *); // mem compare function
    struct ___bucket_entry *blist; // bucket list
};

/***********************************************************************/
/* tSearch: Search for an entry                                        */
/*          handle = Handle                                            */
/*          ptr = Entry to be deleted                                  */
/*                                                                     */
/***********************************************************************/
static void *tSearch(void *handle, void *ptr)
{
    struct ___bucket_header *p = handle;
    struct ___bucket_entry *be;
    struct ___entry_header *eh = NULL;

    /* Validate inputs */
    if (!handle || !ptr)
        return NULL;

    /* Get the relevant bucket header */
    be = &p->blist[p->hash_fn(ptr) % p->bcount];
    eh = be->start;

    /* Find the entry */
    while (eh && (p->cmp_fn(eh + 1, ptr) != 0))
        eh = eh->next;

    /* Success or Failure depending on the search */
    return eh;
}

/***********************************************************************/
/* tFreeBucket: Free memory allocated to a bucket                      */
/*              bckt = Handle                                          */
/*                                                                     */
/***********************************************************************/
void tFreeBucket(struct ___bucket_entry *bckt)
{
    struct ___entry_header *h, *nh;

    /* If the bucket is empty, then return */
    if (!bckt->start)
        return;
    h = bckt->start; // get the start
    while (h) // loop deleting the nodes of the linked list
    {
        nh = h->next;
        free(h);
        h = nh;
    }
}

/***********************************************************************/
/* HashTAlloc: Initialize Hash Table                                   */
/*             size = Bucket size -- maximum number of buckets         */
/*             entry_size = Size of the table entry                    */
/*                                                                     */
/***********************************************************************/
void *HashTAlloc(unsigned int size, unsigned int esize,
                 int (*hash_fn)(void *), int (*cmp_fn)(void *, void *))
{
    struct ___bucket_header *p;
    int total_bytes = sizeof(struct ___bucket_header) +      // 1 header
                     (size * sizeof(struct ___bucket_entry));// n buckets

    /* Validate the inputs */
    if (!size || !hash_fn || !esize)
        return NULL;

    /* Allocate stack memory. */
    p = calloc(total_bytes, sizeof(unsigned char));
    if (!p)
        return NULL;
    p->bcount = size;                                  // bucket count
    p->esize = esize + sizeof(struct ___entry_header); // entry size
    p->blist = (struct ___bucket_entry *)(p + 1);     // bucket list
    p->hash_fn = hash_fn; // hash generator
    p->cmp_fn = cmp_fn; // hash generator

    /* Return the queue handle */
    return p;
}

/***********************************************************************/
/* HashTFree: Free hash table                                          */
/*            handle = Hash table handle                               */
/*                                                                     */
/***********************************************************************/
void HashTFree(void *handle)
{
    struct ___bucket_header *p = handle;
    int i;

    /* Loop and free all the buckets */
    for (i = 0; i < p->bcount; ++i)
        tFreeBucket(&p->blist[i]);
    free(handle);
}

/***********************************************************************/
/* HashTAdd: Add elements to the hash table                            */
/*           handle = Handle                                           */
/*           ptr = Entry to be added                                   */
/*                                                                     */
/***********************************************************************/
int HashTAdd(void *handle, void *ptr)
{
    struct ___bucket_header *p = handle;
    struct ___bucket_entry *be;
    struct ___entry_header *eh;
    unsigned char *entry;

    /* Validate inputs and verify available size. */
    if (!handle || !ptr)
        return -1;

    /* Allocate the entry */
    if ((entry = malloc(p->esize)) == NULL)
        return -1;
    eh = (struct ___entry_header *)entry;
    eh->prev = NULL;

    /* Copy contents */
    memcpy(&entry[sizeof(struct ___entry_header)], ptr,
           p->esize - sizeof(struct ___entry_header));

    /* Get the bucket header */
    be = &p->blist[p->hash_fn(ptr) % p->bcount];

    /* If there are no entries, the simply add to the start */
    eh->next = be->start; // point to the start
    if (!be->start)
        be->start = eh;
    /* Else install this entry as the new header */
    else
    {
        be->start->prev = eh;
        be->start = eh; // update the header
    }

    /* Success */
    return 0;
}

/***********************************************************************/
/* HashTDelete: Delete Entry from the table                            */
/*              handle = Handle                                        */
/*              ptr = Entry to be deleted                              */
/*                                                                     */
/***********************************************************************/
int HashTDelete(void *handle, void *ptr)
{
    struct ___entry_header *eh = tSearch(handle, ptr);

    /* If the entry is found, then delete */
    if (eh)
    {
        /* If next is NULL, then it's end of the list */
        if (eh->next)
            eh->next->prev = eh->prev;

        /* If prev is NULL, then it's the beginning of the list */
        if (eh->prev)
            eh->prev->next = eh->next;
        /* Set the bucket entry pointer to NULL */
        else
        {
            struct ___bucket_header *p = handle;
            struct ___bucket_entry *be;

            /* Get the bucket entry to set the pointer to NULL */
            be = &p->blist[p->hash_fn(ptr) % p->bcount];
            be->start = eh->next;
        }
        free(eh); // live free
    }

    /* Success or Failure depending on the search */
    return eh ? 0 : -1;
}

/***********************************************************************/
/* HashTSearch: Search for an entry from the table                     */
/*              handle = Handle                                        */
/*              ptr = Entry to be deleted                              */
/*                                                                     */
/***********************************************************************/
void *HashTSearch(void *handle, void *ptr)
{
    struct ___entry_header *eh = tSearch(handle, ptr); // search
    return (eh) ? eh + 1 : NULL;
}
