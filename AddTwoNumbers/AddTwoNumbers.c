/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode
{
      int val;
      struct ListNode *next;
};

/***********************************************************************/
/* free_list: Free linked list pointers                                */
/*                                                                     */
/***********************************************************************/
void free_list(struct ListNode *list)
{
    struct ListNode *next = NULL;

    /* Set all the valid nodes free */
    while(list)
    {
        next = list->next;
        free(list);
        list = next;
    }
}

/***********************************************************************/
/* You are given two linked lists representing two non-negative        */
/* numbers. The digits are stored in reverse order and each of their   */
/* nodes contain a single digit. Add the two numbers and return it as  */
/* a linked list.                                                      */
/* Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)                                */
/* Output: 7 -> 0 -> 8                                                 */
/*                                                                     */
/***********************************************************************/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode *tl1 = l1, *tl2 = l2;
    struct ListNode *nl = NULL, *nl_t = NULL;
    int c = 0;

    /* Ensure sanity */
    if (!l1 && !l2)
        return NULL;

    /* Initialize the new list */
    nl = malloc(sizeof(struct ListNode));
    if (!nl)
        return NULL;
    nl->val = 0;
    nl_t = nl;

    /* If list 1 is valid, then add the value */
    if (tl1)
    {
        nl->val = tl1->val;
        tl1 = tl1->next;
    }

    /* If list 2 is valid, then add the value */
    if (tl2)
    {
        nl->val += tl2->val;
        tl2 = tl2->next;
    }

    /* Take care of the carry */
    if (nl_t->val > 9)
    {
        c = nl_t->val / 10;
        nl_t->val %= 10;
    }

    /* Loop as long as the lists are valid */
    while (tl1 || tl2)
    {
        /* Allocate the new node */
        nl_t->next = malloc(sizeof(struct ListNode));
        if (!nl_t->next)
        {
            free_list(nl);
            return NULL;
        }

        /* Initialize it with the carry */
        nl_t = nl_t->next;
        nl_t->val = c;
        c = 0;

        /* If the list 1 is valid, then add the value */
        if (tl1)
        {
            nl_t->val += tl1->val;
            tl1 = tl1->next;
        }

        /* If the list 2 is valid, then add the value */
        if (tl2)
        {
            nl_t->val += tl2->val;
            tl2 = tl2->next;
        }

        /* Take care of the carry! */
        if (nl_t->val > 9)
        {
            c = nl_t->val / 10;
            nl_t->val %= 10;
        }
    }

    /* If the carry is valid then append the last node */
    if (c)
    {
        nl_t->next = malloc(sizeof(struct ListNode));
        if (!nl_t->next)
        {
            free_list(nl);
            return NULL;
        }
        nl_t = nl_t->next;
        nl_t->val = c;
    }

    /* Mark the end of the list and return */
    nl_t->next = NULL;
    return nl;
}

/***********************************************************************/
/* get_list: Transform an integer into a list                          */
/*                                                                     */
/***********************************************************************/
struct ListNode *get_list(unsigned val)
{
    struct ListNode *nl = NULL, *tnl = NULL;

    /* Loop converting integer into list */
    while(val)
    {
        /* Initialize the list */
        if (nl == NULL)
        {
            nl = malloc(sizeof(struct ListNode));;
            if (nl)
                tnl = nl;
            else
                return NULL;
        }

        /* Add the next node */
        else
        {
            tnl->next = malloc(sizeof(struct ListNode));;
            if (tnl->next)
                tnl = tnl->next;
            else
            {
                free_list(nl);
                return NULL;
            }
        }

        /* Add the node values */
        tnl->val = val % 10;
        tnl->next = NULL;
        val = val / 10;
    }
    return nl;
}

/***********************************************************************/
/* print_list: Print the list                                          */
/*                                                                     */
/***********************************************************************/
void print_list(struct ListNode *l1)
{
    struct ListNode *tl = l1;
    while(tl)
    {
        printf("%d->", tl->val);
        tl = tl->next;
    }
    printf("\n");
}

/***********************************************************************/
/* check_list: Compare two lists                                       */
/*                                                                     */
/***********************************************************************/
int check_list(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *t1 = l1, *t2 = l2;

    /* Loop and check while the lists are valid */
    while(t1 && t2)
    {
        if (t1->val != t2->val)
            return -1;
        t1 = t1->next;
        t2 = t2->next;
    }

    /* If either of the lists are valid then error, else success */
    if (t1 || t2)
        return -1;
    else
        return 0;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *l1, *l2, *l3, *l4;
    int i = 0;

    /* Big loop generating random numbers for testing */
    while (++i < 32)
    {
        int num1 = rand(), num2 = rand(), num3;

        /* Add the random values */
        num3 = num1 + num2;

        /* Generate the corresponding lists */
        l1 = get_list(num1);
        l2 = get_list(num2);

        /* Print the lists */
        print_list(l1);
        printf("+\n");
        print_list(l2);
        printf("-----------\n");

        /* Add the lists */
        l3 = addTwoNumbers(l1, l2);
        print_list(l3);

        /* Verify the result */
        l4 = get_list(num3);
        if (check_list(l3,l4))
        {
            printf("Error !! \n");
            print_list(l3);
            print_list(l4);
            exit(-1);
        }
        printf("\n\n");

        /* Clean up */
        free_list(l1);
        free_list(l2);
        free_list(l3);
    }
    return 0;
}

