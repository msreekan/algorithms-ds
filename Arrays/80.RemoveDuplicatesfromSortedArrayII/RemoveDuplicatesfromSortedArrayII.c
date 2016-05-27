/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* What if duplicates are allowed at most twice?                       */
/* For example,                                                        */
/* Given sorted array nums = [1,1,1,2,2,3],                            */
/*                                                                     */
/* Your function should return length = 5, with the first five elements*/
/* of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave    */
/* beyond the new length.                                              */
/***********************************************************************/
int removeDuplicates(int* nums, int numsSize)
{
    int len = numsSize;
    int i = len - 1, j, l;
    int *a = nums;

    /* We need to run only up to index 2. Also, scanning backwards from
    the end of the array would ensure that the copies happen after the
    redundant ( > 2 ) elements are removed. Still O(n), but reduces the
    memcopy. */
    while (i - 2 >= 0)
    {
        /* If there are more than 3 instances of a value then shift
        the array to the left removing the redundant elements */
        if ((nums[i] == nums[i - 1]) && (nums[i - 2] == nums[i - 1]))
        {
            /* Find the index with the first non-repeating element */
            j = i - 1;
            while ((j >= 0) && (a[j] == a[i]))
                j--;

            /* Elements from (i - 1) to len needs to be moved to j */
            l = i - 1;
            ++j;

            /* First, update the outer loop scan offset */
            i = j;

            /* Copy */
            while (l < len)
            {
                a[j] = a[l];
                ++j;
                ++l;
            }

            /* Update the length */
            len = j;
        }

        /* Decrement the index */
        --i;
    }

    /* Return */
    return len;
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
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{           // 0  1  2  3  4  5  6  7  8  9  10 11  12
    int a[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3,  4};
    int len = sizeof(a) / sizeof(int);
    prn_array(a, len);
    len = removeDuplicates(a, len);
    prn_array(a, len);
    return 0;
}

