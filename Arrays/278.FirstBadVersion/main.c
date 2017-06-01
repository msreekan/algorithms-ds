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

// Forward declaration of isBadVersion API.
bool isBadVersion(int version)
{
    return version >= 2 ? true : false;
}

/***********************************************************************/
/* You are a product manager and currently leading a team to develop a */
/* new product. Unfortunately, the latest version of your product fails*/
/* the quality check. Since each version is developed based on the     */
/* previous version, all the versions after a bad version are also bad.*/
/* Suppose you have n versions [1, 2, ..., n] and you want to find out */
/* the first bad one, which causes all the following ones to be bad.   */
/* You are given an API bool isBadVersion(version) which will return   */
/* whether version is bad. Implement a function to find the first bad  */
/* version. You should minimize the number of calls to the API.        */
/***********************************************************************/
int firstBadVersion(int n)
{
    int start = 1, end = n, mid;
    bool s;

    /* Binary lookup for bad version. */
    while (start <= end)
    {
        /* Get the middle of the array. */
        mid = start + (end - start + 1) / 2;

        /* If we have the bad version and the previous version was good,
           then we have a hit. */
        s = isBadVersion(mid);
        if (s && ((mid == 1) || !isBadVersion(mid - 1)))
            return mid;
        /* Else adjust the pointers. */
        else if (!s)
            start = mid + 1;
        else
            end = mid - 1;
    }

    /* Return start. */
    return 1;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 2;
    printf("First bad version = %d :\n", firstBadVersion(num));
    return 0;
}
