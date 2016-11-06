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
/* Sort a linked list using insertion sort.                            */
/***********************************************************************/
struct ListNode *insertionSortList(struct ListNode* head)
{
    struct ListNode *pnext = head, *next = head ? head->next : head;
    struct ListNode *start;

    /* Find the first out of place value */
    while (pnext && next && pnext->val <= next->val) {
            pnext = next;
            next = next->next;
    }

    /* Loop while there are unsorted nodes. */
    while (next)
    {
        /* Initialize this to the head of the list */
        start = head;

        /* Handle the special case where head needs to be modified */
        if (start->val > next->val) {
            pnext->next = next->next;
            next->next = start;
            head = next;
            next = pnext->next;
        }
        else {
            /* Loop seeking the location */
            while (start->next != next && start->next->val <= next->val)
                start = start->next;

            /* If we have a location with value greater than the one at next,
            then insert "next" here. */
            if (start->next->val > next->val){
                pnext->next = next->next;
                next->next = start->next;
                start->next = next;
                next = pnext->next;
            }
        }

        /* Find the next out of place node */
        while (pnext && next && pnext->val <= next->val) {
            pnext = next;
            next = next->next;
        }
    }

    /* Return sorted head */
    return head;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {5, 2, 4, 3, 6, 5, 6, 7, 7, 1, 2};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *root;
    root = CreateList(a, 0, len - 1);
    PrintList(root);
    printf("\n");
    root = insertionSortList(root);
    PrintList(root);
    FreeList(root);
    return 0;
}
