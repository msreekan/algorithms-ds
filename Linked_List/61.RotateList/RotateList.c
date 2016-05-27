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
/* Given a list, rotate the list to the right by k places, where k is  */
/* non-negative.                                                       */
/* For example:                                                        */
/* Given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.    */
/***********************************************************************/
struct ListNode* rotateRight(struct ListNode *head, int k)
{
    int i;
    struct ListNode *le, *lh;
    int len = 0;

    /* Ensure sanity */
    if (!head)
        return head;

    /* Assign the markers */
    le = head;
    lh = head;

    /* Scan k elements */
    for (i = 0; i < k; ++i)
    {
        le = le->next;
        len++;

        /* If the list is smaller than k elements,
        then break */
        if(!le)
        {
            le = head;
            break;
        }
    }

    /* If the list is smaller than the rotate length, then
    calculate the modulus. Much faster than looping around n times */
    if (len != k)
    {
        /* Modulus of k */
        k = k % len;

        /* Scan modulus of k elements */
        for (i = 0; i < k; ++i)
            le = le->next;
    }

    /* Set markers to the last k elements */
    while (le->next)
    {
        le = le->next;
        lh = lh->next;
    }

    /* Append the list to the front */
    le->next = head;
    head = lh->next;
    lh->next = NULL;
    return head;
}

/***********************************************************************/
/* free_list: Free the list                                            */
/*                                                                     */
/***********************************************************************/
void free_list(struct ListNode *l)
{
    struct ListNode *n = l;
    while (l)
    {
        n = l->next;
        free(l);
        l = n;
    }
}

/***********************************************************************/
/* prn_list: Print list                                                */
/*                                                                     */
/***********************************************************************/
void prn_list(struct ListNode *l)
{
    struct ListNode *n = l;
    while (l)
    {
        printf("%d-> ", l->val);
        n = l->next;
        l = n;
    }
    printf(" NULL\n");
}

/***********************************************************************/
/* generate_list: Generate list from an array                          */
/*                                                                     */
/***********************************************************************/
struct ListNode *generate_list(int *a, int len)
{
    struct ListNode *s, *n;
    int i;

    /* Ensure sanity of parameters */
    if (!a || !len)
        return NULL;

    /* Initialize the head */
    s = malloc(sizeof(struct ListNode));
    if (!s)
        return NULL;
    s->val = a[0];
    n = s;

    /* Generate the list */
    for (i = 1; i < len; ++i)
    {
        n->next = malloc(sizeof(struct ListNode));
        if (!n->next )
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
    int a[] = {1, 2, 3};
    int r = 2000000001, len = sizeof(a) / sizeof(int);
    struct ListNode *s;

    s = generate_list(a, len);
    if (s)
    {
        printf("Before Rotation :\n");
        prn_list(s);
        s = rotateRight(s, r);
        printf("After Rotation :\n");
        prn_list(s);
        free_list(s);
    }
    return 0;
}

