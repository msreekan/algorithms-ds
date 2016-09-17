/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/stack.h"
#include "../Utils/btree.h"

/****************************************/
/* Macros & Data Structures             */
/****************************************/
#define MAX_TREE_NODES 8192

/***********************************************************************/
/* Given a binary tree, return the inorder traversal of its node values*/
/*                                                                     */
/***********************************************************************/
int *inorderTraversal(struct TreeNode* root, int *returnSize)
{
    struct TreeNode *r = root, *br = NULL;
    void *s = NULL;
    int *arr = NULL;
    int cnt = 0;

    /* Validate */
    *returnSize= 0;
    if (!r)
        goto __exit;

    /* Allocate stack */
    s = StackAlloc(MAX_TREE_NODES, sizeof(struct TreeNode *));
    if (!s)
        goto __exit;

    /* Allocate the return array */
    arr = malloc(sizeof(int) * MAX_TREE_NODES);
    if (!arr)
        goto __exit;

    /* Loop while there are nodes to be parsed */
    while (r || br)
    {
        /* Two states to inorder traversal :
           1. When 'r' is not NULL, then traverse left sub-tree
           2. When 'br' is valid, then backtrack. */

        /* If r is not NULL, then move to left sub-tree. */
        if (r)
        {
            /* Move left ? */
            if (r->left)
            {
                if (StackPush(s, &r)) // save for backtracking
                    goto __exit;
                r = r->left;
            }

            /* Else either move right or start backtracking */
            else
            {
                arr[cnt++] = r->val; // save value
                if (r->right) // move right
                    r = r->right;
                else // Else start backtracking.
                {
                    r = NULL;
                    br = !StackPop(s, &br) ? br : NULL;
                }
            }

        }

        /* Else backtrack */
        else if (br)
        {
            arr[cnt++] = br->val; // save

            /* If there is a right sub-tree, then stop backtracking */
            if (br->right)
                r = br->right;
            else // Else backtrack
                br = !StackPop(s, &br) ? br : NULL;
        }
    }

    /* Set the return size */
    *returnSize = cnt;

__exit:
    if (*returnSize == 0 && arr) {
        free(arr);
        arr = NULL;
    }
    if (s) StackFree(s);

    /* Return array */
    return arr;
}

/***********************************************************************/
/* prn_array: Print array                                              */
/*                                                                     */
/***********************************************************************/
void prn_array(int *a, int len)
{
    int i;
    for (i = 0; i < len - 1; ++i)
        printf("%d, ", a[i]);
    printf("%d\n", a[i]);
}
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1,2,3,4,5,6,9,10,20};
    int len = sizeof(a) / sizeof(int), ret;
    int *arr;
    struct TreeNode *root;

    root = CreateBtree(a, 0, len - 1);
    InorderBtree(root);
    printf("\n");
    arr = inorderTraversal(root, &ret);
    prn_array(arr, ret);
    free(arr);
    FreeBtree(root);
    return 0;
}

