/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/btree.h"

/**********************************/
/* Macros.                        */
/**********************************/
#define MAX_BPATH       1024
#define MAX_ENTRIES     1024
#define INT_TO_ASCII(x) ((x) + 48)
#define SWAP_CHAR(x, y) {\
                          char c;\
                          c = x;\
                          x = y;\
                          y = c;\
                        }


/***********************************************************************/
/* itoa: Integer to ASCII!                                             */
/*                                                                     */
/***********************************************************************/
int t_itoa(char *buf, int val)
{
    int len = 0, j, i, soff = 0;
    unsigned tval;

    /* Get the absolute value.  */
    tval = (val < 0) ? -val : val;

    /* If needed, add the negative. */
    if (val < 0)
    {
        buf[len++] = '-';
        soff = 1;
    }

    /* Loop adding the integers. */
    for (;tval; tval /= 10)
        buf[len++] = INT_TO_ASCII(tval % 10);

    /* Reverse the order. */
    for (j = len - 1, i = soff; j > i; ++i, --j)
        SWAP_CHAR(buf[j], buf[i]);

    /* Return the length. */
    return len;
}

/***********************************************************************/
/* get_paths: Get all the paths!                                       */
/*                                                                     */
/***********************************************************************/
void get_paths(struct TreeNode* root, int* rsz, char **carr, char *parr,
               int off)
{
    /* Return if invalid. */
    if (!root)
        return;

    /* Ensure we do not exceed the limit. */
    if (off == MAX_BPATH)
        return;

    /* If it's not the first node, then add the arrow. */
    if (off)
    {
        parr[off++] = '-';
        parr[off++] = '>';
    }

    /* Add the value. */
    off += t_itoa(&parr[off], root->val);

    /* If we have reached a leaf node, then save the stack. */
    if (!root->right && !root->left)
    {
        if (*rsz == MAX_ENTRIES)
            return;
        carr[*rsz] = malloc(sizeof(char) * (off + 1));
        if (!carr[*rsz])
            return;
        memcpy(carr[*rsz], parr, off);
        (carr[*rsz])[off] = 0;
        ++*rsz;
        return;
    }

    /* Continue down the path. */
    get_paths(root->left, rsz, carr, parr, off);
    get_paths(root->right, rsz, carr, parr, off);
}


/***********************************************************************/
/* Given a binary tree, return all root-to-leaf paths.                 */
/***********************************************************************/
char** binaryTreePaths(struct TreeNode* root, int* rsz)
{
    char **carr;
    char *parr;

    /* Validate the paramters. */
    if (!root || !rsz)
        return NULL;
    *rsz = 0;

    /* Allocate the memeory. */
    carr = malloc(sizeof(char **) * MAX_ENTRIES);
    if (!carr)
        return NULL;
    parr = malloc(sizeof(char *) * MAX_BPATH);
    if (!parr) {
        free(carr);
        return NULL;
    }

    /* Get the paths. */
    get_paths(root, rsz, carr, parr, 0);
    free(parr);
    return carr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{

    return 0;
}
