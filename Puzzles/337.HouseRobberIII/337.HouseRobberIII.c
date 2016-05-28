/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

#define max(a, b, c) ((a) > (((b) > (c)) ? (b) : (c)) ? \
                      (a) : (((b) > (c)) ? (b) : (c)))

/***********************************************************************/
/* get_max: Recursively generate the greatest combination sum          */
/*                                                                     */
/***********************************************************************/
void get_max(struct node *root, int *sum)
{
    int tsum1[2] = {0 , 0}, tsum2[2] = {0 , 0};

    /* Leaf node */
    if (root == NULL)
    {
        sum[0] = 0;
        sum[1] = 0;
        return;
    }

    /* Get the maximum from the left and right children */
    get_max(root->left, tsum1);
    get_max(root->right, tsum2);

    /* Value of this node can be included in the sum
    only if the values of the two children are excluded
    Index 0 includes the node's value
    Index 1 does not include the node's value */
    sum[0] = tsum1[1] + root->val + tsum2[1];

    /* We need to pick the greatest among the available combinations :
    1. Values of both the children are included.
    2. Only one of the children is picked
    3. Value of both the children are excluded, this enables the parent
    to generate a combination where its own value is added to this.
    Which is not possible if only above sum[0] is provided.
    Essentially, the robber has to work on alternate levels but he also
    has the option of skipping two levels  */
    sum[1] = max (tsum1[0] + tsum2[0], tsum1[1] + tsum2[0], tsum1[0] +
                  tsum2[1]);
    sum[1] = (sum[1] > (tsum1[1] + tsum2[1])) ? sum[1] : (tsum1[1] +
                                                          tsum2[1]);
}

/***********************************************************************/
/* The thief has found himself a new place for his thievery again.     */
/* There is only one entrance to this area, called the "root." Besides */
/* the root, each house has one and only one parent house. After a     */
/* tour, the smart thief realized that "all houses in this place forms */
/* a binary tree". It will automatically contact the police if two     */
/* directly-linked houses were broken into on the same night.          */
/*                                                                     */
/* Determine the maximum amount of money the thief can rob tonight     */
/* without alerting the police.                                        */
/***********************************************************************/
int rob(struct node *root)
{
    int max[2] = {0, 0};
    get_max(root, max);
    return (max[0] > max[1]) ? max[0] : max[1];
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {1, 4, 3, 3, 5, 1};
    int len = sizeof(a) / sizeof(int);
    struct node *root = generate_tree(a, 0, len - 1);
    if (root == NULL)
        return -1;
    printf(" Max = %d :\n", rob(root));
    free_tree(root);
    return 0;
}
