/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __BTREE_H__
#define __BTREE_H__

/*
** Tree Node
*/
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
** Tree Node + Linked list
*/
struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
};

/********************************************/
/* Function Prototypes                      */
/********************************************/
struct TreeNode *CreateBtree(int *arr, int s, int e);
void FreeBtree(struct TreeNode *root);
void PreorderBtree(struct TreeNode *root);
void PostorderBtree(struct TreeNode *root);
void InorderBtree(struct TreeNode *root);
void InorderBtreeArr(struct TreeNode *root, int **arr);
void PreorderBtreeArr(struct TreeNode *root, int **arr);
void PostorderBtreeArr(struct TreeNode *root, int **arr);
void PreorderBtreeBArr(struct TreeNode *root, struct TreeNode ***arr);
struct TreeLinkNode *CreateBLTree(int *arr, int s, int e);
void InorderBLTree(struct TreeLinkNode *root);
void LevelTraversalBLtree(struct TreeLinkNode *root);
void FreeBLtree(struct TreeLinkNode *root);
#endif // __BTREE_H__
