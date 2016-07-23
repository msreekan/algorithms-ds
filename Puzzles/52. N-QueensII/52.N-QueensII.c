/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prn_map(int n, unsigned short *map);

/*********************************/
/* Basic macros                  */
/*********************************/
#define SAFE_LOC   0
#define UNSAFE_LOC 1
#define MARK_LOC(v, loc) {\
                            if ((v) == SAFE_LOC)\
                                (loc)--;\
                            else\
                                (loc)++;\
                         }

/***********************************************************************/
/* check_loc: Check whether location is dangerous or safe              */
/*                                                                     */
/***********************************************************************/
int check_loc(unsigned char *map, int k, int c, int n)
{
    int ld = (c > k) ? (n + (c - k)) : (k - c);

    /* Check whether the rows, column and diagonals are free */
    if (map[c] || map[n + k] || map[(n * 2) + c + k] ||
        map[(n * 4) + ld])
        return 1;
    return 0;
}

/***********************************************************************/
/* mark_loc: Mark the locations as dangerous or safe                    */
/*                                                                     */
/***********************************************************************/
void mark_loc(unsigned char *map, int k, int c, int n, int val)
{
    int ld = (c > k) ? (n + (c - k)) : (k - c);

    /* Mark the row and column. It's easy to encode rows and columns
       with a simple array of size n, one location for each row/column
          0  1  2  3   <-- Columns codes
        0 00 01 02 03
        1 10 11 12 13
        2 20 21 22 23
        3 30 31 32 33
        ^
        ^
        Row codes
    */
    MARK_LOC(val, map[c]);
    MARK_LOC(val, map[n + k]);

    /* Upper diagonal offsets can be coded using the column + row
       combination. For example, (10, 01) or (20, 22, 02).
          0  1  2  3 -|--- Upper diagonal codes
          00 01 02 03 |
          10 11 12 13 4
          20 21 22 23 5
          30 31 32 33 6
    */
    MARK_LOC(val, map[(n * 2) + c + k]);

    /* Lower diagonal encoding is slightly more complex. It can be
    coded using either the row value or the column value.
    If the row is greater then it's picked, else column.
       Lower diagonal codes >>> 0  4  5  6
                              0 00 01 02 03
                              1 10 11 12 13
                              2 20 21 22 23
                              3 30 31 32 33
    */
    MARK_LOC(val, map[(n * 4) + ld]);
}

/***********************************************************************/
/* nqueens: Recursive nqueens problem                                  */
/*                                                                     */
/***********************************************************************/
void nqueens(unsigned char *map, int c, int n, int *solcnt)
{
    int k;

    /* We have a solution */
    if (c == n)
    {
        (*solcnt) += 1;
        return;
    }

    /* Loop through the rows looking for a safe location */
    for (k = 0; k < n; ++k)
    {
        if (!check_loc(map, k, c, n))
        {
            /* Mark the locations as unsafe */
            mark_loc(map, k, c, n, UNSAFE_LOC);

            /* Attempt to place more queens */
            nqueens(map, c + 1, n, solcnt);

            /* Mark the locations as safe */
            mark_loc(map, k, c, n, SAFE_LOC);
        }
    }
}

/***********************************************************************/
/* The n-queens puzzle is the problem of placing n queens on an n×n    */
/* chessboard such that no two queens attack each other.               */
/***********************************************************************/
int totalNQueens(int n)
{
    unsigned char *map;
    int ret = 0;

    /* Allocate the memory for map */
    map = calloc((n * 6), sizeof(unsigned char));
    if (!map)
        return -1;
    nqueens(map, 0, n, &ret);
    free(map);
    return ret;
}

/***********************************************************************/
/* prn_map: Print map                                                  */
/*                                                                     */
/***********************************************************************/
void prn_map(int n, unsigned short *map)
{
    int j, k;
    for (j = 0; j < n; ++j)
    {
        for (k = 0; k < n; ++k)
            printf("%d ", map[j * n + k]);
        printf("\n\n");
    }
    printf("\n\n");
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 9;
    printf ("Nqueens %d = %d :\n", n, totalNQueens(n));
    return 0;
}
