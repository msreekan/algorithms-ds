/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**************************************/
/* Macros                             */
/**************************************/
#define INT_TO_ASCII(x) ((x) + 48)
#define MAX_NUM_LEN     12 // max for int + 2
#define MAX_RANGE_LEN   (MAX_NUM_LEN * 2)
#define SWAP_CHAR(x, y) {\
                         char c = x;\
                         x = y;\
                         y = c;\
                         }


/***********************************************************************/
/* t_itoa: Local int to ascii!                                         */
/*                                                                     */
/***********************************************************************/
int t_itoa(int num, char *s)
{
    int off = 0, div = 10, j = 0, i;
    long long tnum = num;

    /* If the number is negative, then add '-' */
    if (tnum < 0) {
        s[off++] = '-';
        tnum = -tnum;
    }

    /* Extract all the digits. */
    do
        s[off++] = INT_TO_ASCII(tnum % div);
    while (tnum /= div);

    /* Reverse the order. */
    if (s[0] == '-')
        j = 1;
    for (i = off - 1; i > j; i--, j++)
        SWAP_CHAR(s[i], s[j]);

    /* NULL Terminate. */
    s[off] = 0;
    return off;
}

/***********************************************************************/
/* Given a sorted integer array without duplicates, return the summary */
/* of its ranges. For example, given [0,1,2,4,5,7]:                    */
/* return ["0->2","4->5","7"].                                         */
/***********************************************************************/
char** summaryRanges(int* nums, int numsSize, int* returnSize)
{
    int i, pnum, rnum = 0, roff;
    char **carr;

    /* Validate the parameters. */
    if (!nums || numsSize <= 0 || !returnSize)
        return NULL;
    *returnSize = 0;

    /* Allocate space for the array. */
    carr = malloc(numsSize * sizeof(char **));
    if (!carr)
        return NULL;

    /* Get the first value. */
    pnum = nums[0];
    if (!(carr[rnum] = malloc(sizeof(char) * MAX_RANGE_LEN)))
        return carr;
    roff = t_itoa(pnum, carr[rnum]);

    /* Loop through the list. */
    for (i = 1; i < numsSize; ++i)
    {
        /* If we have a new range, then add that. */
        if (nums[i] != nums[i - 1] + 1)
        {
            /* If needed, complete the previous range. */
            if (pnum != nums[i - 1])
            {
                (carr[rnum])[roff++] = '-';
                (carr[rnum])[roff++] = '>';
                t_itoa(nums[i - 1], &(carr[rnum])[roff]);
            }

            /* Allocate new memory. */
            rnum++;
            carr[rnum] = malloc(sizeof(char) * MAX_RANGE_LEN);
            if (!carr[rnum])
                return carr;
            roff = t_itoa(nums[i], carr[rnum]);
            pnum = nums[i];
        }
    }

    /* Complete any pending ranges. */
    if (numsSize > 1 && nums[i - 2] + 1 == nums[i - 1])
    {
        (carr[rnum])[roff++] = '-';
        (carr[rnum])[roff++] = '>';
        t_itoa(nums[i - 1], &(carr[rnum])[roff]);
    }

    *returnSize = rnum + 1;
    return carr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int arr[] = {0, 1, 2, 4, 5, 7};
    #elif 0
    int arr[] = {234, 235, 999, 1000};
    #elif 0
    int arr[] = {0,1,2,4,5,7,9,10,12,14,15,16,27,28};
    #elif 0
    int arr[] = {-5,-4,-3,-2,-1,0,1,4,5,7,9,10,12,14,15,16,27,28};
    #elif 1
    int arr[] = {1};
    #endif
    int len = sizeof(arr) / sizeof(int), ret, i;
    char **c;

    /* Get the ranges. */
    c = summaryRanges(arr, len, &ret);
    for (i = 0; i < ret; ++i)
    {
        printf("%s:\n", c[i]);
        free(c[i]);
    }
    free(c);
    return 0;
}
