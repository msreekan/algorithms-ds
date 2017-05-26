/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an integer array of size n, find all elements that appear     */
/* more than ⌊ n/3 ⌋ times. The algorithm should run in linear time    */
/* and in O(1) space.                                                  */
/***********************************************************************/
int* majorityElement(int* nums, int numsSize, int* returnSize)
{
    int *arr;
    int count[2] = {0}, val[2];
    int i;

    /* Validate the parameters. */
    if (!nums || numsSize <= 0 || !returnSize)
        return NULL;
    *returnSize = 0;

    /* Loop through the array looking for instances. */
    for (i = 0; i < numsSize; ++i)
    {
        /* If the value matches either of the candisates, then
        increment count. */
        if (nums[i] == val[0] || nums[i] == val[1])
        {
            count[0] = nums[i] == val[0] ? count[0] + 1 : count[0];
            count[1] = nums[i] == val[1] ? count[1] + 1 : count[1];
        }
        /* If either of the counts have expired, then replace the
        corresponding candidate. */
        else if (!count[0] || !count[1])
        {
            if (!count[0]) {
                val[0] = nums[i];
                count[0]++;
            }
            else {
                val[1] = nums[i];
                count[1]++;
            }
        }
        /* Else simply decrement, both the counts. */
        else
        {
            count[0]--;
            count[1]--;
        }
    }

    /* Count the number of instances for these candidates. */
    count[0] = count[1] = 0;
    for (i = 0; i < numsSize; ++i)
    {
        count[0] = (nums[i] == val[0]) ? count[0] + 1 : count[0];
        count[1] = (nums[i] == val[1]) ? count[1] + 1 : count[1];
    }

    /* Allocate memory. */
    if (!(arr = malloc(sizeof(int) * 2)))
        return NULL;

    /* Confirm the number of candidates. */
    if (count[0] > numsSize / 3)
        arr[(*returnSize)++] = val[0];
    if (count[1] > numsSize / 3)
        arr[(*returnSize)++] = val[1];

    /* Return the array. */
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 1
    int a[] = {2, 3, 4, 4, 5, 6, 6, 6, 6};
    #elif 0
    int a[] = {11,11,11,11,23,33,33,33,33,22,22};
    #elif 1
    int a[] = {11,22};
    #endif
    int len = sizeof(a) / sizeof(int), ret;
    int *arr;

    arr = majorityElement(a, len, &ret);
    if (ret > 0)
        printf("%d : \n", arr[0]);
    if (ret > 1)
        printf("%d : \n", arr[1]);
    return 0;
}
