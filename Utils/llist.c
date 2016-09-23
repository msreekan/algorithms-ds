/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

/***********************************************************************/
/* CreateList: Create linked list from an integer array                */
/*                                                                     */
/***********************************************************************/
struct ListNode *CreateList(int *arr, int s, int e)
{
    struct ListNode *start, *node;
    int i = s + 1;

    /* Validate the parameters */
    if (!arr || s > e)
        return NULL;

    /* Allocate the starting node */
    if ((start = malloc(sizeof(struct ListNode))) == NULL)
        return NULL;
    start->val = arr[s];
    node = start;

    /* Loop creating the rest of the list. */
    while (i <= e)
    {
        node->next = malloc(sizeof(struct ListNode));
        if (!node->next)
            return start;
        node->next->val = arr[i++];
        node = node->next;
    }

    /* NULL terminate the last node */
    node->next = NULL;
    return start;
}

/***********************************************************************/
/* FreeList: Free a linked list.                                       */
/*                                                                     */
/***********************************************************************/
void FreeList(struct ListNode *head)
{
    struct ListNode *node;
    while(head)
    {
        node = head;
        head = head->next;
        free(node);
    }
}

/***********************************************************************/
/* PrintList: Print a linked list.                                     */
/*                                                                     */
/***********************************************************************/
void PrintList(struct ListNode *head)
{
    while(head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
}
