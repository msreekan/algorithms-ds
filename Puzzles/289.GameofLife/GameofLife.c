/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* GameOfLife: Recursively modify the array!                           */
/*                                                                     */
/***********************************************************************/
void GameOfLife(int** b, int rsz, int csz, int r, int c)
{
    int count = 0, nc = c + 1, nr = r, i, j;

    /* Count the neighbors. Ensure the index is within the bounds and
       it's not the cell at [r, c]. */
    for (i = r - 1 < 0 ? 0 : r - 1; i < r + 2 && i < rsz; ++i)
        for (j = c - 1 < 0 ? 0 : c - 1; j < c + 2 && j < csz; ++j)
            if (!(i == r && j == c) && (b[i])[j])
                count++;

    /* If it's the end of the row, then move to the next one. */
    if (c == csz - 1) {
        nc = 0;
        nr++;
    }

    /* If we are within the bounds, then continue the traversal. */
    if (nr < rsz)
        GameOfLife(b, rsz, csz, nr, nc);
    /* Determine the status of the cell. */
    if (count < 2 || count > 3)
        (b[r])[c] = 0;
    else if (count == 3)
        (b[r])[c] = 1;
}

/***********************************************************************/
/* According to the Wikipedia's article: "The Game of Life, also known */
/* simply as Life, is a cellular automaton devised by the British      */
/* mathematician John Horton Conway in 1970."                          */
/* Given a board with m by n cells, each cell has an initial state live*/
/* (1) or dead (0). Each cell interacts with its eight neighbors       */
/* (horizontal, vertical, diagonal) using the following four rules     */
/* (taken from the above Wikipedia article):                           */
/*                                                                     */
/* Any live cell with fewer than two live neighbors dies, as if caused */
/* by under-population.                                                */
/* Any live cell with two or three live neighbors lives on to the next */
/* generation.                                                         */
/* Any live cell with more than three live neighbors dies, as if by    */
/* over-population..                                                   */
/* Any dead cell with exactly three live neighbors becomes a live cell,*/
/* as if by reproduction.                                              */
/*                                                                     */
/* Write a function to compute the next state (after one update) of the*/
/* board given its current state.                                      */
/* Follow up:                                                          */
/* Could you solve it in-place? Remember that the board needs to be    */
/* updated at the same time: You cannot update some cells first and    */
/* then use their updated values to update other cells.                */
/* In this question, we represent the board using a 2D array. In       */
/* principle, the board is infinite, which would cause problems when   */
/* the active area encroaches the border of the array. How would you   */
/* address these problems?                                             */
/*                                                                     */
/***********************************************************************/
void gameOfLife(int** b, int brsz, int bcsz)
{
    if (!b || brsz < 1 || bcsz < 1)
      return;
    GameOfLife(b, brsz, bcsz, 0, 0);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    printf("Hello world!\n");
    return 0;
}
