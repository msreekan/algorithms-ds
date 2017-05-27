/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Utils/llist.h"

/***********************************************************************/
/* Given a singly linked list, determine if it is a palindrome.        */
/* Follow up:                                                          */
/* Could you do it in O(n) time and O(1) space?                        */
/***********************************************************************/
bool isPalindrome(struct ListNode* h)
{
    struct ListNode *s, *e1, *e2, *re;
    struct ListNode *n1 = NULL, *n2 = NULL, *n3 = NULL, *nh1, *nh2;
    int count = 0;
    bool ret = false;

    /* Validate the parameter. */
    if (!h || !h->next) return true;

    /* Use the slow and fast pointer to get to the center. */
    s = e2 = e1 = h;
    while(s)
    {
        /* Move the pointers ahead. */
        s = s->next;
        e2 = e1;
        e1 = e1->next;
        count++;

        /* Move the fast pointer again. */
        if (s) {
            s = s->next;
            count++;
        }
    }

    /* Depending on whether the links are odd/even
       set the end of the first half of the list. */
    if (count & 1)
        re = e2;
    else
        re = e1;

    /* Set the three nodes used for reversal. */
    n1 = h;
    if (n1->next)
        n2 = n1->next;
    if (n2)
        n3 = n2->next;

    /* Loop till the required end. */
    n1->next = NULL;
    while (n2 != re && n2)
    {
        n2->next = n1;
        n1 = n2;
        n2 = n3;
        if (n3)
            n3 = n3->next;
    }

    /* Compare the lists. */
    nh1 = n1;
    nh2 = e1;
    while (nh1 && nh2 && nh1->val == nh2->val)
    {
        nh1 = nh1->next;
        nh2 = nh2->next;
    }

    /* If it's the end of the list, then palindrome. */
    if (!nh1 && !nh2)
        ret = true;

    /* Reverse back the list. */
    n2 = n1->next;
    n1->next = re; // link back to the original list
    if (n2)
        n3 = n2->next;
    while (n2)
    {
        n2->next = n1;
        n1 = n2;
        n2 = n3;
        if (n3)
            n3 = n3->next;
    }

    /* Return the status. */
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *n = CreateList(a, 0, len - 1);
    PrintList(n);
    printf("Is Palindrome %d:\n", isPalindrome(n));
    PrintList(n);
    FreeList(n);
    return 0;
}
