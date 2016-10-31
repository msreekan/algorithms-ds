/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/******************************************/
/* Macros                                 */
/******************************************/
#define MAX_NODES    16

/******************************************/
/* Data Structure                         */
/******************************************/
 struct ListNode
 {
    int val;
    struct ListNode *next;
 };

/***********************************************************************/
/* Given a linked list, return the node where the cycle begins. If     */
/* there is no cycle, return null.                                     */
/*                                                                     */
/* Note: Do not modify the linked list.                                */
/*                                                                     */
/* Follow up:                                                          */
/* Can you solve it without using extra space?                         */
/***********************************************************************/
struct ListNode *detectCycle(struct ListNode *head)
{
    struct ListNode *slow = head, *fast = (head) ? head->next : NULL;
    int size = 0, i;

    /* Loop seeking the loop!! */
    while (fast)
    {
        /* If slow and fast pointers are same, then we have a loop */
        if (slow == fast)
            break;
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    }

    /* If there is a loop, then figure out the length */
    if (slow == fast) {
        slow = slow->next;
        while (slow != fast) { // figure out the length of the loop
            size++;
            slow = slow->next;
        }

        /* Reset the pointers */
        slow = head;
        fast = head;
        for (i = 0; i < size; ++i) // move the pointer ahead by the loop size
            fast = fast->next;
        while (slow != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* Return the pivot */
    return fast;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *list[MAX_NODES] = {NULL};
    struct ListNode *cyclenode;
    int i, node1, node2;

    /* Allocate the list */
    for (i = 0; i < MAX_NODES; ++i) {
        if (!(list[i] = malloc(sizeof(struct ListNode))))
            goto __exit;
        list[i]->val = i;
        if (i) list[i - 1]->next = list[i];
    }
    list[i - 1]->next = NULL;
    node1 = rand() % MAX_NODES;
    node2 = rand() % node1;
    list[node1]->next = list[node2]; // loop
    printf("Cycle from %d to %d \n", node1, node2);

    if (!(cyclenode = detectCycle(list[0])))
        printf("ERROR:\n");
    else if (cyclenode != list[node1])
        printf("Wrong Node!!\n");
__exit:
    for (i = 0; i < MAX_NODES; ++i)
        if (list[i]) free(list[i]);
    return 0;
}
