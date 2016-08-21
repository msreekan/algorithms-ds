/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool; // custom data type

/*****************************/
/* Macros                    */
/*****************************/
#define TRUE 1
#define FALSE 0


/***********************************************************************/
/* cexist: Recursively check for string!                               */
/*                                                                     */
/***********************************************************************/
bool cexist(char** b, unsigned char *map, int r, int c, int rsz, int csz,
            char* w)
{
    bool ret = FALSE;

    /* Finished processing the string */
    if (*w == 0)
        return TRUE;

    /* Validate the board offsets, do not account for one cell more than
       once, or if the characters are unequal then return FALSE. */
    if (r >= rsz || c >= csz || r < 0 || c < 0 ||
        map[r * csz + c] || (*(b[r] + c) != *w))
        return FALSE;

    /* If the characters match, then move into surrounding cells. */
    map[r * csz + c] = 1;
    ret = (ret == 0) ? cexist(b, map, r + 1, c, rsz, csz, w + 1) : ret;
    ret = (ret == 0) ? cexist(b, map, r, c + 1, rsz, csz, w + 1) : ret;
    ret = (ret == 0) ? cexist(b, map, r - 1, c, rsz, csz, w + 1) : ret;
    ret = (ret == 0) ? cexist(b, map, r, c - 1, rsz, csz, w + 1) : ret;
    map[r * csz + c] = 0;

    /* Return status */
    return ret;
}

/***********************************************************************/
/* Given a 2D board and a word, find if the word exists in the grid.   */
/*                                                                     */
/* The word can be constructed from letters of sequentially adjacent   */
/* cell, where "adjacent" cells are those horizontally or vertically   */
/* neighboring. The same letter cell may not be used more than once.   */
/*                                                                     */
/* For example,                                                        */
/* Given board =                                                       */
/* [                                                                   */
/*  ['A','B','C','E'],                                                 */
/*  ['S','F','C','S'],                                                 */
/*  ['A','D','E','E']                                                  */
/* ]                                                                   */
/*                                                                     */
/* word = "ABCCED", -> returns true,                                   */
/* word = "SEE", -> returns true,                                      */
/* word = "ABCB", -> returns false.                                    */
/***********************************************************************/
bool exist(char** board, int boardRowSize, int boardColSize, char* word)
{
    unsigned char *map;
    bool ret = 0;
    int r = 0, c = 0;
    int mlen = boardRowSize * boardColSize;

    /* Allocate memory for map*/
    map = calloc(mlen, sizeof(unsigned char));
    if (!map)
        return FALSE;

    /* Scan the the board looking for a match */
    while (r < boardRowSize && !ret)
    {
        /* If the characters match, then do a DFS */
        if (*(board[r] + c) == *word)
            ret = cexist(board, map, r, c, boardRowSize, boardColSize,
                         word);
        /* Move to the next character on the board */
        c += 1;
        r = (c == boardColSize) ? r + 1 : r;
        c = (c == boardColSize) ? 0 : c;
    }
    free(map);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char a1[] = "FYCENRD", a2[] = "KLNFINU", a3[] = "AAARAHR";
    char a4[] = "NDKLPNE", a5[] = "ALANSAP", a6[] = "OOGOTPN";
    char a7[] = "HPOLANO";
    char *a[] = {a1, a2, a3, a4, a5, a6, a7};
    char w[] = "USA";
    int r = sizeof(a) / sizeof(char *);
    int c = strlen(a1);

    printf("%d", exist(a, r, c, w));
    return 0;
}
