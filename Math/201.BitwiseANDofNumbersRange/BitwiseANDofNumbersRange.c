/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given a range [m, n] where 0 <= m <= n <= 2147483647, return the    */
/* bitwise AND of all numbers in this range, inclusive.                */
/* For example, given the range [5, 7], you should return 4.           */
/*                                                                     */
/***********************************************************************/
int rangeBitwiseAnd(int m, int n)
{
    int msb;
    /*
    ** A bitwise AND of m and n gives only a partial answer, numbers
    ** in between m and n might still cause resetting of some of the
    ** other least significant bits (LSBs).
    **
    ** Consider [5, 7] :
    ** 5(101b) & 7(111b) = 101b
    **
    ** Here the number 6 in the incrementing sequence would cause the
    ** LSB 0 to get reset. To figure this out, we need to find the first
    ** distinct MSB bit. In this case it's MSB 1.
    **
    ** We know this bit would be set in the larger number ('n') only
    ** because LSBs to the right of this bit was reset at least once
    ** during this incrementing sequence. For example, we cannot reach
    ** 1011b without going through 1000b.
    **
    ** Instead of a C loop, we could use an assembly instruction "bsrl"
    ** to figure out this MSB. Makes the code platform dependent, but
    ** it's an interesting approach.
    **
    */
    __asm__("bsrl %1,%0" : "=r"(msb) : "r"(m ^ n));
    return m == n ? m & n : m & n & ~((1 << msb) - 1);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int m = 2, n = 3;
    printf("Bitwise AND sequence = %d \n", rangeBitwiseAnd(m, n));
    return 0;
}
