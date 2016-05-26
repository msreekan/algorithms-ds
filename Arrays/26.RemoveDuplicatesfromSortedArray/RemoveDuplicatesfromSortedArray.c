/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a sorted array, remove the duplicates in place such that each */
/* element appear only once and return the new length.                 */
/*                                                                     */
/* Do not allocate extra space for another array, you must do this in  */
/* place with constant memory.                                         */
/*                                                                     */
/* For example, Given input array nums = [1,1,2],                      */
/* Your function should return length = 2, with the first two elements */
/* of nums being 1 and 2 respectively. It doesn't matter what you      */
/* leave beyond the new length.                                        */
/*                                                                     */
/***********************************************************************/
int removeDuplicates(int* nums, int numsSize)
{
    int len = numsSize;
    int poff = 0, noff = 0;

    /* Sanity Check */
    if (!len)
        return 0;

    /* Loop till the end of the list */
    while (nums[noff] != nums[len - 1])
    {
        /* Seek to the next unique element */
        while(nums[noff] == nums[poff])
            noff++;

        /* Increment the write index and save the
        next unique value */
        poff++;
        nums[poff] = nums[noff];
    }

    /* Return the new size */
    return poff + 1;
}

/***********************************************************************/
/* prn_array: Print array                                              */
/*                                                                     */
/***********************************************************************/
void prn_array(int *a, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 1, 2, 2, 3, 3, 3, 5, 5, 5, 6, 6, 6, 6, 7, 7, 8};
    int len = sizeof(a) / sizeof(int), nlen = 0;

    prn_array(a, len);
    nlen = removeDuplicates(a, len);
    prn_array(a, nlen);
    return 0;
}

