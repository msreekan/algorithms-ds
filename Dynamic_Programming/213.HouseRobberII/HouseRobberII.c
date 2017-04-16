/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************/
/* Macros                           */
/************************************/
#define GET_TLARGEST(a, b, c) ((a) > (b) ? (((a) > (c)) ? (a) : (c)) :\
                                          (((b) > (c)) ? (b) : (c)))
#define GET_DLARGEST(a, b) ((a) > (b) ? (a) : (b))


/***********************************************************************/
/* Note: This is an extension of House Robber.                         */
/* After robbing those houses on that street, the thief has found      */
/* himself a new place for his thievery so that he will not get too    */
/* much attention. This time, all houses at this place are arranged in */
/* a circle. That means the first house is the neighbor of the last    */
/* one. Meanwhile, the security system for these houses remain the     */
/* same as for those in the previous street.                           */
/*                                                                     */
/* Given a list of non-negative integers representing the amount of    */
/* money of each house, determine the maximum amount of money you can  */
/* rob tonight without alerting the police.                            */
/***********************************************************************/
int rob(int* nums, int n)
{
    int i, g, *tarr;

    /* Less than 5 elements handled as a special case. */
    if (n == 1)
        return nums[0];
    else if (n == 2)
        return GET_DLARGEST(nums[0], nums[1]);
    else if (n == 3)
        return GET_TLARGEST(nums[0], nums[1], nums[2]);
    else if (n == 4)
        return GET_DLARGEST(nums[0] + nums[2], nums[1] + nums[3]);

    /* Allocate a temporary array. */
    if (!(tarr = malloc(n * sizeof(int))))
        return 0;
    memcpy(tarr, nums, n * sizeof(int)); // copy element

    /* Generate the largest sum by scanning from the end. Exclude
    the first element. The sub-structure here is a 4 element array,
    the sum generated will be arr[0] += LARGER(arr[2], arr[3]).
    Follow this one rule and generate the values by building on
    top of the previous sums. */
    tarr[n - 3] += tarr[n - 1];
    for (i = n - 4; i >= 1; --i)
        tarr[i] += GET_DLARGEST(tarr[i + 2], tarr[i + 3]);
    g = GET_DLARGEST(tarr[1], tarr[2]);

    /* Now generate the largest sum by excluding the last element. */
    nums[n - 1] = 0; // ignore the last value
    for (i = n - 4; i >= 0; --i)
        nums[i] += GET_DLARGEST(nums[i + 2], nums[i + 3]);
    g = GET_TLARGEST(g, nums[0], nums[1]);

    /* Free array and return the largest. */
    free(tarr);
    return g;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {2, 4, 8, 9, 9, 3};
    //int arr[] = {1, 1, 1};
    //int arr[] = {6,6,4,8,4,3,3,10};
    int len = sizeof(arr) / sizeof(int);
    printf("Max Robber Catch : %d \n", rob(arr, len));
    return 0;
}
