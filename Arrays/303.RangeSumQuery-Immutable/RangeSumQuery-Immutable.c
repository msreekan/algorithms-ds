/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an integer array nums, find the sum of the elements between   */
/* indices i and j (i ≤ j), inclusive.                                 */
/* Example:                                                            */
/* Given nums = [-2, 0, 3, -5, 2, -1]                                  */
/*                                                                     */
/* sumRange(0, 2) -> 1                                                 */
/* sumRange(2, 5) -> -1                                                */
/* sumRange(0, 5) -> -3                                                */
/*                                                                     */
/* Note:                                                               */
/* You may assume that the array does not change.                      */
/* There are many calls to sumRange function.                          */
/***********************************************************************/
typedef struct
{
    int *arr;
    int len;
} NumArray;

/***********************************************************************/
/* numArrayCreate: Create the array!                                   */
/*                                                                     */
/***********************************************************************/
NumArray* numArrayCreate(int* nums, int numsSize)
{
    NumArray *n;
    int i;

    /* Allocate space. */
    if (!(n = malloc(sizeof(NumArray) + (sizeof(int) * numsSize))))
        return NULL;
    n->arr = (int *)&n[1];

    /* Generate the range sum array. */
    n->arr[0] = nums[0];
    for (i = 1; i < numsSize; ++i)
        n->arr[i] = n->arr[i - 1] + nums[i];
    n->len = numsSize;

    /* Return the handle. */
    return n;
}

/***********************************************************************/
/* numArraySumRange: Return the sum range.                             */
/*                                                                     */
/***********************************************************************/
int numArraySumRange(NumArray* obj, int i, int j)
{
    int sum = obj->arr[j];

    /* Subtract the sum of the values less than 'i' when it's valid. */
    if (i > 0)
        sum -= obj->arr[i - 1];
    return sum;
}

/***********************************************************************/
/* numArrayFree: Free the array.                                       */
/*                                                                     */
/***********************************************************************/
void numArrayFree(NumArray* obj)
{
    free(obj);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
