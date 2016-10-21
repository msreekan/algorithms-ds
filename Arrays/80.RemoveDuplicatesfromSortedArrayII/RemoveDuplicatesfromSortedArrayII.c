/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/* Macros                                           */
/****************************************************/
#define DUP_COUNT 3

/***********************************************************************/
/* What if duplicates are allowed at most twice?                       */
/* For example,                                                        */
/* Given sorted array nums = [1,1,1,2,2,3],                            */
/*                                                                     */
/* Your function should return length = 5, with the first five elements*/
/* of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave    */
/* beyond the new length.                                              */
/***********************************************************************/
int removeDuplicates(int* a, int len)
{
    int roff, wroff = 0, cnt = 0;

    /* Loop till the end of the array: Handle two states. */
    for (roff = 0; roff < len; ++roff) {
        /* 1. Duplicate count < DUP_COUNT -- Just Copy values and
              identify duplicates. */
        if (cnt < DUP_COUNT) {
            a[wroff++] = a[roff];
            cnt = roff + 1 < len && a[roff] == a[roff + 1] ? cnt + 1 : 0;
        }
        /* 2. Avoid copy, identify the end of duplicate sequence. */
        else if (a[roff] != a[roff - 1]) {
            cnt = 0; // reset
            --roff; // compensate for the increment above
        }
    }

    /* Return */
    return wroff;
}

/***********************************************************************/
/* prn_array: Print array                                              */
/*                                                                     */
/***********************************************************************/
void prn_array(int *a, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{           // 0  1  2  3  4  5  6  7  8  9  10 11  12
    #if 1
    int a[] = {0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3,  4};
    #elif 0
    int a[] = {1, 1, 2, 2, 2, 2, 3, 4, 4, 4, 5, 5, 6};
    #elif 1
    int a[] = {1,1,1,2};
    #endif
    int len = sizeof(a) / sizeof(int);
    prn_array(a, len);
    len = removeDuplicates(a, len);
    prn_array(a, len);
    return 0;
}
