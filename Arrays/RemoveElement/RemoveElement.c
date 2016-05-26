/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array and a value, remove all instances of that value in   */
/* place and return the new length. Do not allocate extra space for    */
/* another array, you must do this in place with constant memory.      */
/*                                                                     */
/* The order of elements can be changed. It doesn't matter what you    */
/* leave beyond the new length.                                        */
/*                                                                     */
/* Example:                                                            */
/* Given input array nums = [3,2,2,3], val = 3                         */
/* Your function should return length = 2, with the first two elements */
/* of nums being 2.                                                    */
/*                                                                     */
/***********************************************************************/
int removeElement(int* nums, int numsSize, int val)
{
    int s = 0, e = numsSize - 1, len = numsSize;

    /* Scan the array from both the ends seeking and replacing
       target values. Eventually all the values to be replaced will be
       at the end of the list */
    while (s <= e)
    {
        /* Find the first instance of the target value from the
           start */
        while ((s < len) && (nums[s] != val))
            ++s;

        /* Find the first instance of an element not equal to the
           target */
        while((s <= e) && (e >= 0) && (nums[e] == val))
            --e;

        /* Swap out the target value */
        if (s < e)
        {
            int t = nums[s];
            nums[s] = nums[e];
            nums[e] = t;
        }
    }

    /* Return new size */
    return s;
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
    int a[] = {1, 1, 2, 2, 3, 3, 4, 4, 3, 3, 4, 5};
    int len = sizeof(a) / sizeof(int);
    int nlen;
    prn_array(a, len);
    nlen = removeElement(a, len, 2);
    prn_array(a, nlen);
    return 0;
}

