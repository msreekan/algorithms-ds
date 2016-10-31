/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/hasht.h"

/**************************************/
/* Data Structures                    */
/**************************************/
/* Global LRU Cache Handle */
struct LRUCache
{
    int sz;
    int used_cnt;
    struct LRUEntry *list;
    struct LRUEntry *head;
    struct LRUEntry *tail;
    void *hasht;
};

/*
** Cache Entry
*/
struct LRUEntry
{
    int key; // keep the key as the first ui32 vaue for hash functions
    int val;
    struct LRUEntry *next; // LRU Queue
    struct LRUEntry *prev;
};

/* Global Cache Instance */
struct LRUCache *LRUc;

/***********************************************************************/
/* HashFn: Generate Hash                                               */
/*                                                                     */
/***********************************************************************/
int HashFn(void *ptr)
{
    int key = **(int **)ptr;
    return key;
}

/***********************************************************************/
/* HashCmp: Compare entries                                            */
/*                                                                     */
/***********************************************************************/
int HashCmp(void *ptr1, void *ptr2)
{
    int key1 = **(int **)ptr1;
    int key2 = **(int **)ptr2;
    return key1 == key2 ? 0 : 1;
}

/***********************************************************************/
/* lruListUpdate: Update the queue to reflect the new priorities!      */
/*                                                                     */
/***********************************************************************/
static void lruListUpdate(struct LRUEntry *lru_ent)
{
    /* Head of the list was picked */
    if (lru_ent == LRUc->head && lru_ent->prev) {
        LRUc->head = lru_ent->prev;
        LRUc->head->next = NULL;
    }

    /* If it's an intermediate node, then delete it and push to the
    end. */
    else if (lru_ent->next && lru_ent->prev) {
        lru_ent->prev->next = lru_ent->next;
        lru_ent->next->prev = lru_ent->prev;
    }

    /* If it's not already the tail, then update. */
    if (lru_ent != LRUc->tail) {
        LRUc->tail->prev = lru_ent;
        lru_ent->next = LRUc->tail;
        LRUc->tail = lru_ent;
        lru_ent->prev = NULL;
    }
}

/***********************************************************************/
/* Design and implement a data structure for Least Recently Used (LRU) */
/* cache. It should support the following operations: get and set.     */
/*                                                                     */
/* get(key) - Get the value (will always be positive) of the key if    */
/* the key exists in the cache, otherwise return -1.                   */
/* set(key, value) - Set or insert the value if the key is not already */
/* present. When the cache reached its capacity, it should invalidate  */
/* the least recently used item before inserting a new item.           */
/***********************************************************************/
void lruCacheInit(int capacity)
{
    /* Initialize the cache */
    /* If the cache is not initialized, then do the same */
    if (!LRUc) {
        /* Allocate cache book keeping information and the entries. */
        LRUc = calloc(sizeof(struct LRUCache) + (sizeof(struct LRUEntry)
                      * capacity), sizeof(char));
        if (!LRUc) exit(-1);

        /* Initialize the cache */
        LRUc->sz = capacity;
        LRUc->used_cnt = 0;
        LRUc->list = (struct LRUEntry *)(LRUc + 1);
        LRUc->head = NULL;
        LRUc->tail = NULL;

        /* Create a hash table */
        LRUc->hasht = HashTAlloc(capacity, sizeof(struct LRUEntry *),
                                 HashFn, HashCmp);
        if (!LRUc->hasht) {
            free(LRUc);
            exit(-1);
        }
    }
}

/***********************************************************************/
/* lruCacheFree: Free the cache list!                                  */
/*                                                                     */
/***********************************************************************/
void lruCacheFree()
{
    /* Free the cache */
    if (!LRUc) return;
    HashTFree(LRUc->hasht);
    free(LRUc);
    LRUc = NULL;
}

/***********************************************************************/
/* lruCacheGet: Get a cache entry!                                     */
/*                                                                     */
/***********************************************************************/
int lruCacheGet(int key)
{
    int *key_ptr = &key;
    struct LRUEntry **lru_entptr = HashTSearch(LRUc->hasht, &key_ptr);

    /* Return -1 if not found, else update and return value */
    if (lru_entptr)
        lruListUpdate(*lru_entptr);
    return lru_entptr == NULL ? -1 : (*lru_entptr)->val;
}

/***********************************************************************/
/* lruCacheSet: Set a cache entry!                                     */
/*                                                                     */
/***********************************************************************/
void lruCacheSet(int key, int value)
{
    struct LRUEntry *lru_ent;
    int *key_ptr = &key;
    struct LRUEntry **lru_entptr = HashTSearch(LRUc->hasht, &key_ptr);

    /* Get the entry if it's already present */
    if (lru_entptr)
        lru_ent = *lru_entptr;

    /* If entry not present, then pick the next available location
    or the head of the LRU Q. */
    else {
        /* If there is space left in the cache, then pick that */
        if (LRUc->sz > LRUc->used_cnt) {
            lru_ent = &LRUc->list[LRUc->used_cnt];

            /* Increment the used count. */
            LRUc->used_cnt++;
            if (!LRUc->head && !LRUc->tail) {
                LRUc->head = lru_ent;
                LRUc->tail = lru_ent;
            }

            /* Add the entry */
            lru_ent->key = key;
            if (HashTAdd(LRUc->hasht, &lru_ent))
                exit(-1);
        }
        /* Else select the head of the LRU queue */
        else {
            void *ptr = HashTRemove(LRUc->hasht, &LRUc->head);

            /* Change the values. */
            lru_ent = LRUc->head;
            lru_ent->key = key;

            /* Remap the hash */
            if (HashTRemap(LRUc->hasht, ptr))
                exit(-1);
        }
    }
    /* Update the value and the queue */
    lru_ent->val = value;
    lruListUpdate(lru_ent);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int v[] = {1,1,1,10,5,3,3,3,4, 5,55, 6, 6, 7, 7, 8, 9, 1, 2, 2, 3, 4, 4};
    int k[] = {2,1,4,9,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int g[] = {-1,-1,2,-1,1,2,-2,1,-1,1,2,3,4,5,-2}; // get keys
    int rv[] = {-1,-1,1,-1,1,1,2,-1,-1,-1,2,3,-1,5}; // expected result
    int len = sizeof(v) / sizeof(int), i, j = 0, size = 10, res;

    /* Initialize the cache */
    lruCacheInit(size);
    for (i = 0; i < len; ++i)
    {
        /* Check cache get */
        for (;g[j] != -1 && g[j] != -2; j++) {
            res = lruCacheGet(g[j]); // get the value
            if (res != rv[j]) // verify
                printf("Error : Key = %d Result = %d Expected = %d \n",
                       g[j], res, rv[j]);
        }

        /* If it's not the end of the list, then increment */
        if (g[j] != -2) j++;
        lruCacheSet(k[i], v[i]);
    }
    lruCacheFree();
    return 0;
}
