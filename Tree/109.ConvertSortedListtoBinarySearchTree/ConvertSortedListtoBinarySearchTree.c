/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/llist.h"
#include "../Utils/btree.h"

/***********************************************************************/
/* GetListMid: Get the middle node of a list!                          */
/*                                                                     */
/***********************************************************************/
struct ListNode *GetListMid(struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *node = head, *mid = head;

    /* List with one node has no center */
    if (head == tail)
        return NULL;

    /* Loop till the tail */
    while (node != tail)
    {
        /* Move node twice */
        node = node->next;
        /* If it's not the tail, increment node and middle tracker. */
        if (node != tail)
        {
            node = node->next;
            mid = mid->next;
        }
    }

    /* Return the center */
    return mid;
}

/***********************************************************************/
/* ListToBST: Recursively generate BST from a sorted list!             */
/*                                                                     */
/***********************************************************************/
struct TreeNode *ListToBST(struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *mid;
    struct TreeNode *root;

    /* Get the middle node */
    if (((mid = GetListMid(head, tail)) == NULL) ||
        ((root = malloc(sizeof(struct TreeNode))) == NULL))
        return NULL;

    /* Assign the middle value */
    root->val = mid->val;
    root->left = ListToBST(head, mid);
    root->right = ListToBST(mid->next, tail);
    return root;
};

/***********************************************************************/
/* Given a singly linked list where elements are sorted in ascending   */
/* order, convert it to a height balanced BST.                         */
/***********************************************************************/
struct TreeNode* sortedListToBST(struct ListNode* head)
{
    return ListToBST(head, NULL);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {1, 3, 4, 5, 6, 7, 8, 10, 11};
    int len = sizeof(arr) / sizeof(int);
    struct ListNode *start;
    struct TreeNode *root;

    /* Create list */
    start = CreateList(arr, 0, len - 1);
    PrintList(start);
    printf("\n");

    root = sortedListToBST(start);
    InorderBtree(root);
    printf("\n");

    FreeBtree(root);
    FreeList(start);
    return 0;
}
