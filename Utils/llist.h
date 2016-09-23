/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __LLIST_H__
#define __LLIST_H__

/*
** Linked List Node
*/
struct ListNode
{
    int val;
    struct ListNode *next;
};

/********************************************/
/* Function Prototypes                      */
/********************************************/
void PrintList(struct ListNode *head);
struct ListNode *CreateList(int *arr, int s, int e);
void FreeList(struct ListNode *head);
#endif // __BTREE_H__
