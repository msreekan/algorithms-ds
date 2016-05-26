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
void free_list(struct ListNode *l)
{
    struct ListNode *n = l, *nn;
    while(n)
    {
        nn = n->next;
        free(n);
        n = nn;
    }
}

/***********************************************************************/
/* generate_list: Generate the list                                    */
/*                                                                     */
/***********************************************************************/
struct ListNode *generate_list(int *a, int len)
{
    int i;
    struct ListNode *start, *n;

    /* Allocate the head */
    start = malloc(sizeof(struct ListNode));
    if (!start)
        return NULL;
    start->val = a[0];
    start->next = NULL;
    n = start;

    /* Generate the list */
    for (i = 1; i < len; ++i)
    {
        n->next = malloc(sizeof(struct ListNode));
        if (!n->next)
            free_list(start);
        n = n->next;
        n->val = a[i];
    }

    /* NULL terminate and return */
    n->next = NULL;
    return start;
}

/***********************************************************************/
/* generate_array: Generate a random array                             */
/*                                                                     */
/***********************************************************************/
int *generate_array(int len)
{
    int i, seed = rand();
    int *a;

    a = malloc(sizeof(int) * len);
    if (!a)
        exit(-1);
    for (i = 0; i < len; ++i)
        a[i] = seed + (i * 2);
    return a;
}

/***********************************************************************/
/* prn_list: Print the list                                            */
/*                                                                     */
/***********************************************************************/
void prn_list(struct ListNode *l1)
{
    struct ListNode *sl = l1;
    while(sl)
    {
        printf("%d-> ", sl->val);
        sl = sl->next;
    }
    printf("NULL \n");
}

/***********************************************************************/
/* Given a linked list, swap every two adjacent nodes and return its   */
/* head.                                                               */
/***********************************************************************/
struct ListNode *swapPairs(struct ListNode* head)
{
    struct ListNode *n = head, *nn = NULL, *nh = NULL, *pn = NULL;

    /* Maintain non-NULL references */
    if (!n)
        return n;

    /* Special case where there is only one node */
    if (!(n->next))
        return head;

    /* Else move to the next node */
    else
    {
        nn = n->next->next;
        nh = n->next;
    }

    /* Reverse pairs while the list is valid. */
    while(n)
    {
        struct ListNode *t = n->next;

        /* n now would point to next->next */
        n->next = nn;
        /* previous next now points to n */
        t->next = n;
        /* Reversal of the first pair complete */

        /* Link the previous reversed pair to the above change */
        if (pn)
            pn->next = t;

        /* Present pair becomes the previous pair */
        pn = n;

        /* Move to the next pair */
        n = nn;
        if ((nn) && (nn->next))
            nn = nn->next->next;
        else if (nn)
            break;
    }

    /* Return the new head */
    return nh;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int *al;
    struct ListNode *l;
    int len = 7;

    /* Generate array and list. Then print, free array, swap list pairs,
     print and free */
    al = generate_array(len);
    l = generate_list(al, len);
    prn_list(l);
    free(al);
    l = swapPairs(l);
    prn_list(l);
    free_list(l);

    /* Done */
    return 0;
}

