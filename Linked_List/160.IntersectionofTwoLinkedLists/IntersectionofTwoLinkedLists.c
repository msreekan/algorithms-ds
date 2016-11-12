/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/llist.h"

/***********************************************************************/
/* Write a program to find the node at which the intersection of two   */
/* singly linked lists begins.                                         */
/* A:          a1 → a2                                                 */
/*                   ↘                                                 */
/*                     c1 → c2 → c3                                    */
/*                   ↗                                                 */
/* B:     b1 → b2 → b3                                                 */
/*                                                                     */
/***********************************************************************/
struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB)
{
    struct ListNode *node1 = headA, *node2 = headB;
    int lenA = 0, lenB = 0;

    /* Find the length of the lists */
    while (node1 || node2){
        if (node1) {
            node1 = node1->next;
            lenA++;
        }
        if (node2) {
            node2 = node2->next;
            lenB++;
        }
    }

    /* Move the first or second list pointer based on the difference */
    node1 = headA;
    node2 = headB;
    /* Scan forward to cover the difference in length */
    while (lenA > lenB) {
        node1 = node1->next;
        --lenA;
    }
    while (lenB > lenA) {
        node2 = node2->next;
        --lenB;
    }

    /* Now scan both the lists together to find the intersection */
    while (node1 != node2 && node1 && node2) {
        node1 = node1->next;
        node2 = node2->next;
    }

    /* Return the intersection */
    return node1;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *list1[10] = {0}, *list2[5] = {0};
    struct ListNode *intersection = NULL;
    int i, l1 = sizeof(list1) / sizeof(struct ListNode *);
    int l2 = sizeof(list2) / sizeof(struct ListNode *);

    /* Create the list */
    for (i = 0; i < l1; ++i)
    {
        /* Allocate the nodes */
        if (!(list1[i] = malloc(sizeof(struct ListNode))))
            goto __exit;
        list1[i]->val = i;
        if (i) list1[i - 1]->next = list1[i]; // link them
    }
    list1[i - 1]->next = NULL;

    /* Generate the second list */
    for (i = 0; i < l2; ++i)
    {
        /* Allocate nodes */
        if (!(list2[i] = malloc(sizeof(struct ListNode))))
            goto __exit;
        list2[i]->val = i;
        if (i) list2[i - 1]->next = list2[i]; // link them
    }
    list2[i - 1]->next = NULL;

    /* NULL intersection */
    intersection = NULL;
    if (getIntersectionNode(list1[0], list2[0]) != intersection)
        printf("Error :\n");
__exit:
    /* Free memory */
    for (i = 0; i < l1; ++i)
        if (list1[i])
            free(list1[i]);
    for (i = 0; i < l2; ++i)
        if (list2[i])
            free(list2[i]);
    return 0;
}
