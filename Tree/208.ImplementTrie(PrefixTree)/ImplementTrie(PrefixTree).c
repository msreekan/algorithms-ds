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
#define MAX_ALLOCATION_BLOCKS 1024
#define ALLOCATION_BLK_SIZE   64

/***********************************/
/* Data Structures.                */
/***********************************/
/* Trie Node. */
struct TrieNode
{
    struct TrieNode *child[MAX_CHILDREN];
    int count; /* > 0 for a word ending here. */
};

/* Trie Handle. */
typedef struct
{
    struct TrieNode *node;
    void *salloc; /* Simple allocator handle. */
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
    Trie *trie = malloc(sizeof(Trie));

    /* If the handle was not allocated, then return error. */
    if (!trie)
        goto __Err_exit;

    /* Initialize the simple allocator. */
    if (!(trie->salloc = InitSAlloc(ALLOCATION_BLK_SIZE *
                                    sizeof(struct TrieNode),
                                    MAX_ALLOCATION_BLOCKS)))
        goto __Err_exit;

    /* Allocate the Trie node. */
    if (!(trie->node = GetSAlloc(trie->salloc ,
                                 sizeof(struct TrieNode))))
        goto __Err_exit;

    /* Memset the memeory, assign the handle and return. */
    memset(trie->node, 0, sizeof(struct TrieNode));
    return trie;
__Err_exit:
    /* Wind up the allocations. */
    if (trie) {
        if (trie->salloc)
            FreeSAlloc(trie->salloc);
        free(trie);
    }
    return NULL;
}

/***********************************************************************/
/* InsertHelper: Add words into the Trie!                              */
/*                                                                     */
/***********************************************************************/
void InsertHelper(struct TrieNode* obj, char* word, void *salloc)
{
    /* If pointers are invalid, return. */
    if (!obj || !word)
        return;

    /* If it's a NULL character, then increment count and return. */
    if (!*word) {
        obj->count++;
        return;
    }

    /* If the word is not already present, then allocate. */
    if (!obj->child[ASCII_TO_OFFSET(*word)]) {
        if (!(obj->child[ASCII_TO_OFFSET(*word)] = GetSAlloc(salloc,
                                          sizeof(struct TrieNode))))
            return;

        /* Memset the memory, assign the handle. */
        memset(obj->child[ASCII_TO_OFFSET(*word)], 0,
               sizeof(struct TrieNode));
    }

    /* Move to the next character. */
    InsertHelper(obj->child[ASCII_TO_OFFSET(*word)], word + 1, salloc);
}
/***********************************************************************/
/* trieInsert: Insert words into the Trie!                             */
/*                                                                     */
/***********************************************************************/
void trieInsert(Trie* obj, char* word)
{
    InsertHelper(obj->node, word, obj->salloc);
}

/***********************************************************************/
/* SearchHelper: Search the Trie!                                      */
/*                                                                     */
/***********************************************************************/
bool SearchHelper(struct TrieNode* obj, char* word)
{
    /* Return false in following cases:
       1. If pointers are invalid.
       2. If it's the last character of the word and it's not present.
       3. If the present character is not present.
       */
    if (!obj || !word || ((!*word) && !obj->count) ||
         ((*word) && !obj->child[ASCII_TO_OFFSET(*word)]))
        return false;

    /* We have a hit. */
    if ((!*word) && obj->count)
        return true;

    /* Move to the next character. */
    return SearchHelper(obj->child[ASCII_TO_OFFSET(*word)], word + 1);
}

/***********************************************************************/
/* trieSearch: Search the Trie!                                        */
/*                                                                     */
/***********************************************************************/
bool trieSearch(Trie* obj, char* word)
{
    return SearchHelper(obj->node, word);
}

/***********************************************************************/
/* StartsWithHelper: Search the Trie!                                  */
/*                                                                     */
/***********************************************************************/
bool StartsWithHelper(struct TrieNode* obj, char* prefix)
{
    /* Return false in following cases:
       1. If pointers are invalid.
       2. If the present character is not present.
       */
    if (!obj || !prefix ||
        ((*prefix) && !obj->child[ASCII_TO_OFFSET(*prefix)]))
        return false;

    /* We have a hit. */
    if (!*prefix)
        return true;

    /* Move to the next character. */
    return StartsWithHelper(obj->child[ASCII_TO_OFFSET(*prefix)],
                            prefix + 1);
}

/***********************************************************************/
/* trieStartsWith: Search the Trie!                                    */
/*                                                                     */
/***********************************************************************/
bool trieStartsWith(Trie* obj, char* prefix)
{
    return StartsWithHelper(obj->node, prefix);
}

/***********************************************************************/
/* trieFree: Free the Trie!                                            */
/*                                                                     */
/***********************************************************************/
void trieFree(Trie* obj)
{
    FreeSAlloc(obj->salloc);
    free(obj);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *wlist[] = {"darkthrone", "enslaved", "ihsahn"};
    char *wsearch[] = {"enslaved", "amon amarth"};
    char *wprefix[] = {"dark", "throne"};
    Trie *t;

    /* Initialize trie. */
    t = trieCreate();
    trieInsert(t, wlist[0]);
    trieInsert(t, wlist[1]);

    /* Search. */
    if (!trieSearch(t, wsearch[0]))
        exit(-1);
    if (trieSearch(t, wsearch[1]))
        exit(-1);

    /* Search. */
    if (!trieStartsWith(t, wprefix[0]))
        exit(-1);
    if(trieStartsWith(t, wprefix[1]))
        exit(-1);

    /* Free Trie. */
    trieFree(t);
    return 0;
}
