/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/generic.h"

/********************************************/
/* Macros                                   */
/********************************************/
#define O_1 1 // TRUE for O(1) space solution

#if O_1
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
void reverse(int* nums, int n)
{
    int i, j;
    for (i = 0, j = n - 1; i < j; i++, --j)
        INT_SWAP(&nums[i], &nums[j]);
}

/***********************************************************************/
/* Rotate an array of n elements to the right by k steps.              */
/*                                                                     */
/* For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is     */
/* rotated to [5,6,7,1,2,3,4].                                         */
/***********************************************************************/
void rotate(int* nums, int n, int k)
{
    /* Calculate the rotate value */
    k = k % n;

    /* Reverse the whole array, then the 1st segment, and 2nd segment */
    reverse(nums, n);
    reverse(nums, k);
    reverse(&nums[k], n - k);
}
#else
/***********************************************************************/
/* Rotate an array of n elements to the right by k steps.              */
/*                                                                     */
/* For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is     */
/* rotated to [5,6,7,1,2,3,4].                                         */
/***********************************************************************/
void rotate(int* nums, int n, int k)
{
    int i, j;
    int *arr;

    /* Calculate the rotate value */
    k = k % n;

    /* Allocate the array. */
    if (k == n || !(arr = malloc(sizeof(int) * n)))
        return;

    /* Copy the contents while swapping the segments. */
    for (i = 0, j = n - k; j < n && i + k < n; ++j, ++i) {
        arr[i] = nums[j];
        arr[i + k] = nums[i];
    }
    for (;i + k < n; ++i)
        arr[i + k] = nums[i];
    for (;j < n; ++j, ++i)
        arr[i] = nums[j];

    /* Copy back the whole array */
    memcpy(nums, arr, sizeof(int) * n);
    free(arr);
}
#endif
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 1
    int arr[] = {1,2,3,4,5,6,7,8};
    int k = 6;
    #elif 1
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
    int k = 38;
    #endif
    int len = sizeof(arr) / sizeof(int);

    printf("Before Rotation : \n");
    PrintArray(arr, len);

    rotate(arr, len, k);

    printf("\nAfter Rotation : \n");
    PrintArray(arr, len);

    return 0;
}
