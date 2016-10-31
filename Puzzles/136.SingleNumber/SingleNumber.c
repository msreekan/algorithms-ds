/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an array of integers, every element appears twice except for  */
/* one. Find that single one.                                          */
/*                                                                     */
/* Note:                                                               */
/* Your algorithm should have a linear runtime complexity. Could you   */
/* implement it without using extra memory?                            */
/***********************************************************************/
int singleNumber(int* nums, int numsSize)
{
    int i, num = 0;
    /* Loop while XORing values */
    for (i = 0; i < numsSize; ++i)
        num ^= nums[i];
    return num;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1,1,2,2,3};
    int len = sizeof(a) / sizeof(int);
    printf("Lone single instance of %d", singleNumber(a, len));
    return 0;
}
