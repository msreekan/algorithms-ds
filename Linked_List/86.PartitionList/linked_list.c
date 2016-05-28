/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Linked List Routines                                                */
/***********************************************************************/

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
