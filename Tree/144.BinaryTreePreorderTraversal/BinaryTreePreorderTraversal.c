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
#define MAX_NODES 1024

/***********************************************************************/
/* Given a binary tree, return the postorder traversal of its nodes'   */
/* values.                                                             */
/***********************************************************************/
int* preorderTraversal(struct TreeNode* root, int* returnSize)
{
    int *arr = NULL;
    void *stack = NULL;
    struct TreeNode *node = root;
    int ret = 0;

    /* Validate */
    if (!root)
        return NULL;

    /* Allocate array and stack */
    *returnSize = 0;
    if (!(arr = malloc(sizeof(int) * MAX_NODES)) ||
        !(stack = StackAlloc(MAX_NODES, sizeof(struct TreeNode *))))
        goto __exit;

    /* Traverse as long as node is valid or stack is not empty */
    while (node)
    {
        /* Save the value */
        arr[ret++] = node->val;

        /* Push the right sub-tree to the stack */
        if ((node->right) && StackPush(stack, &node->right))
            goto __exit;

        /* Keep moving left */
        if (node->left) node = node->left;
        /* Else pop the stack */
        else if (StackPop(stack, &node))
            node = NULL;
    }
    *returnSize = ret;
__exit:
    if (!*returnSize && arr) {
            free(arr);
            arr = NULL;
    }
    if (stack) StackFree(stack);
    return arr;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(a) / sizeof(int), ret;
    int *arr;
    struct TreeNode *root = CreateBtree(a, 0, len - 1);
    PreorderBtree(root);
    printf("\n");
    arr = preorderTraversal(root, &ret);
    PrintArray(arr, len);
    free(arr);
    FreeBtree(root);
    return 0;
}
