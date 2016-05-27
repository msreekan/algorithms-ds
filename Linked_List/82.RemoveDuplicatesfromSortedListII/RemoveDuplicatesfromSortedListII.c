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
/* del_dups: Delete nodes which matches a value                        */
/*                                                                     */
/***********************************************************************/
struct ListNode *del_dups(struct ListNode *s, int val)
{
    struct ListNode *n = s;
    while ((s) && (s->val == val))
    {
        n = s->next;
        free(s);
        s = n;
    }

    /* New head */
    return n;
}

/***********************************************************************/
/* Given a sorted linked list, delete all nodes that have duplicate    */
/* numbers, leaving only distinct numbers from the original list.      */
/*                                                                     */
/* For example,                                                        */
/* Given 1->2->3->3->4->4->5, return 1->2->5.                          */
/* Given 1->1->1->2->3, return 2->3.                                   */
/***********************************************************************/
struct ListNode *deleteDuplicates(struct ListNode* head)
{
    struct ListNode *s = head, *ns = head, *pn;

    /* Ensure sanity */
    if (!s || !s->next)
        return s;

    /* Scan the list */
    while (s)
    {
        /* If the node has duplicates, then initiate deletion
        process */
        if ((s->next) && (s->val == s->next->val))
        {
            /* If needed, update the head */
            if (s == ns)
                ns = s = del_dups(s, s->val);

            /* Else update the previous link */
            else
                pn->next = s = del_dups(s, s->val);
        }

        /* Else, move on */
        else
        {
            pn = s;
            s = s->next;
        }
    }

    /* Return the new head */
    return ns;
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

