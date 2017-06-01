/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************************************************/
/* You are playing the following Nim Game with your friend: There is a */
/* heap of stones on the table, each time one of you take turns to     */
/* remove 1 to 3 stones. The one who removes the last stone will be the*/
/* winner. You will take the first turn to remove the stones.          */
/* Both of you are very clever and have optimal strategies for the     */
/* game. Write a function to determine whether you can win the game    */
/* given the number of stones in the heap.                             */
/* For example, if there are 4 stones in the heap, then you will never */
/* win the game: no matter 1, 2, or 3 stones you remove, the last stone*/
/* will always be removed by your friend.                              */
/***********************************************************************/
bool canWinNim(int n)
{
    /* The idea is to always leave 4 stones for the very last pick.
    This is possible only if the total number of stones is not a multiple
    of 4. */
    return n % 4 ? true : false;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 10;
    printf("NIM Game for %d = %d \n", n, canWinNim(n));
    return 0;
}
