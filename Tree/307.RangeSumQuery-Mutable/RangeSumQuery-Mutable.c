/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************/
/* Macros                    */
/*****************************/
#define ARRAY_IMPLEMENTATION   1
#define CALC_MID(s, e) ((s) + ((e) - (s) + 1) / 2)

/***********************************************************************/
/* Given an integer array nums, find the sum of the elements between   */
/* indices i and j (i ≤ j), inclusive.                                 */
/* he update(i, val) function modifies nums by updating the element at */
/* index i to val.                                                     */
/* Example:                                                            */
/* Given nums = [1, 3, 5]                                              */
/*                                                                     */
/* sumRange(0, 2) -> 9                                                 */
/* update(1, 2)                                                        */
/* sumRange(0, 2) -> 8                                                 */
/*                                                                     */
/* Note:                                                               */
/* The array is only modifiable by the update function.                */
/* You may assume the number of calls to update and sumRange function  */
/* is distributed evenly.                                              */
/***********************************************************************/
#if ARRAY_IMPLEMENTATION
typedef struct
{
    int *arr; /* Segment tree. */
    int len;  /* Number of leaf nodes. */
} NumArray;

/***********************************************************************/
/* CreateSegTree: Create the segment tree with range sums!             */
/*                                                                     */
/***********************************************************************/
int CreateSegTree(NumArray *n, int soff, int *arr, int s, int e)
{
    int mid = CALC_MID(s, e);

    /* If this is a leaf node, then simply assign the value and
       return. */
    if (s == e)
        n->arr[soff] = arr[s];

    /* Recursively generate and save the sums. */
    else
        n->arr[soff] = CreateSegTree(n, soff * 2 + 1, arr, s, mid - 1) +
                       CreateSegTree(n, soff * 2 + 2, arr, mid, e);
    return n->arr[soff];
}

/***********************************************************************/
/* SearchSegTree: Search the segment tree for range sums!              */
/*                                                                     */
/***********************************************************************/
int SearchSegTree(NumArray *n, int soff, int s, int e, int ss, int se)
{
    int mid = CALC_MID(s, e);

    /* Adjust pointers according to the range we need to search.*/
    while ((ss >= mid || se < mid) &&
           (s != ss || e != se))
    {
        soff = soff * 2 + 1;
        /* Search the seconf half. */
        if (ss >= mid) {
            s = mid;
            soff++;
        }
        /* Else it's the first half. */
        else
            e = mid - 1;
        mid = CALC_MID(s, e);
    }

    /* If we have a hit, then return. */
    if (s == ss && e == se)
        return n->arr[soff];
    /* Else we straddle both the halves. */
    return SearchSegTree(n, soff * 2 + 1, s, mid - 1, ss, mid - 1) +
           SearchSegTree(n, soff * 2 + 2, mid, e, mid, se);
}

/***********************************************************************/
/* InitSegTree: Init the segment tree!                                 */
/*                                                                     */
/***********************************************************************/
NumArray *InitSegTree(int* nums, int len)
{
    int val = 1;
    NumArray *n;

    /* Verify the inputs. */
    if (!nums || len < 1)
        return NULL;

    /* Calculate the nearest power of two for the length. */
    while (val < len)
        val <<= 1;
    /* Calcualate the total length of the array. */
    val = (val * 2) - 1;

    /* Allocate space.*/
    if (!(n = malloc((sizeof(int) * val) + sizeof(NumArray))))
        return NULL;
    n->len = len;
    n->arr = (int *)&n[1];

    /* Initialize values and return. */
    CreateSegTree(n, 0, nums, 0, len - 1);
    return n;
}

/***********************************************************************/
/* numArraySumRange: Sum the range!                                    */
/*                                                                     */
/***********************************************************************/
int numArraySumRange(NumArray* obj, int i, int j)
{
    /* Validate the parameters. */
    if (i > j)
        return -1;
    return SearchSegTree(obj, 0, 0, obj->len - 1, i, j);
}

/***********************************************************************/
/* numArrayUpdate: Update the array!                                   */
/*                                                                     */
/***********************************************************************/
void numArrayUpdate(NumArray* n, int loc, int val)
{
    int mid, diff, soff = 0, s = 0, e = n->len - 1;

    /* Loop till we reach the leaf node. */
    while (s != loc || e != loc)
    {
        /* Get the middle .*/
        mid = CALC_MID(s, e);
        soff = soff * 2 + 1;

        /* Select the half to be searched. */
        if (loc < mid)
            e = mid - 1;
        else {
            s = mid;
            soff++;
        }
    }

    /* Calculate the difference. */
    diff = val - n->arr[soff];

    /* Update all the parents. */
    while (soff > 0) {
        n->arr[soff] += diff;
        soff = (soff - 1) / 2;
    }
    n->arr[soff] += diff;
}

/***********************************************************************/
/* numArrayFree: Free the array!                                       */
/*                                                                     */
/***********************************************************************/
void numArrayFree(NumArray* obj)
{
    if (!obj) return;
    free(obj);
}
#else
/***********************************************/
/* Data Structures                             */
/***********************************************/
struct node
{
    int val;
    struct node *left;
    struct node *right;
};

typedef struct
{
    struct node *root; /* Segment tree. */
    int len;           /* Number of leaf nodes. */
} NumArray;

/***********************************************************************/
/* CreateSegTree: Create the segment tree with range sums!             */
/*                                                                     */
/***********************************************************************/
struct node *CreateSegTree(int *arr, int s, int e)
{
    struct node *n;
    int mid = CALC_MID(s, e);

    /* Allocate the node. */
    if (!(n = malloc(sizeof(struct node))))
        return NULL;

    /* If this is a leaf node, then assign and return. */
    if (s == e)
    {
        n->left = n->right = NULL;
        n->val = arr[s];
        return n;
    }

    /* Else generate the tree recursively, and return. */
    n->left = CreateSegTree(arr, s, mid - 1);
    n->right = CreateSegTree(arr, mid, e);
    n->val = n->left->val + n->right->val;
    return n;
}

/***********************************************************************/
/* InitSegTree: Init the segment tree!                                 */
/*                                                                     */
/***********************************************************************/
NumArray *InitSegTree(int* nums, int len)
{
    NumArray *n = NULL;

    /* Allocate the handle. */
    if (!(n = malloc(sizeof(NumArray))))
        goto __InitExit;

    /* Initialize the tree and return. */
    if (!(n->root = CreateSegTree(nums, 0, len - 1)))
        goto __InitExit;
    n->len = len;
    return n;

    /* Error. */
__InitExit:
    if (n)
        free(n);
    return NULL;
}

/***********************************************************************/
/* SearchSegTree: Search the segment tree for range sums!              */
/*                                                                     */
/***********************************************************************/
int SearchSegTree(struct node *n, int s, int e, int ss, int se)
{
    int mid = CALC_MID(s, e);

    /* If we have narrowed the range, then return. */
    if (s == ss && e == se)
        return n->val;

    /* If the range is in the first half, then search that sub-tree. */
    if (se < mid)
        return SearchSegTree(n->left, s, mid - 1, ss, se);
    /* Else search the right sub-tree. */
    else if (ss >= mid)
        return SearchSegTree(n->right, mid, e, ss, se);
    /* Else we straddle both the halves. */
    else
        return SearchSegTree(n->right, mid, e, mid, se) +
               SearchSegTree(n->left, s, mid - 1, ss, mid - 1);
}

/***********************************************************************/
/* UpdateSegTree: Update the segment tree!                             */
/*                                                                     */
/***********************************************************************/
int UpdateSegTree(struct node *n, int s, int e, int loc, int val)
{
    int diff, mid = CALC_MID(s, e);

    /* If we have a hit, then change the value and return difference.*/
    if (s == loc && e == loc)
        diff = val - n->val;
    /* Else search the left sub-tree. */
    else if (loc < mid)
        diff = UpdateSegTree(n->left, s, mid - 1, loc, val);
    /* Else in the right sub-tree. */
    else
        diff = UpdateSegTree(n->right, mid, e, loc, val);
    n->val += diff;
    return diff;
}

/***********************************************************************/
/* FreeSegTree: Free the segment tree!                                 */
/*                                                                     */
/***********************************************************************/
void FreeSegTree(struct node *n)
{
    /* If the node is NULL, then return. */
    if (!n) return;

    /* Recursively free the nodes. */
    FreeSegTree(n->left);
    FreeSegTree(n->right);
    free(n);
}

/***********************************************************************/
/* numArraySumRange: Sum the range!                                    */
/*                                                                     */
/***********************************************************************/
int numArraySumRange(NumArray* obj, int i, int j)
{
    /* Validate the parameters. */
    if (i > j)
        return -1;
    return SearchSegTree(obj->root, 0, obj->len - 1, i, j);
}

/***********************************************************************/
/* numArrayUpdate: Update the array!                                   */
/*                                                                     */
/***********************************************************************/
void numArrayUpdate(NumArray* obj, int loc, int val)
{
    UpdateSegTree(obj->root, 0, obj->len - 1, loc, val);
}

/***********************************************************************/
/* numArrayFree: Free the array!                                       */
/*                                                                     */
/***********************************************************************/
void numArrayFree(NumArray* obj)
{
    if (!obj) return;
    FreeSegTree(obj->root);
    free(obj);
}
#endif /* ARRAY_IMPLMENTATION */
/***********************************************************************/
/* numArrayCreate: Create the array!                                   */
/*                                                                     */
/***********************************************************************/
NumArray *numArrayCreate(int* nums, int len)
{
    /* Validate the parameters. */
    if (!nums || len < 1)
        return NULL;
    return InitSegTree(nums, len);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
#if 1
    int a[] = {1, 3, 5};
#elif 1
    int a[] = {-1};
#endif
    int len = sizeof(a) / sizeof(int);
    NumArray *t;

    if (!(t = numArrayCreate(a, len)))
        return -1;
#if 1
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 2));
    numArrayUpdate(t, 1, 2);
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 2));
    printf("SumRange = %d: \n", numArraySumRange(t, 1, 2));
    printf("SumRange = %d: \n", numArraySumRange(t, 2, 2));
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 0));
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 1));
#elif 1
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 0));
    numArrayUpdate(t, 0, 1);
    printf("SumRange = %d: \n", numArraySumRange(t, 0, 0));
#endif
    numArrayFree(t);
    return 0;
}
