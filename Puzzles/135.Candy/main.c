/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

/***********************************************************************/
/* There are N children standing in a line. Each child is assigned a   */
/* rating value.                                                       */
/*                                                                     */
/* You are giving candies to these children subjected to the following */
/* requirements:                                                       */
/*                                                                     */
/* Each child must have at least one candy.                            */
/* Children with a higher rating get more candies than their neighbors.*/
/* What is the minimum candies you must give?                          */
/***********************************************************************/
int candy(int* ratings, int ratingsSize)
{
    int *dp = calloc(ratingsSize, sizeof(int));
    int i, sum = ratingsSize;

    /* Now run through the ratings ensuring the candy count difference
       is at least one when the ratings differ. */
    for (i = 0; i < ratingsSize - 1; ++i)
        if (ratings[i] > ratings[i + 1] && dp[i] <= dp [i + 1]){
            sum += dp [i + 1] + 1 - dp[i];
            dp[i] = dp [i + 1] + 1;
        }
        else if (ratings[i + 1] > ratings[i] && dp[i + 1] <= dp [i]) {
            sum += dp[i] + 1 - dp[i + 1];
            dp[i + 1] = dp[i] + 1;
        }
    /* Do the same from back to front */
    for (i = ratingsSize - 1; i >= 1; --i)
        if (ratings[i] > ratings[i - 1] && dp[i] <= dp[i - 1]) {
            sum += dp[i - 1] + 1 - dp[i];
            dp[i] = dp[i - 1] + 1;
        }
        else if (ratings[i - 1] > ratings[i] && dp[i - 1] <= dp[i]) {
            sum += dp[i] + 1  - dp[i - 1];
            dp[i - 1] = dp[i] + 1;
        }
    free(dp);
    return sum;
}
/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int r[] = {1,3,4,3,2,1};
    int len = sizeof(r) / sizeof(int);
    printf("Min Cadies = %d:\n", candy(r, len));
    return 0;
}
