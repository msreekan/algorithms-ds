/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************/
/* Macros                       */
/********************************/
#define DP_OFF(x, col, y) (((x) * (col)) + (y))
#define INT_MIN -0x7FFFFFFF
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

/***********************************************************************/
/* Dungeon Game : https://leetcode.com/problems/dungeon-game/          */
/***********************************************************************/
int calculateMinimumHP(int** dungeon, int dRSize, int dCSize)
{
    int *dp;
    int i, j, dpr = dRSize + 1, dpc = dCSize + 1, max;

    /* Validate and allocate the memory */
    if (!dungeon || dCSize < 1 || dRSize < 1 ||
        !(dp = calloc(dpr * dpc, sizeof(int))))
        return -1;

    /* Initialize the last column/row of DP array */
    for (i = 0; i < dpr - 2; ++i)
        dp[DP_OFF(i, dpc, dpc - 1)] = INT_MIN;
    for (i = 0; i < dpc - 2; ++i)
        dp[DP_OFF(dpr - 1, dpc, i)] = INT_MIN;

    /* Scan the array from the end. Pick the maximum of the two paths,
    and then the minimum of its sum with the present location. */
    for (i = dRSize - 1; i >= 0; --i)
        for (j = dCSize - 1; j >= 0; --j)
            dp[DP_OFF(i, dpc, j)] = MIN((dungeon[i])[j],
                                         MAX(dp[DP_OFF(i + 1, dpc, j)],
                                         dp[DP_OFF(i, dpc, j + 1)]) +
                                        (dungeon[i])[j]);

    /* Save the value, free the array, and return the minimum
    required value */
    max = dp[DP_OFF(0, dpc, 0)];
    free(dp);
    return max < 0 ? -max + 1 : 1;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 1
    int r0[] = {-2, -3, 3};
    int r1[] = {-5, 10, 1};
    int r2[] = {10, 30, -5};
    int *d[] = {r0, r1, r2};
    #elif 1
    int r0[] = {0, 1};
    int r1[] = {2, -3};
    int *d[] = {r0, r1};
    #elif 1
    int r0[] = {0};
    int *d[] = {r0};
    #elif 1
    int r0[] = {100};
    int *d[] = {r0};
    #endif // 1
    int clen = sizeof(r0) / sizeof(int);
    int rlen = sizeof(d) / sizeof(int *);
    printf("The Minimum Power = %d", calculateMinimumHP(d, rlen, clen));
    return 0;
}
