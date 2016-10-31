/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/llist.h"

/******************************************/
/* Macros                                 */
/******************************************/
#define MAX_NODES    10
#define O_1          1

 #if O_1
/***********************************************************************/
/* Given a singly linked list L: L0→L1→…→Ln-1→Ln,                      */
/* reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…                              */
/*                                                                     */
/* You must do this in-place without altering the nodes' values.       */
/*                                                                     */
/* For example,                                                        */
/* Given {1,2,3,4}, reorder it to {1,4,2,3}.                           */
/***********************************************************************/
void reorderList(struct ListNode* head)
{
    struct ListNode *l0 = head, *l1 = head ? head->next : head;
    struct ListNode *prev, *p, *next, *nextp;

    /* Return if there are <= 2 nodes */
    if (!l1 || !l1->next)
        return;

    /* Split the linked list into 2 */
    while (l1)
    {
        l0 = l0->next;
        l1 = l1->next;
        if (l1)
            l1 = l1->next;
    }
    prev = l0;
    l0 = l0->next;
    prev->next = NULL;

    /* Reverse the second list */
    prev = NULL;
    p = l0;
    next = p->next;
    while (next) {
            p->next = prev;
            prev = p;
            p = next;
            next = next->next;
    }
    p->next = prev;

    /* Merge the two lists */
    l0 = head;
    l1 = p;
    while (p) {
        next = l0->next;
        l0->next = p;
        nextp = p->next;
        p->next = next;
        l0 = next;
        p = nextp;
    }
}

#elif O_N
/***********************************************************************/
/* Given a singly linked list L: L0→L1→…→Ln-1→Ln,                      */
/* reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…                              */
/*                                                                     */
/* You must do this in-place without altering the nodes' values.       */
/*                                                                     */
/* For example,                                                        */
/* Given {1,2,3,4}, reorder it to {1,4,2,3}.                           */
/***********************************************************************/
void reorderList(struct ListNode* head)
{
    struct ListNode *last = head;
    struct ListNode **list;
    int size = 0, i, j;

    /* Return if there is only one node */
    if (!head)
        return;

    /* Find the number of nodes */
    while (last) {
        size++;
        last = last->next;
    }

    /* Allocate the array */
    if (!(list = malloc(sizeof(struct ListNode *) * size)))
        return;

    /* Populate the array */
    last = head;
    for (i = 0; i < size; ++i, last = last->next)
        list[i] = last;

    /* Reorder */
    for (i = 0, j = size - 1; i < j; ++i, --j)
    {
        if (list[j] != list[i]->next) // last points to start->next
            list[j]->next = list[i]->next;
        list[i]->next = list[j]; //start->next points to last
        if (j - 1 != i)
            list[j - 1]->next = NULL; // second last becomes the new last
    }

    /* Free and return */
    free(list);
}
#endif
/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *list[MAX_NODES] = {NULL};
    struct ListNode *start;
    int i;


    /* Allocate the list */
    for (i = 0; i < MAX_NODES; ++i) {
        if (!(list[i] = malloc(sizeof(struct ListNode))))
            goto __exit;
        list[i]->val = i;
        if (i) list[i - 1]->next = list[i];
    }
    list[i - 1]->next = NULL;
    start = list[0];
    while(start) {
        printf("%d, ", start->val);
        start = start->next;
    }
    printf("\n");

    /* Reorder */
    reorderList(list[0]);
    start = list[0];
    while(start) {
        printf("%d, ", start->val);
        start = start->next;
    }
__exit:
    for (i = 0; i < MAX_NODES; ++i)
        if (list[i]) free(list[i]);
    return 0;
}
