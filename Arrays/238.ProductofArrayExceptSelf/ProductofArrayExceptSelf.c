/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of n integers where n > 1, nums, return an array     */
/* output such that output[i] is equal to the product of all the       */
/* elements of nums except nums[i].                                    */
/* Solve it without division and in O(n).                              */
/* For example, given [1,2,3,4], return [24,12,8,6].                   */
/* Follow up:                                                          */
/* Could you solve it with constant space complexity? (Note: The output*/
/* array does not count as extra space for the purpose of space        */
/* complexity analysis.)                                               */
/***********************************************************************/
int *productExceptSelf(int* nums, int numsSize, int* returnSize)
{
    int *arr;
    int i, p = 1;

    /* Verify the parameters. */
    if (!nums || numsSize <= 0 || !returnSize)
        return NULL;

    /* Allocate the product array. */
    arr = malloc(numsSize * sizeof(int));
    if (!arr)
        return NULL;

    /* Generate the product in reverse. */
    for (i = numsSize - 1; i >=0; --i)
        p = arr[i] = nums[i] * p;

    /* Now generate the array. */
    arr[0] = arr[1];
    for (p = 1, i = 1; i < numsSize - 1; ++i)
    {
        nums[i] *= nums[i - 1];
        arr[i] = arr[i + 1] * nums[i - 1];
    }
    arr[i] = nums[i - 1];

    /* Return the array. */
    *returnSize = numsSize;
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4};
    int len = sizeof(a) / sizeof(int), ret, i;
    int *arr;

    /* Get the result. */
    arr = productExceptSelf(a, len, &ret);
    for (i = 0; i < ret; ++i)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
