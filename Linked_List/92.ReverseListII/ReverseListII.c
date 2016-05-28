/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/***********************************************************************/
/* reversl: Reverse List!                                              */
/*                                                                     */
/***********************************************************************/
void reversl(struct ListNode *s, struct ListNode *e)
{
    struct ListNode *n1 = s, *n2 = s->next, *n3;

    /* Use two pointers and reverse the list in place*/
    n1->next = NULL;
    while (n2 != e)
    {
        n3 = n2->next;
        n2->next = n1;
        n1 = n2;
        n2 = n3;
    }
    n2->next = n1;
}
/***********************************************************************/
/* Reverse a linked list from position m to n. Do it in-place and in   */
/* one-pass.                                                           */
/*                                                                     */
/* For example:                                                        */
/* Given 1->2->3->4->5->NULL, m = 2 and n = 4,                         */
/*                                                                     */
/* return 1->4->3->2->5->NULL.                                         */
/*                                                                     */
/* Note:                                                               */
/* Given m, n satisfy the following condition:                         */
/* 1 ≤ m ≤ n ≤ length of list.                                         */
/***********************************************************************/
struct ListNode *reverseBetween(struct ListNode* head, int m, int n)
{
    struct ListNode *psr = NULL, *sr = head, *se = head, *see = head;
    int i;

    /* Ensure sanity */
    if ((!head) || (n <= m))
        return head;

    /* Seek to the node m */
    for (i = 0; i < m - 1; ++i)
    {
        psr = sr;
        sr = sr->next;
        se = se->next;
        see = see->next;
        if (!sr)
            return NULL;
    }

    /* Seek to the node n */
    for (; i < n - 1; ++i)
    {
        se = se->next;
        see = see->next;
        if (!se)
            return NULL;
    }

    /* Seek to the node beyond n */
    see = see->next;

    /* Reverse the list */
    reversl(sr, se);

    /* If the head has not changed, then update the link */
    if (psr)
      psr->next = se;
    sr->next = see;

    /* Return the old head or the new one */
    if (psr)
        return head;
    else
        return se;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *n;

    /* Generate list, print list, reverse and free */
    n = generate_list(a, len);
    if (!n)
        return -1;
    printf("Original List : \n");
    prn_list(n);
    n = reverseBetween(n, 3, 5);
    printf("Reversed List : \n");
    prn_list(n);
    free_list(n);
    return 0;
}
