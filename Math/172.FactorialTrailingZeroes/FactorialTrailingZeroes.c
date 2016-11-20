/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given an integer n, return the number of trailing zeroes in n!.     */
/* Note: Your solution should be in logarithmic time complexity.       */
/***********************************************************************/
int trailingZeroes(int n)
{
    /*  The trailing zeros are created by multiplication with 10 = 5 x 2:
        10s can be formed by 5 x 2, 2s are in abundance, so we need to
        only figure out the number of 5s in the factorial multiplication
        sequence.
        5! = 1 x 2 x 3 x 4 x 5 -- 1 five, one trailing zero
        10! = 1 x 2 x 3 x 4 x 5 x 6 x 7 x 8 x 9 x (5 x 2) - 2 fives
        25! = 10! x 11 x 12 x 13 x 14 x (5 x 3) x 16 x 17 x 18 x 19 x
             (4 x 5) x 21 x 22 x 23 x 24 x (5 x 5)

        As mentioned above, the idea is to count the number of 5s.
        It's almost as if we are placing all the elements in the
        factorial sequence within an array, and dividing every element
        by 5. This division is only done if the element is multiple of 5.
        Total number of such divisions should give us the number of 5s,
        and hence the number of trailing zeros also. This would be O(n)
        space and O(n) time complexity
            for (i = 1; i <= n; ++i) // populate the sequence
                    arr[i - 1] = i;
            do{
                for (f = 0, i = 0; i < n; ++i)
                  if (!(arr[i] % 5)) // detect multiples of 5
                  {
                      count++; // count of 5s
                      f = 1;
                      arr[i] /= 5;
                  }
            } while (f);
            return count;
        The number of multiples of 5 within a factorial sequence can also
        be calculated by simply dividing the largest element by 5! So
        dividing a number 'n' by 5 gives the number of multiple of 5
        within the range [1, n]. But if this range contains elements which
        are multiples of powers of 5, then the quotient (q) will also be
        greater than or equal to 5. Considering the equation n >= q x 5,
        if q >= 5, then n has to be greater than or equal to 25. So there
        is at least one 5 ^ 2 within the sequence. So, with the first
        division we count the number of multiples of 5 ^ 1, with the
        second we count the number of multiples of 5 ^ 2, then 5 ^ 3 and
        so on. Recursively applying this logic gives a call stack depth of
        Log5(n). Time complexity would be O(Log5(n)).
    */
    return n > 0 ? n / 5 + trailingZeroes(n / 5) : 0;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Trailing zeros in factorial = %d :\n", trailingZeroes(30));
    return 0;
}
