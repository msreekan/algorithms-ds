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
/* Reverse bits of a given 32 bits unsigned integer.                   */
/*                                                                     */
/* For example, given input 43261596 (represented in binary as         */
/* 00000010100101000001111010011100), return 964176192 (represented in */
/* binary as 00111001011110000010100101000000).                        */
/*                                                                     */
/* If this function is called many times, how would you optimize it?   */
/***********************************************************************/
uint32_t reverseBits(uint32_t n)
{   // Nibble reverse map 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
    static int map[16] = {0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9,
                        //10 11,  12,  13,  14,  15
                          0x5, 0xD, 0x3, 0xB, 0x7, 0xF};
    int rnum = 0, i;

    /* Reverse the order of reversed nibbles. */
    for (i = 0; i < 8 && (n >> (i * 4)); ++i)
        rnum |= map[(n >> (i * 4)) & 0xF] << (28 - (i * 4));
    return rnum;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    uint32_t val = 43261596;
    printf("Bits of %d (0x%x) reversed = %d(0x%x) :\n", val, val,
           reverseBits(val), reverseBits(val));
    return 0;
}
