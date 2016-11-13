/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of integers that is already sorted in ascending      */
/* order, find two numbers such that they add up to a specific target  */
/* number.                                                             */
/* The function twoSum should return indices of the two numbers such   */
/* that they add up to the target, where index1 must be less than      */
/* index2. Please note that your returned answers (both index1 and     */
/* index2) are not zero-based.                                         */
/* You may assume that each input would have exactly one solution.     */
/* Input: numbers={2, 7, 11, 15}, target=9                             */
/* Output: index1=1, index2=2                                          */
/*                                                                     */
/***********************************************************************/
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int *rarr = NULL;
    int start = 0, end = numbersSize - 1, psum;

    /* Scan from both the ends attempting to narrow down the correct
    pair. */
    while (start < end) {
        psum = numbers[start] + numbers[end]; // get the present sum

        /* If we have a hit, then break */
        if (psum == target)
            break;
        /* If present sum greater than target, then reduce it */
        else if (psum > target)
            end--;
        /* Else increase it */
        else
            start++;
    }

    /* If we have a hit, then allocate and return the array */
    if (psum == target) {
        rarr = malloc(sizeof(int) * 2);
        if (rarr) {
            rarr[0] = start + 1;
            rarr[1] = end + 1;
            *returnSize = 2;
        }
    }

    /* Return the array */
    return rarr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1,2,3,5,6,7,9};
    int len = sizeof(a) / sizeof(int);
    int target = 9, ret;
    int *arr = twoSum(a, len, target, &ret);
    if (!arr) printf("Pair NOT found!! \n");
    else {
        printf("Pairs [%d, %d] = %d", arr[0], arr[1], target);
        free(arr);
    }
    return 0;
}
