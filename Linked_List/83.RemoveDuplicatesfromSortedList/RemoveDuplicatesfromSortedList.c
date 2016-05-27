/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************/
/* Linked list NODE             */
/********************************/
struct ListNode
{
      int val;
      struct ListNode *next;
};

/***********************************************************************/
/* free_list: Free the list                                            */
/*                                                                     */
/***********************************************************************/
void free_list(struct ListNode *s)
{
    struct ListNode *n = s;
    while (s)
    {
        n = s->next;
        free(s);
        s = n;
    }
}

/***********************************************************************/
/* prn_list: Print the list                                            */
/*                                                                     */
/***********************************************************************/
void prn_list(struct ListNode *s)
{
    while (s)
    {
        printf("%d-> ", s->val);
        s = s->next;
    }
    printf("\n");
}

/***********************************************************************/
/* generate_list: Generate list                                        */
/*                                                                     */
/***********************************************************************/
struct ListNode *generate_list(int *a, int len)
{
    int i;
    struct ListNode *s, *n;

    /* Ensure Sanity */
    if (!a || !len)
        return NULL;

    /* Allocate the header */
    s = malloc(sizeof(struct ListNode));
    if(!s)
        return NULL;
    s->val = a[0];
    n = s;

    /* Create the list */
    for (i = 1; i < len; ++i)
    {
        n->next = malloc(sizeof(struct ListNode));
        if (!n->next)
        {
            free_list(s);
            return NULL;
        }
        n = n->next;
        n->val = a[i];
    }
    n->next = NULL;
    return s;
}

/***********************************************************************/
/* del_dups: Delete duplicates                                          */
/*                                                                     */
/***********************************************************************/
struct ListNode *del_dups(struct ListNode *s)
{
    struct ListNode *n = s;
    while (s)
    {
        n = s->next;
        if (!n || (s->val != n->val))
            break;
        free(s);
        s = n;
    }
    return n;
}

/***********************************************************************/
/* Given a sorted linked list, delete all duplicates such that each    */
/* element appear only once.                                           */
/*                                                                     */
/* For example,                                                        */
/* Given 1->1->2, return 1->2.                                         */
/* Given 1->1->2->3->3, return 1->2->3.                                */
/***********************************************************************/
struct ListNode *deleteDuplicates(struct ListNode* head)
{
    struct ListNode *s = head;

    /* Ensure parameters are sane */
    if (!s || !s->next)
        return s;

    /* Identify and eliminate duplicates */
    while (s)
    {
        if ((s->next) && (s->val == s->next->val))
            s->next = del_dups(s->next);
        s = s->next;
    }

    /* Head */
    return head;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 1, 2, 3, 3};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *n;

    /* Generate a list */
    n = generate_list(a, len);
    if (!n)
        return -1;

    /* Print, delete duplicates and then print */
    printf("Original List : \n");
    prn_list(n);
    n = deleteDuplicates(n);
    printf("Dup Deleted List : \n");
    prn_list(n);
    free_list(n);
    return 0;
}

