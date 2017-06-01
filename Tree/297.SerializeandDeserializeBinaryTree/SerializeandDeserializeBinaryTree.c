/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"

/***************************************/
/* Macros                              */
/***************************************/
#define MAX_NODES (8192 * 2)

/***************************************/
/* Data Structures                     */
/***************************************/
typedef struct
{
    int val;   // Value
    int left;  // Left child offset
    int right; // Right child offset
} TNode;

/***********************************************************************/
/* GenSerial: Recursively generate serial array!                       */
/*                                                                     */
/***********************************************************************/
void GenSerial(struct TreeNode *node, TNode *tnode, TNode *arr,
               int *aindex)
{
    /* Validate. */
    if (!node || !tnode)
        return;

    /* Serialize this sub-structure. Assign LEFT and RIGHT sub-nodes
      only if there is space. */
    tnode->val = node->val;
    tnode->left = node->left && (*aindex < MAX_NODES - 1) ?
                  ++*aindex : 0;
    tnode->right = node->right && (*aindex < MAX_NODES - 1) ?
                  ++*aindex : 0;

    /* Recursively implement the above operation for the children. */
    GenSerial(node->left, tnode->left ? &arr[tnode->left] : NULL, arr,
              aindex);
    GenSerial(node->right,tnode->right ? &arr[tnode->right] : NULL, arr,
              aindex);
}

/***********************************************************************/
/* DeSerial: Recursively transnform the serial array!                  */
/*                                                                     */
/***********************************************************************/
struct TreeNode *DeSerial(TNode *node, TNode *arr)
{
    struct TreeNode *tnode;

    /* If the node is invalid or allocation failed, return NULL. */
    if (!node || !(tnode = malloc(sizeof(struct TreeNode))))
        return NULL;

    /* Assign the values. Recursively generate the sub-trees. */
    tnode->val = node->val;
    tnode->left = DeSerial(node->left ? &arr[node->left] : NULL, arr);
    tnode->right = DeSerial(node->right ? &arr[node->right] : NULL, arr);

    /* Return the root. */
    return tnode;
}

/***********************************************************************/
/* Serialization is the process of converting a data structure or      */
/* object into a sequence of bits so that it can be stored in a file or*/
/* memory buffer, or transmitted across a network connection link to be*/
/* reconstructed later in the same or another computer environment.    */
/* Design an algorithm to serialize and deserialize a binary tree.     */
/* There is no restriction on how your serialization/deserialization   */
/* algorithm should work. You just need to ensure that a binary tree   */
/* can be serialized to a string and this string can be deserialized   */
/* to the original tree structure.                                     */
/***********************************************************************/
/***********************************************************************/
/* Encodes a tree to a single string.                                  */
/***********************************************************************/
char* serialize(struct TreeNode* root)
{
    TNode *t;
    int aindex = 0;

    /* Validate the parameter. Allocate array for serialized storage. */
    if (!root || !(t = (malloc(sizeof(TNode) * MAX_NODES))))
        return NULL;

    /* Serialize. */
    GenSerial(root, t, t, &aindex);
    return (char *)t;
}

/***********************************************************************/
/* Decodes your encoded data to tree.                                  */
/***********************************************************************/
struct TreeNode* deserialize(char* data)
{
    TNode *t = (TNode *)data;
    struct TreeNode *tn;

    /* Deserialize. */
    tn = DeSerial(t, t);
    free(t);
    return tn;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
