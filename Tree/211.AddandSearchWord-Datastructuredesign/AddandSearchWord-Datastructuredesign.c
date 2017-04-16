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

/**********************************/
/* Macros                         */
/**********************************/
#define MAX_CHILDREN      26
#define ASCII_TO_INDEX(c) ((c) - 97)
#define ASSERT(x)         if (!(x)) exit(-1);

/* Simple allocator configuration. */
#define MAX_BLOCK_COUNT 512
#define ALLOC_BLOCK_SZ  128

/**********************************/
/* Trie Data Structure            */
/**********************************/
typedef struct
{
    void *c[MAX_CHILDREN];
    int count; /* > 0 marks presence of the words. */
    void *salloc;
} WordDictionary;

/***********************************************************************/
/* Design a data structure that supports the following two operations: */
/* void addWord(word)                                                  */
/* bool search(word)                                                   */
/* search(word) can search a literal word or a regular expression      */
/* string containing only letters a-z or .. A . means it can represent */
/* any one letter.                                                     */
/* For example:                                                        */
/* addWord("bad")                                                      */
/* addWord("dad")                                                      */
/* addWord("mad")                                                      */
/* search("pad") -> false                                              */
/* search("bad") -> true                                               */
/* search(".ad") -> true                                               */
/* search("b..") -> true                                               */
/* Note:                                                               */
/* You may assume that all words are consist of lowercase letters a-z. */
/***********************************************************************/

/***********************************************************************/
/* wordDictionaryCreate: Create dictionary!                            */
/*                                                                     */
/***********************************************************************/
WordDictionary* wordDictionaryCreate()
{
    void *salloc;
    WordDictionary *node;

    /* Initialize the simple allocator. */
    if (!(salloc = InitSAlloc(ALLOC_BLOCK_SZ * sizeof(WordDictionary),
                              MAX_BLOCK_COUNT)))
        return NULL;

    /* Allocate the node. */
    if (!(node = GetSAlloc(salloc, sizeof(WordDictionary))))
    {
        FreeSAlloc(salloc);
        return NULL;
    }

    /* Reset the node, assign the handle and return. */
    memset(node, 0, sizeof(WordDictionary));
    node->salloc = salloc;
    return node;
}

/***********************************************************************/
/* wordDictionaryAddWord: Add word to dictionary!                      */
/*                                                                     */
/***********************************************************************/
void wordDictionaryAddWord(WordDictionary* obj, char* word)
{
    /* If the parameters are invalid then return. */
    if (!word || !obj)
        return;

    /* If it's the end of the word, then increment the count. */
    if (!*word) {
        obj->count++;
        return;
    }

    ASSERT(ASCII_TO_INDEX(*word) < MAX_CHILDREN);

    /* if space needs to be allocated, then do the same. */
    if (!obj->c[ASCII_TO_INDEX(*word)])
    {
        if (!(obj->c[ASCII_TO_INDEX(*word)] = GetSAlloc(obj->salloc,
            sizeof(WordDictionary))))
            return;
        memset(obj->c[ASCII_TO_INDEX(*word)], 0, sizeof(WordDictionary));
        ((WordDictionary *)obj->c[ASCII_TO_INDEX(*word)])->salloc = obj->salloc;
    }

    /* Recursively continue the insertion. */
    wordDictionaryAddWord(obj->c[ASCII_TO_INDEX(*word)], word + 1);
}

/***********************************************************************/
/* wordDictionarySearch: Add word to dictionary!                      */
/*                                                                     */
/***********************************************************************/
bool wordDictionarySearch(WordDictionary* obj, char* word)
{
    int i;

    ASSERT(ASCII_TO_INDEX(*word) < MAX_CHILDREN);
    /* If the parameters are invalid, or if it's the end of the word,
        and it's not present. Or if there is a mismatch, then return. */
    if (!word || !obj || ((!*word) && !obj->count) ||
        ((*word) && (*word != '.') &&
         !obj->c[ASCII_TO_INDEX(*word)]))
        return false;

    /* If the word is found, then return. */
    if (!*word && obj->count)
        return true;

    /* If the character is present, then continue the search. */
    else if (*word && *word != '.' && obj->c[ASCII_TO_INDEX(*word)])
        return wordDictionarySearch(obj->c[ASCII_TO_INDEX(*word)],
                                    word + 1);

    /* If it's a special character, then try all possible paths. */
    for (i = 0; i < MAX_CHILDREN; ++i)
        if (obj->c[i] && wordDictionarySearch(obj->c[i], word + 1))
            return true;

    /* If none of the above cases were true, then the regular expression
    failed. Return word not present. */
    return false;
}

/***********************************************************************/
/* wordDictionaryFree: Free dictionary!                                */
/*                                                                     */
/***********************************************************************/
void wordDictionaryFree(WordDictionary* obj)
{
    /* Return if the object is NULL. */
    if (!obj) return;

    /* Free the Allocator. */
    FreeSAlloc(obj->salloc);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *words[] = {"dio", "enslaved", "deathangel", "entombed"};
    char *swords[] = {"mastodon", "judas Priest", "overkill", "entombed",
                      "ensl.ved", "deathangels", "dios","dio."};
    int res[] = {false, false, false, true, true, false, false, false};
    WordDictionary *h;
    unsigned int i ;

    /* Create dictionary. */
    h = wordDictionaryCreate();
    for (i = 0; i < sizeof(words) / sizeof(char*); ++i)
        wordDictionaryAddWord(h, words[i]);

    /* Check for presence. */
    for (i = 0; i < sizeof(swords) / sizeof(char*); ++i)
        if (wordDictionarySearch(h, swords[i]) != res[i])
            printf("ERR: %s\n", swords[i]);
    wordDictionaryFree(h);
    return 0;
}
