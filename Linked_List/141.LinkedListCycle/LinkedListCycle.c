/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**************************************/
/* Macros                             */
/**************************************/
#define MAX_NODES 10

/******************************************/
/* Data Structure                         */
/******************************************/
 struct ListNode
 {
    int val;
    struct ListNode *next;
 };

/***********************************************************************/
/* Given a linked list, determine if it has a cycle in it.             */
/*                                                                     */
/* Follow up:                                                          */
/* Can you solve it without using extra space?                         */
/***********************************************************************/
bool hasCycle(struct ListNode *head)
{
    struct ListNode *slow = head, *fast = (head) ? head->next : NULL;

    /* Loop seeking the loop!! */
    while (fast)
    {
        /* If the pointers match, then there is a loop */
        if (slow == fast)
            return true;

        /* Slow pointer advance by one, fast by two */
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    }
    return false;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *list[MAX_NODES] = {NULL};
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

    if (!hasCycle(list[0]))
        printf("ERROR:\n");
__exit:
    for (i = 0; i < MAX_NODES; ++i)
        if (list[i]) free(list[i]);
    return 0;
}
