#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CTONUM(x) ((x) - 49)
#define NUMTOC(x) ((x) + 49)

/***********************************************************************/
/* getSudokuMap: Generate the Sudoku map!                              */
/*                                                                     */
/***********************************************************************/
int getSudokuMap(char** board, int boardRowSize, int boardColSize,
                int *rmap, int *cmap, int *map, int *arr)
{
    int row, col, r = boardRowSize, c = boardColSize, en = 0;

    /* Parameter sanity */
    if (!board || !r || !c)
        return 0;

    /* Slick O(n) method, check each element once, identify the corresponding
    row, column, (3 x 3) block index and check the map values.
    Here is the outer loop for rows */
    for (row = 0; row < r; ++row)
    {
        /* Pick the string */
        char *str = board[row];

        /* Outer loop for columns */
        for (col = 0; col < c; ++col)
        {
            /* Calculate the (3 x 3) block index */
            int index = ((row / 3) * 3) + col / 3;

            /* If the character is valid, then proceed to set the maps */
            if (str[col] != '.')
            {
                int mask = 1 << CTONUM(str[col]);

                /* Update the maps */
                map[index] |= mask;
                cmap[col] |= mask;
                rmap[row] |= mask;
            }

            /* Else record the offset for the location to be filled */
            else
                arr[en++] = row * c + col;
        }
    }

    /* Return success */
    return en;
}

/***********************************************************************/
/* solve_sudoku: Recursively solve sudoku                              */
/*                                                                     */
/***********************************************************************/
int solve_sudoku(char** board, int rp, int cp, int row,
                 int col, int *rmap, int *cmap, int *map,
                 int *arr, int en)
{
    int i, index, r, c;
    char *str;

    /* We have reached the end */
    r = arr[en] / col;
    c = arr[en] % col;
    if ((r == row) && (c == 0))
        return 0;

    /* Set the map index and string */
    index = ((r / 3) * 3) + (c / 3);
    str = board[r];

    /* Loop to 9 attempting to place an element */
    for (i = 8; i >= 0; --i)
    {
        int mask = (1 << i);

        /* If the column, row or the block already contains
        the element, then skip */
        if ((rmap[r] | cmap[c] | map[index]) & mask)
            continue;

        /* Update the map and assign the element */
        rmap[r] |= mask;
        cmap[c] |= mask;
        map[index] |= mask;
        str[c] = NUMTOC(i);

        /* Now go ahead and fill the remaining locations */
        if (!solve_sudoku(board, r, c, row, col, rmap, cmap, map,
                          arr, en + 1))
            return 0;

        /* Revert the changes and loop to the next value */
        rmap[r] &= ~mask;
        cmap[c] &= ~mask;
        map[index] &= ~mask;
    }

    /* Failed to assign a value, no solution within this sub-tree */
    return 1;
}

/***********************************************************************/
/* Write a program to solve a Sudoku puzzle by filling the empty cells.*/
/*                                                                     */
/* Empty cells are indicated by the character '.'.                     */
/*                                                                     */
/* You may assume that there will be only one unique solution.         */
/***********************************************************************/
void solveSudoku(char** board, int boardRowSize, int boardColSize)
{
    /* Allocate three maps, corresponding to the three factors affecting
       the validity of a Sudoku matrix : One for the row,
       other for column and then for 9 (3 x 3) matrices. */
    int rmap[9] = {0}, cmap[9] = {0}, map[9] = {0};
    int arr[9 * 9 + 1], en;

    /* Generate the map, assumption is that there at least one
    unique solution */
    en = getSudokuMap(board, boardRowSize, boardColSize, rmap, cmap,
                      map, arr);
    /* End marker */
    arr[en] = boardRowSize * boardColSize;

    /* Solve Sudoku */
    solve_sudoku(board, 0, 0, boardRowSize, boardColSize, rmap, cmap,
                 map, arr, 0);
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
    printf("\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char a1[] = "..9748...";
    char a2[] = "7........";
    char a3[] = ".2.1.9...";
    char a4[] = "..7...24.";
    char a5[] = ".64.1.59.";
    char a6[] = ".98...3..";
    char a7[] = "...8.3.2.";
    char a8[] = "........6";
    char a9[] = "...2759..";
    char *a[9] = {a1, a2, a3, a4, a5, a6, a7, a8, a9};

    prn_sudoku(a, 9);
    solveSudoku(a, 9, 9);
    prn_sudoku(a, 9);
    return 0;
}
