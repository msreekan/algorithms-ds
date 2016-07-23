/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define FORWARD_NESTED_SCAN 1

#if FORWARD_NESTED_SCAN
/***********************************************************************/
/* Given an array of non-negative integers, you are initially          */
/* positioned at the first index of the array.                         */
/* Each element in the array represents your maximum jump length at    */
/* that position.                                                      */
/* Determine if you are able to reach the last index.                  */
/*                                                                     */
/* For example:                                                        */
/* A = [2,3,1,1,4], return true.                                       */
/*                                                                     */
/* A = [3,2,1,0,4], return false.                                      */
/*                                                                     */
/***********************************************************************/
int canJump(int* nums, int numsSize)
{
    int i = 0, len = numsSize;
    int *a = nums;

    /* Loop while the array is valid, and there is a scope to move
    forward */
    while (i < len - 1 && a[i])
    {
        int leap_o = i + a[i], j = i + 1;

        /* Seek the longest possible leap within range [i, a[i] + i] */
        for(; j < len - 1 && j < (a[i] + i) && leap_o < len - 1; ++j)
            leap_o = (a[leap_o] + leap_o < (a[j] + j)) ? j : leap_o;
        i = leap_o; // Move to the new offset
    }

    /* Return depending on the offset */
    return (i < len - 1) ? 0 : 1;
}
#elif FORWARD_SCAN
/***********************************************************************/
/* Given an array of non-negative integers, you are initially          */
/* positioned at the first index of the array.                         */
/* Each element in the array represents your maximum jump length at    */
/* that position.                                                      */
/* Determine if you are able to reach the last index.                  */
/*                                                                     */
/* For example:                                                        */
/* A = [2,3,1,1,4], return true.                                       */
/*                                                                     */
/* A = [3,2,1,0,4], return false.                                      */
/*                                                                     */
/***********************************************************************/
int canJump(int* nums, int numsSize)
{
    int i, len = numsSize;
    int leap = nums[0];

    /* Loop while the array is valid, and there is a scope to move
    forward. If the present offset offers the longer leap, then pick
    the same */
    for (i = 0; i <= len - 1 && leap >= i && leap < len - 1; ++i)
        leap = (leap < (nums[i] + i)) ? nums[i] + i : leap;

    /* Return depending on the offset */
    return (leap >= len - 1) ? 1 : 0;
}
#elif BACKWARD_SCAN
/***********************************************************************/
/* Given an array of non-negative integers, you are initially          */
/* positioned at the first index of the array.                         */
/* Each element in the array represents your maximum jump length at    */
/* that position.                                                      */
/* Determine if you are able to reach the last index.                  */
/*                                                                     */
/* For example:                                                        */
/* A = [2,3,1,1,4], return true.                                       */
/*                                                                     */
/* A = [3,2,1,0,4], return false.                                      */
/*                                                                     */
/***********************************************************************/
int canJump(int* nums, int numsSize)
{
    int i = numsSize - 1, pos = i;

    /* Scan backwards while updating the target position */
    for (i = numsSize - 1; i >= 0; --i)
        pos = (nums[i] + i >= pos) ? i : pos;

    /* Return TRUE if the target is the start of the array */
    return !pos;
}
#elif RECURSIVE_SCAN
/***********************************************************************/
/* jump: Recursively jump!                                             */
/*                                                                     */
/***********************************************************************/
int jump(int* a, int n, int i, int pos)
{
    /* Update the target position */
    pos = (a[i] + i) >= pos ? i : pos;
    if (i == 0) // return
        return !pos;
    return jump(a, n, i - 1, pos);
}

/***********************************************************************/
/* Given an array of non-negative integers, you are initially          */
/* positioned at the first index of the array.                         */
/* Each element in the array represents your maximum jump length at    */
/* that position.                                                      */
/* Determine if you are able to reach the last index.                  */
/*                                                                     */
/* For example:                                                        */
/* A = [2,3,1,1,4], return true.                                       */
/*                                                                     */
/* A = [3,2,1,0,4], return false.                                      */
/*                                                                     */
/***********************************************************************/
int canJump(int* nums, int numsSize)
{
    return jump(nums, numsSize, numsSize - 1, numsSize - 1);
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6};
    int len = sizeof(a) / sizeof(int);
    printf("canJump = %d:\n", canJump(a, len));
    return 0;
}
