/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifdef ITERATIVE
/***********************************************************************/
/* Say you have an array for which the ith element is the price of a   */
/* given stock on day i.                                               */
/* Design an algorithm to find the maximum profit. You may complete as */
/* many transactions as you like (ie, buy one and sell one share of the*/
/* stock multiple times). However, you may not engage in multiple      */
/* transactions at the same time (ie, you must sell the stock before   */
/* you buy again).                                                     */
/***********************************************************************/
int maxProfit(int* prices, int pricesSize)
{
    int i, profit = 0;
    for (i = 1; i < Size; ++i)
        profit += (p[i] > p[i - 1]) ? p[i] - p[i - 1] : 0;
    return profit;
}
#else
/***********************************************************************/
/* Say you have an array for which the ith element is the price of a   */
/* given stock on day i.                                               */
/* Design an algorithm to find the maximum profit. You may complete as */
/* many transactions as you like (ie, buy one and sell one share of the*/
/* stock multiple times). However, you may not engage in multiple      */
/* transactions at the same time (ie, you must sell the stock before   */
/* you buy again).                                                     */
/***********************************************************************/
int maxProfit(int* p, int pSize)
{
    return  (pSize > 1) ? (p[1] -  p[0] > 0 ? p[1] -  p[0] +
                           maxProfit(&p[1], pSize - 1) :
                           maxProfit(&p[1], pSize - 1)) : 0;
}
#endif


/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] =  {3,3,5,0,0,3,1,4};
    int len = sizeof(a) / sizeof(int);
    printf("Max Profit = %d", maxProfit(a, len));
    return 0;
}
