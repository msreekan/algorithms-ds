/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* Determine if a Sudoku is valid.                                     */
/*                                                                     */
/* The Sudoku board could be partially filled, where empty cells are   */
/* filled with the character '.'                                       */
/***********************************************************************/
int isValidSudoku(char** board, int boardRowSize, int boardColSize)
{
    int row, col, r = boardRowSize, c = boardColSize;

    /* Allocate three maps, corresponding to the three factors affecting
       the validity of a Sudoku matrix : One for the row,
       other for column and then for 9 (3 x 3) matrices. */
    int rmap[9][9] = {{0}}, cmap[9][9] = {{0}}, map[9][9] = {{0}};

    /* Parameter sanity */
    if (!board || !r || !c)
        return 0;

    /* Slick O(n) method, check each element once, identify the corresponding
    row, column, (3 x 3) block index and check the map values.
    Here is the outer loop for rows */
    for (row = 0; row < r; ++row)
    {
        /* Outer loop for columns */
        for (col = 0; col < c; ++col)
        {
            /* Calculate the (3 x 3) block index */
            int index = ((row / 3) * 3) + col / 3;

            /* Pick the string */
            char *str = board[row];

            /* If the character is valid, then proceed to check
            the maps */
            if (str[col] != '.')
            {
                /* If this value already exists in the (3 x 3) block
                then return error */
                if (map[index][str[col] - 49])
                    return 0;
                else
                    map[index][str[col] - 49] = 1;

                /* If this value already exist in the column, then return
                error */
                if (cmap[col][str[col] - 49])
                return 0;
                else
                cmap[col][str[col] - 49] = 1;

                /* If this value already exist in the row, then
                return error */
                if (rmap[row][str[col] - 49])
                    return 0;
                else
                    rmap[row][str[col] - 49] = 1;
            }
        }
    }

    /* Return success */
    return 1;
}

/***********************************************************************/
/* prn_sudoku: Print the array!                                        */
/*                                                                     */
/***********************************************************************/
void prn_sudoku(char **board, int r)
{
    int i;
    for(i = 0; i < r; ++i)
        printf("%s\n", board[i]);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char b1[] = "53..7....";
    char b2[] = "6..195...";
    char b3[] = ".98....6.";
    char b4[] = "8...6...3";
    char b5[] = "4..8.3..1";
    char b6[] = "7...2...6";
    char b7[] = ".6....28.";
    char b8[] = "...419..5";
    char b9[] = "....8..79";
    char *board[9] = {b1, b2, b3, b4, b5, b6, b7, b8, b9};

    prn_sudoku(board, 9);
    if (isValidSudoku(board, 9, 9))
        printf("Valid \n");
    else
        printf("Invalid :\n");
    return 0;
}
