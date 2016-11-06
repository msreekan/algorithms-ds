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
/* MergeSortList: Merge sort a linked list!                            */
/*                                                                     */
/***********************************************************************/
struct ListNode *MergeSortList(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *mh = NULL, *ml = NULL;
    struct ListNode *fast, *slow, *pslow;

    /* Find the center of the list */
    pslow = slow = fast = l1;
    while (fast) {
        fast = fast->next;
        if (fast) {
            pslow = slow;
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* Merge Sort the first partition */
    if (slow != l1) {
        pslow->next = NULL;
        l1 = MergeSortList(l1, slow);
    }

    /* Find the center of the list */
    pslow = slow = fast = l2;
    while (fast) {
        fast = fast->next;
        if (fast) {
            pslow = slow;
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* Merge Sort the first partition */
    if (slow != l2) {
        pslow->next = NULL;
        l2 = MergeSortList(l2, slow);
    }

    /* Assign the head of the new list */
    if (l1 && l1->val < l2->val) {
        ml = mh = l1;
        l1 = l1->next;
    }
    else {
        ml = mh = l2;
        l2 = l2->next;
    }

    /* Merge the contents */
    while (l1 && l2) {
        if (l1->val < l2->val){
            ml->next = l1;
            l1 = l1->next;
        }
        else{
            ml->next = l2;
            l2 = l2->next;
        }
        ml = ml->next;
    }

    /* Simply append the rest */
    if (l1)
        ml->next = l1;
    else
        ml->next = l2;
    return mh;
}


/***********************************************************************/
/* Sort a linked list in O(n log n) time using constant space          */
/* complexity.                                                         */
/***********************************************************************/
struct ListNode *sortList(struct ListNode* head)
{
    struct ListNode *fast = head, *slow = head, *pslow = slow;

    /* Find the center of the list */
    while (fast) {
        fast = fast->next;
        if (fast) {
            pslow = slow;
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* Avoid merge sort */
    if (slow == fast)
        return head;

    /* Merge sort */
    pslow->next = NULL;
    return MergeSortList(head, slow);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //         0  1  2  3  4  5  6  7  8  9  10 11 12
    int a[] = {5, 3, 4, 5, 2, 2, 1, 5, 7, 8, 1, 2, 3};
    int len = sizeof(a) / sizeof(int);
    struct ListNode *root;
    root = CreateList(a, 0, len - 1);
    PrintList(root);
    printf("\n");
    root = sortList(root);
    PrintList(root);
    printf("\n");
    FreeList(root);
    return 0;
}
