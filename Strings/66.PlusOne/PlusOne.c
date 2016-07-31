/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a non-negative number represented as an array of digits, plus */
/* one to the number.                                                  */
/*                                                                     */
/* The digits are stored such that the most significant digit is at the*/
/* head of the list.                                                   */
/***********************************************************************/
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    int *pdigit = digits;
    int i, c = 1;

    /* Trust but verify */
    if (!digits || !digitsSize || !returnSize)
        return NULL;

    /* Initialize */
    *returnSize = digitsSize;

    /* Start with the LSB and move towards the beginning */
    for (i = digitsSize - 1; i >= 0 && c; --i, c /= 10)
    {
        c = digits[i] + c;
        digits[i] = c % 10;
    }

    /* Pick the array based on carry */
    if (c)
    {
        /* Need to allocate more memory */
        pdigit = malloc(sizeof(int) * (digitsSize + 1));
        if (!pdigit)
            return digits;

        /* Copy the contents */
        *returnSize += 1;
        for (i = 1; i < *returnSize; ++i)
            pdigit[i] = digits[i];
        pdigit[0] = c;
    }

    /* Return the array */
    return pdigit;
}

/***********************************************************************/
/* prn_array: Print the array!                                         */
/*                                                                     */
/***********************************************************************/
void prn_array(int *a, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%d", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num1[] = {3, 4, 5, 6, 1, 2};
    int num2[] = {3, 4, 5, 6, 1, 9};
    int len1 = sizeof(num1) / sizeof(int);
    int len2 = sizeof(num1) / sizeof(int);
    int *num[] = {num1, num2}, *arr;
    int len[] = {len1, len2}, ret;
    int l = sizeof(num) / sizeof(int *), i;

    for (i = 0; i < l; ++i)
    {
        prn_array(num[i], len[i]);
        printf("+ 1 \n");
        arr = plusOne(num[i], len[i], &ret);
        prn_array(arr, ret);
        free(arr);
        printf("\n");
    }
    return 0;
}
