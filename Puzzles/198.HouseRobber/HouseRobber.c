/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* You are a professional robber planning to rob houses along a street.*/
/* Each house has a certain amount of money stashed, the only          */
/* constraint stopping you from robbing each of them is that adjacent  */
/* houses have security system connected and it will automatically     */
/* contact the police if two adjacent houses were broken into on the   */
/* same night. Given a list of non-negative integers representing the  */
/* amount of money of each house, determine the maximum amount of      */
/* money you can rob tonight without alerting the police.              */
/***********************************************************************/
int rob(int* nums, int len)
{
  int i;

  /* Handle the special case. */
  if (len > 2)
    nums[len - 3] += nums[len - 1];

  /* The sub-structure can be illustrated using four integers.
     nums = [1, 1, 8, 9]
     Two possible cases:
     1. nums[i] = nums[i] + nums[i + 2] (off by one)
     2. nums[i] = nums[i] + nums[i + 3] (off by two)
     Repeat this logic at every location while accumulating the sums.
     */
  /* Run DP. */
  for (i = len - 4; i >= 0; --i)
        nums[i] += nums[i + 2] > nums[i + 3] ? nums[i + 2] :
                   nums[i + 3];

  /* Return larger of the two sums */
  return len > 1 ? nums[0] > nums[1] ? nums [0] : nums[1] :
                   nums[0];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {2, 4, 5, 1, 1, 8};
    int len = sizeof(a) / sizeof(int);
    printf("Max Rob  = %d:\n", rob(a, len));
    return 0;
}
