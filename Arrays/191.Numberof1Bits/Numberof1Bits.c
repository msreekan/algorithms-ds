/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*******************************************/
/* Types                                   */
/*******************************************/
typedef unsigned int uint32_t;

/***********************************************************************/
/* Write a function that takes an unsigned integer and returns the     */
/* number of ’1' bits it has (also known as the Hamming weight).       */
/*                                                                     */
/* For example, the 32-bit integer ’11' has binary representation      */
/* 00000000000000000000000000001011, so the function should return 3.  */
/***********************************************************************/
int hammingWeight(uint32_t n)
{
    // Nibble bit count   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
    static int map[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2,  3,  2,  3,
    //                    14, 15.
                          3,  4};
    /* Return the sum of bit count. */
    return map[n & 0xF] + map[(n >> 4) & 0xF] + map[(n >> 8) & 0xF] +
           map[(n >> 12) & 0xF] + map[(n >> 16) & 0xF] +
           map[(n >> 20) & 0xF] + map[(n >> 24) & 0xF] +
           map[(n >> 28) & 0xF];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int val = 13;
    printf("Hamming weight for %d (0x%x) = %d :\n", val, val,
           hammingWeight(val));
    return 0;
}
