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
/* Given a linked list and a value x, partition it such that all nodes */
/* less than x come before nodes greater than or equal to x.           */
/*                                                                     */
/* You should preserve the original relative order of the nodes in each*/
/* of the two partitions.                                              */
/* For example,                                                        */
/* Given 1->4->3->2->5->2 and x = 3,                                   */
/* return 1->2->2->4->3->5.                                            */
/*                                                                     */
/***********************************************************************/
struct ListNode *partition(struct ListNode* head, int x)
{
    struct ListNode *lh = NULL, *lh2 = NULL, *nh = head;;
    struct ListNode *e = head, *end = NULL, *oe = NULL;
    int g = -1, s = -1;

    /* Parameters need to be sane */
    if (!head)
        return NULL;

    /* O(1) case */
    if (!head->next)
        return head;

    /* Seek the end of the list */
    do
    {
        /* Find the largest and smallest element */
        if ((g == -1) || (e->val > g))
            g = e->val;
        if ((s == -1) || (e->val < s))
            s = e->val;

        /* Get a pointer to the first node which needs to be
        relocated */
        if ((!lh) && (e->val >= x))
        {
            lh = e;
            lh2 = end;
        }

        /* Move to the next */
        end = e;
        e = e->next;
    } while (e);

    /* If the partition value is outside the range of the list
    then simply return the list */
    if ((s > x) || (g < x))
        return head;

    while (lh != oe)
    {
        /* If the value greater than target, move to the end of the list */
        if (lh->val >= x)
        {
            struct ListNode *t;
            end->next = lh;
            end = lh;
            if (oe == NULL)
                oe = end;

            /* If we are not modifying the head, there merely update the link */
            if (lh2)
            {
                lh2->next = lh->next;
                lh->next = NULL;
                lh = lh2->next;
            }

            /* Else update the head */
            else
            {
                t = lh->next;
                lh->next = NULL;
                lh = t;
                nh = lh;
            }
        }

        /* Move to the next element */
        else
        {
            lh2 = lh;
            lh = lh->next;
        }
    }

    /* Return the head */
    return nh;
}

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
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //int a[] = {1, 4, 3, 2, 5, 2};
    int a[] = {1, 1};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *l;
    l = generate_list(a, len);
    if (!l)
        return -1;
    printf("Before Partition");
    prn_list(l);
    l = partition(l, 1);
    prn_list(l);
    free_list(l);
    return 0;
}

