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
/* Write a function to delete a node (except the tail) in a singly     */
/* linked list, given only access to that node.                        */
/* Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the  */
/* third node with value 3, the linked list should become 1 -> 2 -> 4  */
/* after calling your function.                                        */
/***********************************************************************/
void deleteNode(struct ListNode* node)
{
    struct ListNode *n;

    /* Validate. */
    if (!node)
        return;

    /* Move the values one step to the left. */
    while (node->next) {
        node->val = node->next->val;
        n = node;
        node = node->next;
    }
    /* Free the node. */
    free(node);
    n->next = NULL;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {0, 1};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *n = CreateList(a, 0, len - 1);
    PrintList(n);
    deleteNode(n);
    PrintList(n);
    FreeList(n);
    return 0;
}
