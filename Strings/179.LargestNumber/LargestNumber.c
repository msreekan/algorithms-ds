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

/**********************************/
/* Macros                         */
/**********************************/
#define MAX_STR_SZ 16


/***********************************************************************/
/* CompareStr: Compare two strings!                                    */
/*                                                                     */
/***********************************************************************/
int CompareStr(char *s1, char *s2)
{
    char *ts1 = s1, *ts2 = s2;

    /* Loop while either of these strings are valid. The idea is to
    catch the string with the bigger leading characters.*/
    while (*ts1 || *ts2)
        /* If both the strings are valid, then either scan forward or
        break to return the difference. */
        if (*ts1 && *ts2) {
            /* Equal */
            if (*ts1 == *ts2) {
                ts1++;
                ts2++;
            }
            /* Unequal */
            else if (*ts1 != *ts2)
                break;
        }
        /* Else if only one of them is valid, then loop back and continue
        the scan */
        else if (*ts1)
            ts2 = s2;
        else
            ts1 = s1;
    /* Return the difference */
    return (int)(*ts1 - *ts2);
}


/***********************************************************************/
/* GetPivot: Get the pivot!                                            */
/*                                                                     */
/***********************************************************************/
int GetPivot(char **s, int start, int end)
{
    int i = start, j = end - 1, pivot = end;

    /* Loop seeking the pivot */
    while (i <= j)
    {
        /* Increment the index while the elements are less than or
        equal to pivot */
        if (i < end && CompareStr(s[i], s[pivot]) > 0)
            i++;

        /* Decrement index while the elements are greater than pivot */
        if (j >= start && CompareStr(s[j], s[pivot]) < 1)
            j--;

        /* Swap if the pointers have not crossed */
        if (i < j)
            INT_SWAP((int *)&s[i], (int *)&s[j]);
    }

    /* Swap the pivot into place */
    INT_SWAP((int *)&s[i], (int *)&s[pivot]);
    return i;
}

/***********************************************************************/
/* QuickSort: Quick sort!                                              */
/*                                                                     */
/***********************************************************************/
void QuickSort(char **s, int start, int end)
{
    int pivot;

    /* If the start is less than end, return */
    if (start >= end)
        return;

    /* Get the pivot */
    pivot = GetPivot(s, start, end);

    /* Recursively quick sort */
    QuickSort(s, start, pivot - 1);
    QuickSort(s, pivot + 1, end);
}


/***********************************************************************/
/* Given a list of non negative integers, arrange them such that they  */
/* form the largest number.                                            */
/* For example, given [3, 30, 34, 5, 9], the largest formed number is  */
/* 9534330.                                                            */
/***********************************************************************/
char *largestNumber(int* nums, int numsSize)
{
    int i, ssize = 0, slen;
    char *ch = NULL, *tch;
    char **cstr = NULL;

    /* Validate */
    if (!nums || numsSize < 1 ||
        !(cstr = malloc( numsSize * sizeof(char *) +
                        (numsSize * MAX_STR_SZ))))
        goto __lexit;
    tch = (char *)(cstr + numsSize);

    /* Convert integers into strings */
    for (i = 0; i < numsSize; ++i){
        cstr[i] = tch; // assign the previously allocated memory
        if (!(slen = sprintf(cstr[i],"%d",nums[i])))
            goto __lexit;
        tch += MAX_STR_SZ; // move to the next location
        ssize += slen;
    }

    /* Sort the strings */
    QuickSort(cstr, 0, numsSize - 1);

    /* Allocate space for the string */
    if (!(ch = malloc(sizeof(char) * (ssize + 1))))
        goto __lexit;

    /* Save the values into the string */
    strcpy(ch, cstr[0]);
    slen = strlen(cstr[0]);
    if ((cstr[0])[0] != '0')
        for (i = 1; i < numsSize; ++i) {
            strcat(&ch[slen], cstr[i]);
            slen += strlen(cstr[i]);
        }
__lexit:
    if (cstr) free(cstr);
    return ch;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //int a[] = {0,0};
    int a[] = {166, 11119, 23, 22, 11, 19};
    int len = sizeof(a) / sizeof(int);
    char *str;
    str = largestNumber(a, len);
    printf("\n\n%s", str);
    free(str);
    return 0;
}
