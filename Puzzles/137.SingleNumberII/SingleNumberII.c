/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of integers, every element appears three times except*/
/* for one. Find that single one.                                      */
/* Note:                                                               */
/* Your algorithm should have a linear runtime complexity. Could you   */
/* implement it without using extra memory?                            */
/***********************************************************************/
int singleNumber(int* nums, int numsSize)
{
    int sum[sizeof(int) * 8] = {0};
    int i, mask = 1, j, value = 0;

    /* Loop figuring out the bit count for each value */
    for (i = 0; i < numsSize; ++i)
    {
        mask = 1; // start with first bit
        /* Loop seeking the bit count */
        for (j = 0; j < sizeof(int) * 8; ++j, mask++)
           if ((1 << mask) & nums[i]) // if bit is set, increment the count
                sum[j] += 1;
    }

    /* Find bits which are not in a multiple of 3 */
    for (j = 0; j < sizeof(int) * 8; ++j)
        if (sum[j] % 3)
            value |= (1 << j);
    return value;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {-401451,-177656,-2147483646,-473874,-814645,-2147483646,-852036,-457533,-401451,-473874,-401451,-216555,-917279,-457533,-852036,-457533,-177656,-2147483646,-177656,-917279,-473874,-852036,-917279,-216555,-814645,2147483645,-2147483648,2147483645,-814645,2147483645,-216555};
    int len = sizeof(a) / sizeof(int);
    printf("Value not occurring thrice = %d:\n", singleNumber(a, len));
    return 0;
}
