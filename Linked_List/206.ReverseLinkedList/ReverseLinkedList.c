/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/llist.h"

#define RECURSIVE 1

#if RECURSIVE
/***********************************************************************/
/* rlist: Recursive reverse!                                           */
/*                                                                     */
/***********************************************************************/
struct ListNode *rlist(struct ListNode* node, struct ListNode *next)
{
    struct ListNode *nnext;

    /* Return if we are done. */
    if (!next)
        return node;

    /* Save the next pointer */
    nnext = next->next;
    next->next = node;
    return rlist(next, nnext);
}

/***********************************************************************/
/* Reverse a singly linked list.                                       */
/***********************************************************************/
struct ListNode* reverseList(struct ListNode* head)
{
    /* Validate. */
    if (!head) return NULL;

    /* Recursive reversal. */
    return rlist(NULL, head);
}

#else
/***********************************************************************/
/* Reverse a singly linked list.                                       */
/***********************************************************************/
struct ListNode* reverseList(struct ListNode* head)
{
    struct ListNode *node = head, *ntnode, *np = NULL;

    /* Validate. */
    if (!head) return NULL;

    /* Loop while the nodes are valid. */
    while (node)
    {
        ntnode = node->next;
        node->next = np;
        np = node;
        node = ntnode;
    }

    /* Return the new head. */
    return np;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 5, 7, 7, 8, 2, 1, 3, 9};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *head;

    head = CreateList(a, 0, len - 1);
    PrintList(head);
    printf("\n");

    head = reverseList(head);
    PrintList(head);

    FreeList(head);
    return 0;
}
