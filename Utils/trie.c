/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <stdbool.h>

/****************************************/
/* Macros                               */
/****************************************/
#define DEFAULT_CLEN   53
#define INT_MAX        0x7FFFFFFF
#define TRIE_CHILDREN  53 // upper/lower case + NULL termination

/****************************************/
/* Data structures                      */
/****************************************/
/*
** Trie Node
*/
struct TrieNode
{
    struct TrieNode **carr; // pointers to children
    struct TrieNode *next; // horizontal links
    int count;             // count > 1 for a word
    int index;             // index of this word
};

/*
** Trie Handle
*/
struct TrieHandle
{
    struct TrieNode *root;
    int clen;   // number of children
    int gindex; // global index for strings
    int (*cToIndex)(char c);
};

/***********************************************************************/
/* CToIndex: Default character to index map                            */
/*                                                                     */
/***********************************************************************/
static int CToIndex(char c)
{
    /* If it's a NULL character, then return 0 offset */
    if (!c) return 0;

    /* Else if it's upper case, then return offset 1 - 27 */
    else if (c >= 'A' && c <= 'Z')
        return 1 + c - 'A';

    /* Else if it's lower case, then return offset 28 - 56 */
    else if (c >= 'a' && c <= 'z')
        return 27 + c - 'a';
    return -1; // failure
}

/***********************************************************************/
/* AddStr: Add string to the tree                                      */
/*                                                                     */
/***********************************************************************/
int AddStr(struct TrieHandle *handle, struct TrieNode *n, char *str)
{
    int offset = handle->cToIndex(*str);

    /* If the node at the offset is not present, then allocate the same*/
    if (n->carr[offset] == NULL) {
        struct TrieNode *t;
        /* Allocate the node */
        t = calloc(sizeof(struct TrieNode) + (handle->clen
                   * sizeof(struct TrieNode *)), sizeof(char));
        if (!t) return -1;

        /* Initialize the pointer array */
        t->carr = (struct TrieNode **)(t + 1);
        n->carr[offset] = t; // assign the memory to the tree
    }

    /* If it's the terminating character, then we are done. */
    if (*str == '\0') {
        n->count++; // increment the count at this location
        if (handle->gindex < INT_MAX) // maxed out
            n->index = (handle->gindex)++;
        return 0;
    }

    /* Else continue the DFS parsing */
    return AddStr(handle, n->carr[offset], str + 1);
}

/***********************************************************************/
/* SearchLenStr: Search for a string of specific length                */
/*                                                                     */
/***********************************************************************/
static struct TrieNode *SearchLenStr(struct TrieHandle *handle,
                                     struct TrieNode *n, char *str,
                                     int len)
{
    int offset = handle->cToIndex(*str);

    /* If the node at the offset is not present, then return string not
    present */
    if (!n->carr[offset])
        return NULL;

    /* Else if it's end of string , return the node */
    else if (len == 1)
        return n->carr[offset];

    /* Else continue the DFS */
    return SearchLenStr(handle, n->carr[offset], str + 1, len - 1);
}

/***********************************************************************/
/* FreeNodes: Free the nodes                                           */
/*                                                                     */
/***********************************************************************/
static void FreeNodes(int clen, struct TrieNode *n)
{
    int i;

    /* Validate the node */
    if (!n) return;

    /* Free all the children */
    for (i = 0; i < clen; ++i)
        FreeNodes(clen, n->carr[i]);
    free(n);
}
/***********************************************************************/
/* InitTrie: Create Trie data structure                                */
/*                                                                     */
/***********************************************************************/
void *InitTrie(void)
{
    struct TrieHandle *handle = NULL;

    /* Allocate and initialize the handle */
    if ((handle = malloc(sizeof(struct TrieHandle))))
    {
        handle->clen = TRIE_CHILDREN;
        handle->cToIndex = CToIndex;
        handle->gindex = 0;

        /* Allocate the root */
        handle->root = calloc(sizeof(struct TrieNode) + (handle->clen *
                              sizeof(struct TrieNode *)), sizeof(char));
        if (!handle->root) {
            free(handle);
            return NULL;
        }
        /* initialize the root */
        handle->root->carr = (struct TrieNode **)(handle->root + 1);
    }
    /* Return the handle */
    return handle;
}

/***********************************************************************/
/* FreeTrie: Free trie data structure                                  */
/*                                                                     */
/***********************************************************************/
void FreeTrie(void *handle)
{
    struct TrieHandle *h = handle;

    /* Validate the handle */
    if (!h) return;

    /* Free the nodes */
    FreeNodes(h->clen, h->root);
    free(handle);
}

/***********************************************************************/
/* AddToTrie: Add string to trie                                       */
/*                                                                     */
/***********************************************************************/
int AddToTrie(void *handle, char *str)
{
    struct TrieHandle *h = handle;

    /* Validate */
    if (!handle || !str) return -1;

    /* Recursively add the string to the tree */
    return AddStr(handle, h->root, str);
}

/***********************************************************************/
/* SearchLenTrie: Search for a string of specific length               */
/*                                                                     */
/***********************************************************************/
void *SearchLenTrie(void *handle, void *n, char *str, int len,
                    int *status)
{
    struct TrieHandle *h = handle;
    struct TrieNode *node = n;


    /* Validate the parameters */
    if (!handle || !str || len <= 0 || !status)
        return NULL;

    /* If the input starting node is NULL, then set it to root */
    if (!node) node = h->root;

    /* Do a DFS on the tree */
    *status = -1;
    if ((node = SearchLenStr(h, node, str, len)) && node->count > 0)
        *status = node->index;// if found, set status to true
    return node; // return the next node or NULL;
}

/***********************************************************************/
/* DeleteLenTrie: Delete a string of specific length                   */
/*                                                                     */
/***********************************************************************/
int DeleteLenTrie(void *handle, void *n, char *str, int len)
{
    struct TrieHandle *h = handle;
    struct TrieNode *node = n;

    /* Validate the parameters */
    if (!handle || !str || len < 0 )
        return -1;

    /* If the input starting node is NULL, then set it to root */
    if (!node) node = h->root;

    /* If there is more than one character, then search the tree */
    if (len > 0)
        node = SearchLenStr(h, node, str, len);

    /* If a node is found and it's valid, then decrement counter */
    if (node && node->count > 0) {
        node->count--;
        return 0;
    }

    /* Return failure */
    return -1;
}

/***********************************************************************/
/* UndoDelLenTrie: Undo the delete of a string of specific length      */
/*                                                                     */
/***********************************************************************/
int UndoDelLenTrie(void *handle, void *n, char *str, int len)
{
    struct TrieHandle *h = handle;
    struct TrieNode *node = n;

    /* Validate the parameters */
    if (!handle || !str || len < 0)
        return -1;

    /* If the input starting node is NULL, then set it to root */
    if (!node) node = h->root;

    /* If there is more than one character, then search the tree */
    if (len > 0)
        node = SearchLenStr(h, n, str, len);

    /* If a node is found and it's valid, then increment counter */
    if (node) {
        node->count++;
        return 0;
    }

    /* Return failure */
    return -1;
}
