/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***************************************/
/* Macros.                             */
/***************************************/
#define MAX_VAL(a, b) ((a) > (b) ? (a) : (b))

/***********************************************************************/
/* Say you have an array for which the ith element is the price of a   */
/* given stock on day i.                                               */
/* Design an algorithm to find the maximum profit. You may complete as */
/* many transactions as you like (ie, buy one and sell one share of the*/
/* stock multiple times) with the following restrictions:              */
/*                                                                     */
/* You may not engage in multiple transactions at the same time (ie,   */
/* you must sell the stock before you buy again).                      */
/* After you sell your stock, you cannot buy stock on next day. (ie,   */
/* cooldown 1 day)                                                     */
/* Example:                                                            */
/* prices = [1, 2, 3, 0, 2]                                            */
/* maxProfit = 3                                                       */
/* transactions = [buy, sell, cooldown, buy, sell]                     */
/***********************************************************************/
int maxProfit(int* p, int psz)
{
    int sell[3] = {0}, buy[2] = {0}, i;

    /* Allocate array to record profit values for various state
       transitions. */
    if (!p || psz < 1)
        return 0;

    /* Run through the list calculating the maximum profit for sell and
    buy transactions. */
    buy[0] = MAX_VAL(-p[0], -p[1]);
    sell[1] = MAX_VAL(sell[0], p[1] - p[0]);
    for (i = 2; i < psz; ++i)
    {
        /* Offset for buy will keep switching between 0 and 1. */
        buy[!(i & 1)] = MAX_VAL(sell[0] - p[i], buy[i & 1]);

        /* Get the maximum profit if we sell. */
        sell[2] = MAX_VAL(buy[0] + p[i], sell[1]);
        sell[0] = sell[1]; /* Shift the values. */
        sell[1] = sell[2];
    }

    /* Return the final profit. */
    return sell[1];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int a[] =  {1, 2, 3, 0, 2};
    #elif 0
    int a[] =  {6, 1, 3, 2, 4, 7};
    #elif 0
    int a[] = {2, 1, 2, 0, 1};
    #elif 0
    int a[] = {1, 4, 2, 7};
    #elif 0
    int a[] = {2, 6, 8, 7, 8, 7, 9, 4, 1, 2, 4, 5, 8};
    #elif 0
    int a[] = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    #elif 0
    int a[] = {1, 3, 5, 4, 3, 7, 6, 9, 2, 4};
    #elif 1
    int a[] = {8, 6, 4, 3, 3, 2, 3, 5, 8, 3, 8, 2, 6};
    #endif
    int len = sizeof(a) / sizeof(int);
    printf("Profit = %d :\n", maxProfit(a, len));
    return 0;
}
