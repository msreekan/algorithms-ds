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
#include "../Utils/sallocator.h"

/****************************************/
/* Macros                               */
/****************************************/
#define CCOUNT            4
#define SEQUENCE_LEN      10
#define MAX_BLOCK_CNT     1024
#define ALLOC_SEGMENT_CNT 64   // 64 segment/block

/****************************************/
/* Data Structure                       */
/****************************************/
struct TrieNode
{
    struct TrieNode *cptr[CCOUNT];
    int word;
};

/***********************************************************************/
/* AddToTrie: Add string to trie!                                      */
/*                                                                     */
/***********************************************************************/
struct TrieNode *AddToTrie(struct TrieNode *root, char *str, int count,
                           int *map, void *salloc)
{
    int off;

    /* If we are done, then return */
    if (!count)
        return root;

    /* Get the offset */
    off = map[*str - 'A'];

    /* If there is not child at that location, then allocate */
    if (!root->cptr[off] &&
        !(root->cptr[off] = GetSAlloc(salloc, sizeof(struct TrieNode))))
        return NULL;

    /* Continue the traversal */
    return AddToTrie(root->cptr[off], str + 1, count - 1, map, salloc);
}

/***********************************************************************/
/* All DNA is composed of a series of nucleotides abbreviated as A, C, */
/* G, and T, for example: "ACGAATTCCG". When studying DNA, it is       */
/* sometimes useful to identify repeated sequences within the DNA.     */
/*                                                                     */
/* Write a function to find all the 10-letter-long sequences           */
/* (substrings) that occur more than once in a DNA molecule.           */
/*                                                                     */
/* For example,                                                        */
/*                                                                     */
/* Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",                       */
/*                                                                     */
/* Return:                                                             */
/* ["AAAAACCCCC", "CCCCCAAAAA"].                                       */
/***********************************************************************/
char** findRepeatedDnaSequences(char* s, int* returnSize)
{
    char **str = NULL;
    void *salloc = NULL;
    char *sarr;
    struct TrieNode *root = NULL, *node;
    int len = strlen(s), i;
    unsigned char map[26];

    /* Initialize root, simple allocator and allocate output array,  */
    if (!returnSize || !(root = calloc(1, sizeof(struct TrieNode))) ||
        !(salloc = InitSAlloc(sizeof(struct TrieNode) * ALLOC_SEGMENT_CNT,
          MAX_BLOCK_CNT)) ||
        !(str = malloc(sizeof(char *) * len)))
        goto __exit;

    /* Initialize map corresponding to A, C, G, T, and return size. */
    map[0] = 0, map[2] = 1, map[6] = 2, map[19] = 3;
    *returnSize = 0;

    /* Look for sequences */
    for (i = 0; i <= len - SEQUENCE_LEN; ++i)
    {
        /* Add the word to the trie, and get the terminating node. */
        if (!(node = AddToTrie(root, &s[i], SEQUENCE_LEN, map, salloc)))
            goto __exit;

        /* If there was a previous instance of the same sequence,
        then add this to the solution. */
        if (node->word == 1)  {
            /* Validate the allocation */
            if (!(sarr = malloc(sizeof(char) * (SEQUENCE_LEN + 1))))
                goto __exit;
            /* Copy the sequence */
            strncpy(sarr, &s[i], SEQUENCE_LEN);
            sarr[SEQUENCE_LEN] = 0; // NULL terminate;
            str[*returnSize] = sarr; // add this to the solution
            (*returnSize) += 1; // increment the sequence count
        }
        node->word++; // increment the word instance count
    }
__exit:
    if (salloc)
        FreeSAlloc(salloc);
    if (root) free(root);
    return str;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char **str;
    char s[] = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTTAAAAAAAAAAA";
    int ret, i;
    str = findRepeatedDnaSequences(s, &ret);

    /* Print the repeating sequence */
    for (i = 0; i < ret; ++i){
        printf("%s \n", str[i]);
        free(str[i]);
    }
    free(str);
    return 0;
}
