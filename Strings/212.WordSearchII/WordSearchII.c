/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Utils/stack.h"
#include "../Utils/sallocator.h"

/***********************************/
/* Macros.                         */
/***********************************/
#define MAX_CHILDREN        26
#define ASCII_TO_OFFSET(c) ((c) - 97)

/* Simple Allocator Configuration. */
#define ALLOC_BLOCK_SZ     128
#define MAX_BLOCK_COUNT    512

/***********************************/
/* Trie Data Structure.            */
/***********************************/
typedef struct
{
    void *child[MAX_CHILDREN];
    int count; /* > 0 for a word ending here. */
    void *salloc;
} Trie;

/***********************************************************************/
/* Implement a trie with insert, search, and startsWith methods.       */
/* Note:                                                               */
/* You may assume that all inputs are consist of lowercase letters a-z.*/
/* trieCreate: Create the Trie!                                        */
/*                                                                     */
/***********************************************************************/
Trie* trieCreate()
{
    void *salloc;
    Trie *node;

    /* Initialize the simple allocator. */
    if (!(salloc = InitSAlloc(ALLOC_BLOCK_SZ * sizeof(Trie),
                              MAX_BLOCK_COUNT)))
        return NULL;

    /* Allocate the node. */
    if (!(node = GetSAlloc(salloc, sizeof(Trie))))
    {
        FreeSAlloc(salloc);
        return NULL;
    }

    /* Reset the node, assign the handle and return. */
    memset(node, 0, sizeof(Trie));
    node->salloc = salloc;
    return node;
}

/***********************************************************************/
/* trieCreate: Create the Trie!                                        */
/*                                                                     */
/***********************************************************************/
void trieInsert(Trie* obj, char* word, int len)
{
    /* If pointers are invalid, return. */
    if (!obj || !word)
        return;

    /* If it's a NULL character, then increment count and return. */
    if (!len) {
        obj->count++;
        return;
    }

    /* If the word is not already present, then allocate. */
    if (!obj->child[ASCII_TO_OFFSET(*word)])
    {
        if (!(obj->child[ASCII_TO_OFFSET(*word)] =
              GetSAlloc(obj->salloc, sizeof(Trie))))
            return;

        /* Reset and assign the handle. */
        memset(obj->child[ASCII_TO_OFFSET(*word)], 0, sizeof(Trie));
        ((Trie *)obj->child[ASCII_TO_OFFSET(*word)])->salloc = obj->salloc;
    }

    /* Move to the next character. */
    trieInsert(obj->child[ASCII_TO_OFFSET(*word)], word + 1, len - 1);
}

/***********************************************************************/
/* trieSearch: Search the Trie!                                        */
/*                                                                     */
/***********************************************************************/
bool trieSearch(Trie* obj, char* word)
{
    /* Return false in following cases:
       1. If pointers are invalid.
       2. If it's the last character of the word and it's not present.
       3. If the present character is not present and it's not the end
          of a dictionary word.
       */
    if (!obj || !word || ((!*word) && !obj->count) ||
        ((*word) && !obj->child[ASCII_TO_OFFSET(*word)] && !obj->count))
        return false;

    /* We have a hit. */
    if (((!*word) && obj->count) ||
        ((*word) && !obj->child[ASCII_TO_OFFSET(*word)] && obj->count))
        return true;

    /* Move to the next character. */
    return trieSearch(obj->child[ASCII_TO_OFFSET(*word)], word + 1);
}

/***********************************************************************/
/* trieFree: Free the Trie!                                            */
/*                                                                     */
/***********************************************************************/
void trieFree(Trie* obj)
{
    /* Return if the node is invalid. Else free the simple allocator. */
    if (!obj) return;
    FreeSAlloc(obj->salloc);
}

/***********************************************************************/
/* WordSearch: Search for a word in the matrix!                        */
/*                                                                     */
/***********************************************************************/
int WordSearch(char **mat, int r, int c, int rsz, int csz, char *word,
               char *map, int woff, int *loff)
{
    int ret = 0;

    /* If it's the end of the word, then return true. */
    if (!word[woff])
        return true;

    /* Validate the row and column. If the cell was already visited or
       if the characters do not match, then return. */
    if (r < 0 || c < 0 || r >= rsz || c >= csz || map[r * csz + c] ||
        (mat[r])[c] != word[woff])
    {
        *loff = (*loff < woff) ? woff : *loff;
        return false;
    }

    /* Set the map. */
    map[r * csz + c] = 1;

    /* Search the neighbors for a match. */
    ret = WordSearch(mat, r + 1, c, rsz, csz, word, map, woff + 1,
                     loff);
    ret = (ret == false) ? WordSearch(mat, r - 1, c, rsz, csz, word,
                           map, woff + 1, loff) : ret;
    ret = (ret == false) ? WordSearch(mat, r, c + 1, rsz, csz, word,
                           map, woff + 1, loff) : ret;
    ret = (ret == false) ? WordSearch(mat, r, c - 1, rsz, csz, word,
                           map, woff + 1, loff) : ret;
    /* Reset the map. */
    map[r * csz + c] = 0;

    /* Return the status. */
    return ret;
}


/***********************************************************************/
/* Given a 2D board and a list of words from the dictionary, find all  */
/* words in the board.                                                 */
/* Each word must be constructed from letters of sequentially adjacent */
/* cell, where "adjacent" cells are those horizontally or vertically   */
/* neighboring. The same letter cell may not be used more than once in */
/* a word.                                                             */
/* For example,                                                        */
/* Given words = ["oath","pea","eat","rain"] and board =               */
/* [                                                                   */
/*  ['o','a','a','n'],                                                 */
/*  ['e','t','a','e'],                                                 */
/*  ['i','h','k','r'],                                                 */
/*  ['i','f','l','v']                                                  */
/* ]                                                                   */
/* Return ["eat","oath"].                                              */
/*                                                                     */
/* Note:                                                               */
/* You may assume that all inputs are consist of lowercase letters     */
/* a-z.                                                                */
/***********************************************************************/
char** findWords(char** board, int bRowSz, int bColSz, char** words,
                 int wSz, int* returnSize)
{
    char *map;
    char **list;
    int i, r, c, ret, loff;
    Trie *trie;

    /* Validate the parameters. */
    if (!board || bRowSz < 1 || bColSz < 1 || !words || !returnSize)
        return NULL;
    *returnSize = 0;

    /* Allocate memory to store the list. */
    list = malloc(sizeof(char *) * wSz);
    if (!list)
        return NULL;

    /* Create a Trie. */
    trie = trieCreate();

    /* Allocate map for processing .*/
    map = calloc(bRowSz * bColSz, sizeof(char));
    if (!map) return list;

    /* Loop through the word list looking for a match in the matrix. */
    for (i = 0; i < wSz; ++i)
    {
        int j;

        /* Avoid words with prefix which will fail. */
        if (trieSearch(trie, words[i]))
            continue;

        /* Avoid duplicate words. */
        for (j = 0; j < *returnSize; ++j)
            if (!strcmp(list[j], words[i]))
                break;
        /* Avoid duplicates. */
        if (*returnSize && j < *returnSize)
            continue;

        /* Go through all the rows looking for a match. */
        ret = 0; // reset status
        loff = 0;
        for (r = 0; r < bRowSz; ++r) {
            for (c = 0; c < bColSz; ++c) {
                ret = WordSearch(board, r, c, bRowSz, bColSz, words[i], map,
                                 0, &loff);
                if (ret) {
                    list[*returnSize] = words[i];
                    (*returnSize) += 1;
                    break;
                }
            }
            if (ret)
                break;
        }
        if (!ret)
            trieInsert(trie, words[i], loff + 1);
    }

    /* Free the map. */
    free(map);
    trieFree(trie);

    /* Return the list. */
    return list;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 1
    char c1[] = {'o','a','a','n', 0};
    char c2[] = {'e','t','a','e', 0};
    char c3[] = {'i','h','k','r', 0};
    char c4[] = {'i','f','l','v', 0};
    char *board[] = {c1, c2, c3, c4};
    char *words[] = {"oath","pea","eat","rain"};
    #else
    char c1[] = "a";
    char *board[] = {c1};
    char *words[] = {"ab"};
    #endif
    char **list;
    int row = sizeof(board) / sizeof(char *), cols = sizeof(c1) - 1, i;
    int wsz = sizeof(words) / sizeof(char *), retsz;

    list = findWords(board, row, cols, words, wsz, &retsz);
    for (i = 0; i < retsz; ++i)
        printf("%d : %s \n", i, list[i]);
    return 0;
}
