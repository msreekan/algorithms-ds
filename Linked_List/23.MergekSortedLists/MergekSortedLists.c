/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_LSZ 32
#define LIST_SZ 6

/********************************/
/* Linked list NODE             */
/********************************/
struct ListNode
{
   int val;
   struct ListNode *next;
};

/***********************************************************************/
/* free_list: Free the list                                            */
/*                                                                     */
/***********************************************************************/
void free_list(struct ListNode *l)
{
    struct ListNode *n = l, *nn;
    while(n)
    {
        nn = n->next;
        free(n);
        n = nn;
    }
}

/***********************************************************************/
/* generate_list: Generate the list                                    */
/*                                                                     */
/***********************************************************************/
struct ListNode *generate_list(int *a, int len)
{
    int i;
    struct ListNode *start, *n;

    /* Allocate the head */
    start = malloc(sizeof(struct ListNode));
    if (!start)
        return NULL;
    start->val = a[0];
    start->next = NULL;
    n = start;

    /* Generate the list */
    for (i = 1; i < len; ++i)
    {
        n->next = malloc(sizeof(struct ListNode));
        if (!n->next)
            free_list(start);
        n = n->next;
        n->val = a[i];
    }

    /* NULL terminate and return */
    n->next = NULL;
    return start;
}

/***********************************************************************/
/* prn_list: Print the list                                            */
/*                                                                     */
/***********************************************************************/
void prn_list(struct ListNode *l1)
{
    struct ListNode *sl = l1;
    while(sl)
    {
        printf("%d-> ", sl->val);
        sl = sl->next;
    }
    printf("NULL \n");
}

/***********************************************************************/
/* swap_ptr: Swap pointers                                             */
/*                                                                     */
/***********************************************************************/
void swap_ptr(struct ListNode **l1, struct ListNode **l2)
{
    struct ListNode *t = *l1;
    *l1 = *l2;
    *l2 = t;
}

/***********************************************************************/
/* sift_down: Sift down the value through the heap                     */
/*                                                                     */
/***********************************************************************/
void sift_down(struct ListNode **lists, int s, int listsSize)
{
    int len = listsSize;
    int i = s;
    struct ListNode **l = lists;

    /* Sanity */
    if (len < 2)
        return;

    /* Index till the last non-leaf node */
    while (i <= ((len - 2) / 2))
    {
        int c2 = (i * 2) + 2;
        int c1 = (i * 2) + 1;
        int c = c1;

        /* Select the smallest child */
        if ((c2 < len) && ((l[c2]->val) < l[c1]->val))
            c = c2;

        /* Swap */
        if (l[i]->val > l[c]->val)
            swap_ptr(&l[i], &l[c]);

        /* If there was no swap, then we are done. */
        else
            break;

        /* Move the index to the swapped out child */
        i = c;
    }
}

/***********************************************************************/
/* heapify: Heapify!                                                   */
/*                                                                     */
/***********************************************************************/
void heapify(struct ListNode **lists, int listsSize,
             struct ListNode *maxn)
{
    int len = listsSize, i;
    struct ListNode **l = lists;

    /* Maintain sanity */
    if (len < 2)
    {
        l[len - 1] = (l[len - 1] == NULL) ? maxn : l[len - 1];
        return;
    }


    /* Select the index of the last non-leaf node */
    i = (len - 2) / 2;

    /* Loop to compare and swap parents node values with the children */
    while (i >= 0)
    {
        int c2 = (i * 2) + 2;
        int c = (i * 2) + 1;

        /* Ensure the NULL entries are set to dummy */
        l[c] = (l[c] == NULL) ? maxn : l[c];
        l[i] = (l[i] == NULL) ? maxn : l[i];

        /* Select the smallest child */
        if (c2 < len)
        {
            /* Ensure the child is valid */
            l[c2] = (l[c2] == NULL) ? maxn : l[c2];
            if (l[c2]->val < l[c]->val)
                c = c2;
        }

        /* If needed, sift down the values down the heap */
        if (l[i]->val > l[c]->val)
            sift_down(l, i, len);

        /* Move to the next parent */
        --i;
    }
}

/***********************************************************************/
/* Merge k sorted linked lists and return it as one sorted list.       */
/* Analyze and describe its complexity.                                */
/*                                                                     */
/***********************************************************************/
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    int len = listsSize;
    struct ListNode *sml = NULL, *ml = NULL;
    struct ListNode max = { 0x7FFFFFFF, NULL};

    /* We cannot accept NULL parameter */
    if (!listsSize)
        return NULL;

    /* First heapify the list */
    heapify(lists, len, &max);

    /* Allow the smallest value to rise up through the heap */
    while(lists[0] != &max)
    {
        /* Initialize the merge list head */
        if (!ml)
        {
            sml = lists[0];
            ml = sml;
        }

        /* Else move to the next node */
        else
        {
            ml->next = lists[0];
            ml = ml->next;
        }

        /* Move the list to the next node */
        lists[0] = lists[0]->next;

        /* If the node is NULL then set the end marker */
        if (lists[0] == NULL)
            lists[0] = &max;

        /* Sift down the new root, allow the smalled element to rise up
        through the heap */
        sift_down(lists, 0, len);
    }

    /* NULL terminate and return */
    if(ml)
      ml->next = NULL;
    return sml;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    struct ListNode *l[LIST_SZ] = {NULL};;
    int i;
    struct ListNode *ml;
    int lsz[LIST_SZ] = {3, 4, 7,8,1,3};
    int lvals[LIST_SZ][MAX_LSZ] = {{-9,-7,-7},{-6,-4,-1,1},{-6,-5,-2,0,0,1,2},{-9,-8,-6,-5,-4,1,2,4},{-10},{-5,2,3}};

    /* Generate a list */
    for (i = 0; i < LIST_SZ; ++i)
    {
        printf("L %d \n", lsz[i]);
        l[i] = generate_list(lvals[i], lsz[i]);
        prn_list(l[i]);
    }

    /* Merge the list */
    ml = mergeKLists(&l[0], LIST_SZ);
    printf("Merged List :\n");

    /* Print, free and return */
    prn_list(ml);
    free_list(ml);
    return 0;
}
