/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Utils/generic.h"

/***********************************************************************/
/* MergeArr: Merge two sorted arrays!                                  */
/*                                                                     */
/***********************************************************************/
void MergeArr(int *arr1, int *arr2, int *arr3, int len1, int len2)
{
    int s1 = 0, s2 = 0, s3 = 0;

    /* Loop while both the arrays are valid. */
    while (s1 < len1 && s2 < len2)
    {
        /* Pick the smaller element. */
        if (arr1[s1] < arr2[s2])
            arr3[s3++] = arr1[s1++];
        else
            arr3[s3++] = arr2[s2++];
    }

    /* Merge any remaining values. */
    while (s1 < len1)
        arr3[s3++] = arr1[s1++];
    while (s2 < len2)
        arr3[s3++] = arr2[s2++];
}

/***********************************************************************/
/* MergeSort: Merge Sort!                                              */
/*                                                                     */
/***********************************************************************/
void MergeSort(int *arr1, int *arr2, int start, int len)
{
    int len1 = (len / 2), len2 = len & 1 ? len / 2 + 1 : len / 2;

    /* Terminating condition. */
    if (len < 2)
        return;

    /* Merge Sort the first half. And second half. */
    MergeSort(arr1, arr2, start, len1);
    MergeSort(arr1, arr2, start + len1, len2);

    /* Merge arrays and copy back the contents. */
    MergeArr(&arr1[start], &arr1[start + len1], arr2, len1, len2);
    memcpy(&arr1[start], arr2, len * sizeof(int));
}

/***********************************************************************/
/* Given an array of integers, find if the array contains any          */
/* duplicates. Your function should return true if any value appears at*/
/* least twice in the array, and it should return false if every       */
/* element is distinct.                                                */
/***********************************************************************/
bool containsDuplicate(int* nums, int numsSize)
{
    int i;
    int *marr;

    /* Allocate array for merge sort. */
    marr = malloc(sizeof(int) * numsSize);
    if (!marr) return false;

    /* Sort the array. */
    MergeSort(nums, marr, 0, numsSize);

    /* Look for duplicates. */
    for (i = 0; i < numsSize - 1; ++i)
        if (nums[i] == nums[i + 1])
            return true;

    /* No duplicates. */
    return false;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {2,5,3,1,5, 4};
    int len = sizeof(arr) / sizeof(int);

    printf("Before Sort. \n");
    PrintArray(arr, len);
    printf("\n");

    printf("Duplicate? = %c \n", containsDuplicate(arr, len) ? 'Y' : 'N');

    printf("After Sort. \n");
    PrintArray(arr, len);
    printf("\n");
    return 0;
}
