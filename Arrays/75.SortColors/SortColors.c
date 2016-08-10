/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************/
/* Local prototype                  */
/************************************/
void set_pivot(int* a, int len, int p);

/***********************************************************************/
/* swap_int: Swap integers!                                            */
/*                                                                     */
/***********************************************************************/
void swap_int(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

/***********************************************************************/
/* prn_arr: Print the array!                                           */
/*                                                                     */
/***********************************************************************/
void prn_arr(int *a, int num)
{
    int i;
    for (i = 0; i < num; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}

/***********************************************************************/
/* Given an array with n objects colored red, white or blue, sort them */
/* so that objects of the same color are adjacent, with the colors in  */
/* the order red, white and blue.                                      */
/*                                                                     */
/* Here, we will use the integers 0, 1, and 2 to represent the color   */
/* red, white, and blue respectively.                                  */
/*                                                                     */
/* Note:                                                               */
/* You are not suppose to use the library's sort function for this     */
/* problem.                                                            */
/*                                                                     */
/***********************************************************************/
#if TWO_PASS
void sortColors(int* nums, int numsSize)
{
    int c[3] = {0}, i, j;

    /* Get the red, white, blue counters */
    for (i = 0; i < numsSize; ++i)
        c[nums[i]]++;

    /* Set the colours in the order red, white, blue */
    for (i = 0, j = 0; i < numsSize; ++i, --c[j])
    {
        while (c[j] == 0) ++j;
        if (j > 2) break;
        nums[i] = j;
    }
}
#else
void sortColors(int* nums, int numsSize)
{
    set_pivot(nums, numsSize, 2); // pivot as 2
    set_pivot(nums, numsSize, 1); // pivot as 1
}

/***********************************************************************/
/* set_pivot: Set pivot!                                               */
/*                                                                     */
/***********************************************************************/
void set_pivot(int* a, int len, int p)
{
    int i = 0, j = len - 1;

    /* Loop seeking pivot */
    while (i < j)
    {
        while ((i < len) && a[i] < p) ++i;
        while ((j > 0) && a[j] >= p) --j;
        if (i < j) swap_int(&a[i], &a[j]);
    }
}
#endif // ONE_PASS

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {0, 0, 1, 2, 0, 2, 1, 0, 0, 2, 1, 0};
    int len = sizeof(a) / sizeof(int);
    prn_arr(a, len);
    sortColors(a, len);
    prn_arr(a, len);
    return 0;
}
