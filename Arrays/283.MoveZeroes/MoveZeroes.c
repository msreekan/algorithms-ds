/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array nums, write a function to move all 0's to the end of */
/* it while maintaining the relative order of the non-zero elements.   */
/* For example, given nums = [0, 1, 0, 3, 12], after calling your      */
/* function, nums should be [1, 3, 12, 0, 0].                          */
/* Note:                                                               */
/* You must do this in-place without making a copy of the array.       */
/* Minimize the total number of operations.                            */
/***********************************************************************/
void moveZeroes(int* nums, int nsz)
{
    int s = 0, e = 1;

    /* Validate the parameters. */
    if (!nums || nsz < 1)
        return;

    /* Seek for the first zero. */
    while (e < nsz)
    {
        /* If this is non-zero, then increment. Also, Keep end ahead of
        start. */
        if (nums[s]){
            ++s;
            e = (e < s) ? s : e;
        }

        /* Else if we have a non-zero pointer, then swap. */
        else if (nums[e]) {
                nums[s] = nums[e];
                nums[e] = 0;
        }
        /* Else we are seeking a non-zero 'end'. */
        else ++e;
    }
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 0, 2, 3, 0, 0};
    int len = sizeof(a) / sizeof(int), i;
    moveZeroes(a, len);
    for (i = 0; i < len; ++i)
        printf("%d, ", a[i]);

    return 0;
}
