/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#if O_N
/***********************************************************************/
/* Given an array nums containing n + 1 integers where each integer is */
/* between 1 and n (inclusive), prove that at least one duplicate      */
/* number must exist. Assume that there is only one duplicate number,  */
/* find the duplicate one.                                             */
/* Note:                                                               */
/* You must not modify the array (assume the array is read only).      */
/* You must use only constant, O(1) extra space.                       */
/* Your runtime complexity should be less than O(n2).                  */
/* There is only one duplicate number in the array, but it could be    */
/* repeated more than once.                                            */
/***********************************************************************/
int findDuplicate(int* nums, int nsz)
{
    int s, f;

    /* Validate. */
    if (!nums || nsz < 0)
        return 0;
    if (nsz < 3) return nums[0];


    /* Floyd's cycle finding algorithm:
                       7 (Cycle Length = 8)
                <----- l ----->
           4        4
       <-- c --><-- v-->

       0 1 2 3 4 5 6 7 8 9  10 11 12
       1 2 3 4 5 6 7 8 9 10 11 5  13
               |               | Loop
               |_______________|

          Once the slow and fast pointers hit, then
          we only need to move l - v steps to get to
          the entry point of the loop.

        Rough proof:

        Fast = Slow x 2;
        Fast = c + v + CL (Cycle Length);
        Slow = c + v

        Hence, after we hit Slow == Fast, reset the slow
        pointer and advance both until they are equal.
        They will meet at the entry, in CL - v steps, which
        incidently equals c steps.

        2 x (c + v) = c + v + CL;
        c + v = CL
        c = CV - v;
    */
    s = f = 0;
    do
    {
        s = nums[s];
        f = nums[nums[f]];
    } while (s != f);
    for (s = 0; s != f; s = nums[s], f = nums[f]);
    return s;
}
#else
/***********************************************************************/
/* Given an array nums containing n + 1 integers where each integer is */
/* between 1 and n (inclusive), prove that at least one duplicate      */
/* number must exist. Assume that there is only one duplicate number,  */
/* find the duplicate one.                                             */
/* Note:                                                               */
/* You must not modify the array (assume the array is read only).      */
/* You must use only constant, O(1) extra space.                       */
/* Your runtime complexity should be less than O(n2).                  */
/* There is only one duplicate number in the array, but it could be    */
/* repeated more than once.                                            */
/***********************************************************************/
int findDuplicate(int* nums, int nsz)
{
    int s = 1, e = nsz - 1, i, cnt, dcnt, mid;

    /* Validate. */
    if (!nums || nsz < 0)
        return 0;
    if (nsz < 3) return nums[0];

    /* N LogN method.*/
    while (s <= e)
    {
        /* Get the middle. */
        mid = s + (e - s + 1) / 2;

        /* Look for values less than the middle. */
        for (dcnt = 0, cnt = 0, i = 0; dcnt < 2 && i < nsz; ++i)
        {
            if (nums[i] <= mid)
                cnt++;
            if (nums[i] == mid)
                dcnt++;
        }

        /* If we have a hit, then return. */
        if (dcnt == 2)
            break;

        /* If the duplicated number is less than the value,
        then count would exceed the middle. */
        if (cnt > mid)
            e = mid - 1;
        else
            s = mid + 1;
    }
    return mid;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{   //         0 1 2 3 4
    //int a[] = {1,3,4,2,2};
    //int a[] = {1,1,2};
    //int a[] = {1,3,4,2,1};
    int a[] = {1, 4, 4, 2, 4};
    //int a[] = {4, 3, 1, 4, 2};
    //int a[] = {18,13,14,17,9,19,7,17,4,6,17,5,11,10,2,15,8,12,16,17};
    int len = sizeof(a) / sizeof(int);
    printf("Duplicate = %d :\n", findDuplicate(a, len));
    return 0;
}
