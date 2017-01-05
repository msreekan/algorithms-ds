/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/llist.h"

/***********************************************************************/
/* Remove all elements from a linked list of integers that have value  */
/* val.                                                                */
/* Example                                                             */
/* Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6               */
/* Return: 1 --> 2 --> 3 --> 4 --> 5                                   */
/***********************************************************************/
struct ListNode *removeElements(struct ListNode* head, int val)
{
    struct ListNode *prev = NULL, *node = head, *next;

    /* Validate */
    if (!head) return NULL;

    /* Loop while node is valid. */
    for (node = head; node; node = next)
    {
        /* Set the next node */
        next = node->next;

        /* If there is a matching node value, then delete. */
        if (node->val == val)
        {
            /* If the previous node is valid, then point it to next */
            if (prev)
                prev->next = next;
            /* Else, update the head. */
            else
                head = next;

            /* Free the node, move to the next one. */
            free(node);
        }

        /* Set the previous node */
        else
            prev = node;
    }

    /* Return the head. */
    return head;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {1,2,2,3,3,1,1,5,4,5,1};
    int len = sizeof(arr) / sizeof(int), del = 1;
    struct ListNode *head;

    /* Create the list */
    head = CreateList(arr, 0, len - 1);
    PrintList(head);
    printf("\n");

    /* Delete */
    head = removeElements(head, del);
    PrintList(head);
    FreeList(head);
    return 0;
}
