/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/btree.h"
#include "../Utils/stack.h"
#include "../Utils/generic.h"

/********************************************/
/* Macros                                   */
/********************************************/
#define MAX_NODES   1024
#define GO_RIGHT    1
#define GO_LEFT     2
#define NODE_DONE   3

/********************************************/
/* Data Structure                           */
/********************************************/
struct postt
{
    struct TreeNode *node;
    int state;
};

/***********************************************************************/
/* Given a binary tree, return the postorder traversal of its nodes'   */
/* values.                                                             */
/***********************************************************************/
int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    int *arr = NULL;
    struct TreeNode *node = root;
    void *stack = NULL;
    struct postt post_s = {NULL, 0};
    int ret = 0;

    /* Validate the allocations */
    *returnSize = 0;
    if (!root || !(arr = malloc(sizeof(int) * MAX_NODES)) ||
        !(stack = StackAlloc(MAX_NODES, sizeof(struct postt))))
        goto __exit;

    /* Traverse while stack is not empty */
    while (!StackEmpty(stack) || node)
    {
        /* Push the root to the stack */
        if (node) {
            post_s = (struct postt){node, GO_LEFT};
            StackPush(stack, &post_s);
        }
        /* Pop the stack */
        if (StackPop(stack, &post_s))
            goto __exit;
        node = post_s.node;

        /* If the state of the node is to go left or right, then do
           the same */
        if (post_s.state == GO_LEFT || post_s.state == GO_RIGHT)
        {
            /* Push the node back with the next state */
            node = post_s.state == GO_LEFT ? node->left : node->right;
            post_s.state = post_s.state == GO_LEFT ? GO_RIGHT : NODE_DONE;
            if (StackPush(stack, &post_s))
                goto __exit;
        }
        /* Else, save the node */
        else if (post_s.state == NODE_DONE) { // save the node
            arr[ret++] = node->val;
            node = NULL;
        }
    }
    *returnSize = ret;
__exit:
    if (stack) StackFree(stack);
    if (arr && !(*returnSize)) {
        free(arr);
        arr = NULL;
    }
    return arr;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int len = sizeof(a) / sizeof(int), ret;
    int *arr;
    struct TreeNode* root = CreateBtree(a, 0, len - 1);
    PostorderBtree(root);
    arr = postorderTraversal(root, &ret);
    printf("\n");
    PrintArray(arr, ret);
    free(arr);
    FreeBtree(root);
    return 0;
}
