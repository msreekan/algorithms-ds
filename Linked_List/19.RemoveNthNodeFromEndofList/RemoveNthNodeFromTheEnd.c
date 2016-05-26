/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************/
/* Linked List NODE             */
/********************************/
struct ListNode
{
    int val;
    struct ListNode *next;
};

/***********************************************************************/
/* Given a linked list, remove the nth node from the end of list and   */
/* return its head.                                                    */
/* For example: Given linked list: 1->2->3->4->5, and n = 2.           */
/*              After removing the second node from the end, the       */
/*              linked list becomes 1->2->3->5.                        */
/* Note: Given n will always be valid. Try to do this in one pass.     */
/*                                                                     */
/***********************************************************************/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    struct ListNode *nn = head, *ln = head;
    struct ListNode *tln;
    int i;

    /* Move to the nth node from the start */
    for (i = 0; i < n; ++i)
        nn = nn->next;

    /* Handle the corner case where there are only N nodes */
    if (nn == NULL)
    {
        head = head->next;
        free(ln);
        return head;
    }

    /* Traverse the list, get to the nth node from the end */
    while (nn->next != NULL)
    {
        nn = nn->next;
        ln = ln->next;
    }

    /* Break free */
    tln = ln->next;
    ln->next = ln->next->next;
    free(tln);

    /* Return new head */
    return head;
}

/***********************************************************************/
/* free_list: Free the list                                            */
/*                                                                     */
/***********************************************************************/
void free_list(struct ListNode *l)
{
    struct ListNode *tl = l;
    while (tl)
    {
        l = l->next;
        free(tl);
        tl = l;
    }
}

/***********************************************************************/
/* generate_list: Generate the list                                    */
/*                                                                     */
/***********************************************************************/
struct ListNode *generate_list(int *a, int len)
{
    struct ListNode *head, *next;
    int i = 1;

    /* Allocate the head */
    head = malloc(sizeof(struct ListNode));
    if (head == NULL)
        return NULL;
    next = head;
    head->next = NULL;
    head->val = a[0];

    /* Generate the list */
    do
    {
        next->next = malloc(sizeof(struct ListNode));
        if (next->next == NULL)
        {
            free_list(head);
            return NULL;
        }
        next = next->next;
        next->next = NULL;
        next->val = a[i];
        ++i;
    } while (i < len);

    /* Return the head */
    return head;
}

/***********************************************************************/
/* prn_list: Print the list                                            */
/*                                                                     */
/***********************************************************************/
void prn_list(struct ListNode *l)
{
    struct ListNode *tl = l;
    while(tl)
    {
        printf("%d ", tl->val);
        tl = tl->next;
    }
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *n = generate_list(a, len);
    prn_list(n);

    printf("After Nth del:\n");
    n = removeNthFromEnd(n, 2);
    prn_list(n);
    return 0;
}

