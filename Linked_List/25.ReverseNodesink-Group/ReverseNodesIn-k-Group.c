#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/***********************************************************************/
/* reverseKGroup: Reverse k groups                                     */
/*                                                                     */
/***********************************************************************/
struct ListNode *reverse_list(struct ListNode *start,
                              struct ListNode *end)
{
    struct ListNode *n1 = start, *n2 = n1->next, *n3 = n2->next;
    struct ListNode *n_end = end;

    /* Loop till the last element points to end. */
    while (n3 != end->next)
    {
        /*  reverse the pointer */
        n2->next = n1;

        /* move previous pointer to the present one */
        n1 = n2;

        /* set the next element as the previously saved next->next */
        n2 = n3;

        /* new next->next */
        n3 = n3->next;

        /* Seek the new end */
        if (n_end)
            n_end = n_end->next;
    }

    /* Again seek the new end, we need to run this couple of more times
    because the above loop executes only k - 2 iterations */
    if (n_end)
    {
        n_end = n_end->next;
        if (n_end)
            n_end = n_end->next;
    }

    /*  reverse the last pointer */
    n2->next = n1;

    /*  Return the new end */
    return n_end;
}

/***********************************************************************/
/* Given a linked list, reverse the nodes of a linked list k at a time */
/* and return its modified list.                                       */
/* If the number of nodes is not a multiple of k then left-out nodes in*/
/* the end should remain as it is.                                     */
/* You may not alter the values in the nodes, only nodes itself may be */
/* changed.                                                            */
/* Only constant memory is allowed.                                    */
/*                                                                     */
/* For example,                                                        */
/* Given this linked list: 1->2->3->4->5                               */
/*                                                                     */
/* For k = 2, you should return: 2->1->4->3->5                         */
/*                                                                     */
/* For k = 3, you should return: 3->2->1->4->5                         */
/*                                                                     */
/***********************************************************************/
struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    int i;
    struct ListNode *end = head, *rlist_h = head, *new_h = head;
    struct ListNode *prev_en, *prev_t;
    int n = k;

    /* Maintain sanity */
    if (!head || (k <= 1))
        return head;

    /* Run through the list till we reach the nth element */
    for (i = 0; i < (n - 1); ++i)
    {
        /* if end is valid then move to the next element */
        if (end->next)
            end = end->next;

        /* else return the new head */
        else
            return new_h;
    }

    /* loop till all the elements are exhausted */
    do
    {
        /* Before the reversal save pointer to next segment */
        prev_en = end->next;

        /* If it's the first section, then save the new head */
        if (rlist_h == head)
            new_h = end;

        /* Else link the previous tail to the new head */
        else
            prev_t->next = end;

        /* Reverse, return the next segment end, an optimization! */
        end = reverse_list(rlist_h, end);

        /* Save the present reversed tail as the previous tail */
        prev_t = rlist_h;

        /* Present head becomes the new previous
           segment tail, link it to the new segment */
        rlist_h->next = prev_en;

        /* Next segment list head and tail */
        rlist_h = prev_en;
    } while(end);

    /* return the new start node */
    return new_h;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *k_list, *rk_list;
    int k = 12;
    int arr[] = {23, 45, 67, 88, 99, 100, 101, 112, 115, 200, 25, 65,
                 77, 98, 109, 110, 121, 132, 145, 240, 26, 85, 97, 108,
                 119, 12, 13, 14, 158, 20, 27, 95, 7, 118, 129, 10,
                 141, 152, 165, 200, 28, 105, 117, 128, 39, 140, 15, 12,
                 175, 200, 63, 75, 87, 98, 99, 100, 151, 162, 280};

    /* Convert array into linked list */
    k_list = generate_list(arr, sizeof(arr) / sizeof(int));
    prn_list(k_list);

    /* Rever, print and free */
    printf("\nReversing every %d nodes....\n", k);
    rk_list = reverseKGroup(k_list, k);
    prn_list(rk_list);
    free_list(rk_list);
    return 0;
}
