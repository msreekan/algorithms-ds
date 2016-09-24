#include <stdio.h>
#include <stdlib.h>
#include "../Utils/stack.h"
#include "../Utils/btree.h"
#include "../Utils/generic.h"

/********************************************/
/* Macros                                   */
/********************************************/
#define MAX_DEPTH 1024
#define MAX_BREADTH 1024

/***********************************************************************/
/* PathSumGen: Generate path sums for BTree!                           */
/*                                                                     */
/***********************************************************************/
void PathSumGen(struct TreeNode* root, int psum, int sum, int *csizes,
                int *rsize, int **arr, void *stack)
{
    /* Stop once the node is invalid */
    if (!root)
        return;

    /* Push to stack, increment sum. */
    StackPush(stack, &root->val);
    psum += root->val;

    /* If this is a leaf node, then pause, reflect and save */
    if (!root->left && !root->right && psum == sum)
    {
        /* Allocate and copy */
        csizes[*rsize] = StackGet(stack);
        arr[*rsize] = malloc(sizeof(int) * csizes[*rsize]);
        if (!arr[*rsize] || StackCopy(stack, (unsigned char *)arr[*rsize]))
            return;
        (*rsize) += 1;
    }

    /* Traverse the left and right sub-trees */
    PathSumGen(root->left, psum, sum, csizes, rsize, arr, stack);
    PathSumGen(root->right, psum, sum, csizes, rsize, arr, stack);
    StackPop(stack, &root->val); // pop
}

/***********************************************************************/
/* Given a binary tree and a sum, find all root-to-leaf paths where    */
/* each path's sum equals the given sum.                               */
/***********************************************************************/
int **pathSum(struct TreeNode* root, int sum, int** columnSizes,
              int *returnSize)
{
    int **arr = NULL;
    void *stack = NULL;

    /* Allocate stack/arrays */
    if (((stack = StackAlloc(MAX_DEPTH, sizeof(int))) == NULL) ||
        ((arr = malloc(sizeof(int *) * MAX_BREADTH)) == NULL) ||
        ((*columnSizes = malloc(sizeof(int) * MAX_DEPTH)) == NULL))
        goto __exit;

    /* Reset return size, generate array and return */
    *returnSize = 0;
    PathSumGen(root, 0, sum, *columnSizes, returnSize, arr, stack);
    StackFree(stack);
    return arr;
__exit:
    if (stack)
        StackFree(stack);
    if (arr)
        free(arr);
    if (*columnSizes)
        free(*columnSizes);
    return NULL;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {8, 6, 3, 1, 9, 15, 7};
    int len = sizeof(a) / sizeof(int), sum = 15, ret, i;
    struct TreeNode *root;
    int *csizes;
    int **arr;

    root = CreateBtree(a, 0, len - 1);
    printf("Inorder of the tree \n");
    InorderBtree(root);
    printf("\n");

    printf("Path sums: %d:\n", sum);
    arr = pathSum(root, sum, &csizes, &ret);
    for (i = 0; i < ret; ++i)
    {
        PrintArray(arr[i], csizes[i]);
        printf("\n");
        free(arr[i]);
    }
    FreeBtree(root);
    free(arr);
    free(csizes);
    return 0;
}
