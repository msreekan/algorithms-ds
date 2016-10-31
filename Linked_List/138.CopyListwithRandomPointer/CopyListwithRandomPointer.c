/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/hasht.h"

/***********************************/
/* Data Structure                  */
/***********************************/
struct RandomListNode
{
    int label;
    struct RandomListNode *next;
    struct RandomListNode *random;
};

/***********************************/
/* Macros                          */
/***********************************/
#define HASH_BUCKET_COUNT        1024
#define MAX_NODES 8

/***********************************************************************/
/* HashFn: Generate hash                                               */
/*                                                                     */
/***********************************************************************/
int HashFn(void *ptr)
{
    struct RandomListNode **node = ptr;
    return (int)*node; // merely return the address
}

/***********************************************************************/
/* HashCmp: Compare hash                                               */
/*                                                                     */
/***********************************************************************/
int HashCmp(void *ptr1, void *ptr2)
{
    struct RandomListNode **node1 = ptr1;
    struct RandomListNode **node2 = ptr2;
    return *node1 == *node2 ? 0 : 1; // if equal, return 0
}

/***********************************************************************/
/* A linked list is given such that each node contains an additional   */
/* random pointer which could point to any node in the list or null.   */
/* Return a deep copy of the list.                                     */
/***********************************************************************/
struct RandomListNode *copyRandomList(struct RandomListNode *head)
{
    void *hasht;
    struct RandomListNode *start = head, *next, *nstart = NULL;
    struct RandomListNode *nret = NULL, *prev = NULL ;
    struct RandomListNode *npair[2];
    struct RandomListNode **nhtpair;

    /* Allocate the hash table to hold the pointer pair. */
    if (!(hasht = HashTAlloc(HASH_BUCKET_COUNT,
                  sizeof(struct RandomListNode *) * 2, HashFn, HashCmp)))
        return NULL;

    /* Run through the linked list */
    while (start)
    {
        /* Allocate the new node */
        if (!(next = malloc(sizeof(struct RandomListNode))))
            goto __exit;

        /* Record the list head */
        if (!nstart)
            nstart = next;

        /* Copy the contents */
        next->label = start->label;
        next->next = NULL;
        next->random = start->random;
        if (prev)
            prev->next = next;
        prev = next;

        /* Assign the node pair */
        npair[0] = start;
        npair[1] = next;

        /* Add the pair to the hash table */
        if (HashTAdd(hasht, &npair))
            goto __exit;

        /* Goto the next node */
        start = start->next;
    }

    /* Now populate the random */
    next = nstart;
    while (next)
    {
        /* Get the pair. */
        if (next->random && (!(nhtpair = HashTSearch(hasht, &next->random))))
            goto __exit;

        /* Pick the newly allocated memory */
        if (next->random)
            next->random = nhtpair[1];
        next = next->next; // next node
    }

    /* Assign the return */
    nret = nstart;
    nstart = NULL;
__exit:
    if (hasht) HashTFree(hasht);
    if (nstart)
        while(nstart) {
            next = nstart;
            nstart = nstart->next;
            free(next);
        }
    return nret;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct RandomListNode *nodelst[MAX_NODES];
    struct RandomListNode *start, *nstart, *next;
    int i;

    /* Loop allocating nodes */
    for (i = 0; i < MAX_NODES; ++i) {
        if (!(nodelst[i] = malloc(sizeof(struct RandomListNode))))
            return -1;
        nodelst[i]->label = i;
        /* Point the previous node to the next one */
        if (i) nodelst[i - 1]->next = nodelst[i];
    }
    nodelst[i - 1]->next = NULL; //NULL terminate

    /* Now generate the linked list with random pointers */
    for (i = 0; i < MAX_NODES; ++i)
        nodelst[i]->random = nodelst[rand() % MAX_NODES];

    /* Generate the copy */
    nstart = copyRandomList(nodelst[0]);
    start = nodelst[0];
    next = nstart;
    while (next)
    {
        /* If the values or the random values do not match, return */
        if ((next->label != start->label) ||
            (next->random && !start->random) ||
            (!next->random && start->random) ||
            (next->random && (start->random->label != next->random->label)))
        {
            printf("Error :");
            return -1;
        }
        next = next->next;
        start = start->next;
        if ((!start && next) || (!next && start))
            return -1;
    }

    /* Free the copy and the original list */
    start = nodelst[0];
    while (nstart)
    {
        next = nstart;
        nstart = nstart->next;
        free(next);
        next = start;
        start = start->next;
        free(next);
    }

    return 0;
}
