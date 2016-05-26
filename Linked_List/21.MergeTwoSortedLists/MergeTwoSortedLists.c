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
/* Merge two sorted linked lists and return it as a new list. The new  */
/* list should be made by splicing together the nodes of the first two */
/* lists.                                                              */
/*                                                                     */
/***********************************************************************/
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode *sl1 = l1, *sl2 = l2;
    struct ListNode *snl = NULL, *nl = NULL;

    /* If both the lists are valid, then initialize the head
       after comparison */
    if ((sl1) && (sl2))
    {
        /* Smaller value gets to be the head */
        if (sl1->val > sl2->val)
        {
            nl = sl2;
            sl2 = sl2->next;
        }
        else
        {
            nl = sl1;
            sl1 = sl1->next;
        }
    }

    /* Else we pick the valid list */
    else if (sl1)
    {
        nl = sl1;
        sl1 = sl1->next;
    }

    else if (sl2)
    {
        nl = sl2;
        sl2 = sl2->next;
    }

    /* Merge as long as there are valid elements left */
    snl = nl;
    while (sl1 || sl2)
    {
        /* If both the lists are valid, we need to pick the smaller
        value */
        if ((sl1) && (sl2))
        {
            if (sl1->val > sl2->val)
            {
                nl->next = sl2;
                nl = nl->next;
                sl2 = sl2->next;
            }
            else
            {
                nl->next = sl1;
                nl = nl->next;
                sl1 = sl1->next;
            }
        }

        /* Else pick the remaining valid list */
        else if (sl1)
        {
            nl->next = sl1;
            nl = nl->next;
            sl1 = sl1->next;
        }
        else if (sl2)
        {
            nl->next = sl2;
            nl = nl->next;
            sl2 = sl2->next;
        }
    }

    /* NULL termination */
    if (nl)
        nl->next = NULL;

    /* Return the merged list */
    return snl;
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

    /* Initialize the head */
    head = malloc(sizeof(struct ListNode));
    if (head == NULL)
        return NULL;
    next = head;
    head->next = NULL;
    head->val = a[0];

    /* Create the new list */
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
    printf("\n");
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {11, 23, 33, 44, 55, 70};
    int alen = sizeof(a) / sizeof(int);
    int b[] = {12, 24, 53, 64, 85, 170};
    int blen = sizeof(b) / sizeof(int);
    struct ListNode *l1, *l2, *l3;

    l1 = generate_list(a, alen);
    if (l1 == NULL)
        exit(-1);
    prn_list(l1);
    l2 = generate_list(b, blen);
    if (l2 == NULL)
        exit(-1);
    prn_list(l2);
    l3 = mergeTwoLists(l1, l2);
    prn_list(l3);
    free_list(l3);
    return 0;
}

