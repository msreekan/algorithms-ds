/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/stack.h"

/******************************************/
/* Data Structure                         */
/******************************************/
struct ch_pos
{
    int r;
    int c;
};


/***********************************************************************/
/* ResetO: DFS + Stack to the rescue                                   */
/*                                                                     */
/***********************************************************************/
void ResetO(char** b, int bRSz, int bCSz, int r, int c, void *stack)
{
    struct ch_pos pos;

    /* If the value at the location is not 'O', then return. */
    if ((b[r])[c] != 'O') return;

    /* Push the element to the stack */
    pos = (struct ch_pos){r, c};
    if (StackPush(stack, &pos)) return;

    /* Process all the stack elements */
    while (!StackPop(stack, &pos)) {
        (b[pos.r])[pos.c] = 'T';

        /* Attempt to push the neighboring cell on the next row */
        if ((++pos.r < bRSz) && (b[pos.r])[pos.c] == 'O')
            StackPush(stack, &pos);
        --pos.r;

        /* Attempt to push the neighboring cell on the same row */
        if ((++pos.c < bCSz) && (b[pos.r])[pos.c] == 'O')
            StackPush(stack, &pos);
        --pos.c;

        /* Attempt to push the neighboring cell on the same row */
        if ((--pos.c >= 0) && (b[pos.r])[pos.c] == 'O')
            StackPush(stack, &pos);
        ++pos.c;

        /* Attempt to push the neighboring cell on the previous row */
        if ((--pos.r >= 0) && (b[pos.r])[pos.c] == 'O')
            StackPush(stack, &pos);
    }
}

/***********************************************************************/
/* Given a 2D board containing 'X' and 'O' (the letter O), capture all */
/* regions surrounded by 'X'.                                          */
/*                                                                     */
/* A region is captured by flipping all 'O's into 'X's in that         */
/* surrounded region.                                                  */
/*                                                                     */
/* For example,                                                        */
/* X X X X                                                             */
/* X O O X                                                             */
/* X X O X                                                             */
/* X O X X                                                             */
/* After running your function, the board should be:                   */
/*                                                                     */
/* X X X X                                                             */
/* X X X X                                                             */
/* X X X X                                                             */
/* X O X X                                                             */
/***********************************************************************/
void solve(char** b, int bRSz, int bCSz)
{
    int i, j;
    void *stack;

    /* Allocate stack  */
    if ((stack = StackAlloc(bRSz * bCSz, sizeof(struct ch_pos))) == NULL)
        return;

    /* Now run a boundary scan to figure out all the accessible 'O'
       cells. First scan top and bottom rows. */
    for (j = 0; j < bCSz; ++j) {
        ResetO(b, bRSz, bCSz, 0, j, stack);
        ResetO(b, bRSz, bCSz, bRSz - 1, j, stack);
    }

    /* Scan first and last column. */
    for (j = 1; j < bRSz - 1; ++j) {
        ResetO(b, bRSz, bCSz, j, 0, stack);
        ResetO(b, bRSz, bCSz, j, bCSz - 1, stack);
    }

    /* Revert 'T's to Os and make remaining 'O's as 'X's. */
    for (i = 0; i < bRSz; ++i)
        for (j = 0; j < bCSz; ++j)
            (b[i])[j] = (b[i])[j] == 'T' ? 'O' : 'X'; // Ts revert to Os
    StackFree(stack); //free
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char a1[] = {'X', 'X', 'X', 'X', 0};
    char a2[] = {'X', 'O', 'O', 'X', 0};
    char a3[] = {'X', 'X', 'O', 'X', 0};
    char a4[] = {'X', 'O', 'X', 'X', 0};
    char *a[] = {a1, a2, a3, a4};
    #elif 0
    char a1[] = "XOX";
    char a2[] = "OXO";
    char a3[] = "XOX";
    char *a[] = {a1, a2, a3};
    #elif 0
    char a1[] = "XOXOXO";
    char a2[] = "OXOXOX";
    char a3[] = "XOXOXO";
    char a4[] = "OXOXOX";
    char *a[] = {a1, a2, a3, a4};
    #elif 0
    char a1[] = "OXXOX";
    char a2[] = "XOOXO";
    char a3[] = "XOXOX";
    char a4[] = "OXOOO";
    char a5[] = "XXOXO";
    char *a[] = {a1, a2, a3, a4, a5};
    #elif 1
    char a1[] = "O";
    char *a[] = {a1};
    #endif
    int r = sizeof(a) / sizeof(char *), i;
    int c = sizeof(a1) / sizeof(char) - 1;

    printf("Original Array :\n");
    for (i = 0; i < r; ++i)
        printf("%s \n", a[i]);

    /* Solve the problem */
    solve(a, r, c);

    printf("Solved Array :\n");
    for (i = 0; i < r; ++i)
        printf("%s \n", a[i]);
    return 0;
}
