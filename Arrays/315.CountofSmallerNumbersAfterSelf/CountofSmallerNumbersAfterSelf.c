/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if BST_METHOD
/*******************************/
/* BST structure               */
/*******************************/
struct bnode
{
    int val;             /* Value. */
    int ltcount;         /* Left sub-tree count. */
    struct bnode *left;  /* Left node. */
    struct bnode *right; /* Right node. */
};

/***********************************************************************/
/* CntCmaller: Count the smaller values!                               */
/*                                                                     */
/***********************************************************************/
struct bnode *CntSmaller(struct bnode *root, int val,
                         struct bnode *node, int *cnt)
{
    /* If we have reached the leaf node, then assign and return. */
    if (!root) {
        node->val = val;
        node->left = node->right = NULL;
        node->ltcount = 0;
        root = node;
    }

    /* If the value is less than the root, then go left. */
    else if (root->val >= val) {
        /* Increment the count for the left sub-tree. */
        root->ltcount++;
        root->left = CntSmaller(root->left, val, node, cnt);
    }
    else {
        /* Account for the smaller nodes. */
        *cnt += root->ltcount + 1;
        root->right = CntSmaller(root->right, val, node, cnt);
    }

    /* Return the root. */
    return root;
}

/***********************************************************************/
/* You are given an integer array nums and you have to return a new    */
/* counts array. The counts array has the property where counts[i] is  */
/* the number of smaller elements to the right of nums[i].             */
/* Example:                                                            */
/* Given nums = [5, 2, 6, 1]                                           */
/*                                                                     */
/* To the right of 5 there are 2 smaller elements (2 and 1).           */
/* To the right of 2 there is only 1 smaller element (1).              */
/* To the right of 6 there is 1 smaller element (1).                   */
/* To the right of 1 there is 0 smaller element.                       */
/* Return the array [2, 1, 1, 0].                                      */
/***********************************************************************/
int *countSmaller(int* n, int nsz, int* rsz)
{
    int *carr;
    int i;
    struct bnode *barr, *root;

    /* Validate the parameters. */
    if (!n || nsz < 1 || !rsz)
        return NULL;
    *rsz = 0;

    /* Allocate nodes. */
    if (!(carr = malloc(sizeof(int) * nsz)))
        return NULL;
    if (!(barr = malloc(sizeof(struct bnode) * nsz)))
    {
        free(carr);
        return NULL;
    }
    *rsz = nsz;

    /* Initialize the structures. */
    root = &barr[nsz - 1];
    root->val = n[nsz - 1];
    root->left = root->right = NULL;
    root->ltcount = 0;
    memset(carr, 0, nsz * sizeof(int));

    /* Count the smaller values. */
    for (i = nsz - 2; i >= 0; --i)
        CntSmaller(root, n[i], &barr[i], &carr[i]);
    /* Return the result. */
    return carr;
}
#elif O_N2
/***********************************************************************/
/* You are given an integer array nums and you have to return a new    */
/* counts array. The counts array has the property where counts[i] is  */
/* the number of smaller elements to the right of nums[i].             */
/* Example:                                                            */
/* Given nums = [5, 2, 6, 1]                                           */
/*                                                                     */
/* To the right of 5 there are 2 smaller elements (2 and 1).           */
/* To the right of 2 there is only 1 smaller element (1).              */
/* To the right of 6 there is 1 smaller element (1).                   */
/* To the right of 1 there is 0 smaller element.                       */
/* Return the array [2, 1, 1, 0].                                      */
/***********************************************************************/
int *countSmaller(int* n, int nsz, int* rsz)
{
    int *arr, *arr1;
    int i, k;

    /* Validate. */
    if (!n || nsz < 1 || !rsz)
        return NULL;
    *rsz = 0;

    /* Allocate space for merge sort. */
    if (!(arr = calloc(nsz * 2, sizeof(int))))
        return NULL;
    arr1 = &arr[nsz];
    *rsz = nsz;

    /* Scan from the end. */
    for (i = nsz - 1; i >= 0; --i)
    {
        /* Look for the first value greater than or equal to the one
        at offst i. */
        for (k = i; n[i] > arr1[k + 1] && k + 1 < nsz; ++k, arr[i]++)
            arr1[k] = arr1[k + 1]; // keep shifting elements
        arr1[k] = n[i];
    }

    /* Return the result. */
    return arr;
}
#else
/***********************************************************************/
/* MergeSort: Merge sort, count the number smaller elements!           */
/*                                                                     */
/***********************************************************************/
void MergeSort(int *marr, int *iarr, int *tarr, int s, int e, int *count)
{
    int mid = s + (e - s) / 2, i = s, j = mid + 1, k = s, lc = 0;

    /* Terminating condition. */
    if (s >= e)
        return;

    /* Merge sort both the halves. */
    MergeSort(marr, iarr, tarr, s, mid, count);
    MergeSort(marr, iarr, tarr, mid + 1, e, count);

    /* Merge the two sorted halves. */
    while (i <= mid && j <= e) {
        /* If the left subarray element is less than right, then
        merge and increment the count. */
        if (marr[iarr[j]] < marr[iarr[i]]) {
            tarr[k++] = iarr[j++];
            lc++;
        }
        else {
            tarr[k++] = iarr[i];
            count[iarr[i++]] += lc;
        }
    }

    /* Merge any remaining elements. */
    while (i <= mid) {
        tarr[k++] = iarr[i];
        count[iarr[i++]] += lc;
    }

    /* Merge any remaining elements. */
    while (j <= e)
        tarr[k++] = iarr[j++];
    /* Copy the elements back into the main array. */
    memcpy(&iarr[s], &tarr[s], (e - s + 1) * sizeof(int));
}

/***********************************************************************/
/* You are given an integer array nums and you have to return a new    */
/* counts array. The counts array has the property where counts[i] is  */
/* the number of smaller elements to the right of nums[i].             */
/* Example:                                                            */
/* Given nums = [5, 2, 6, 1]                                           */
/*                                                                     */
/* To the right of 5 there are 2 smaller elements (2 and 1).           */
/* To the right of 2 there is only 1 smaller element (1).              */
/* To the right of 6 there is 1 smaller element (1).                   */
/* To the right of 1 there is 0 smaller element.                       */
/* Return the array [2, 1, 1, 0].                                      */
/***********************************************************************/
int *countSmaller(int* n, int nsz, int* rsz)
{
    int *iarr, *tarr, *count;
    int i;

    /* Validate. */
    if (!n || nsz < 1 || !rsz)
        return NULL;
    *rsz = 0;

    /* Allocate memory. */
    if (!(count = calloc(nsz * 3, sizeof(int))))
        return NULL;
    tarr = &count[nsz];
    iarr = &tarr[nsz];
    *rsz = nsz;

    /* Initialize the array. */
    for (i = 0; i < nsz; ++i)
        iarr[i] = i;

    /* Merge sort the array. */
    MergeSort(n, iarr, tarr, 0, nsz - 1, count);
    return count;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int a[] = {5, 2, 6, 1};
    int len = sizeof(a) / sizeof(int), retsz, i;
    int *arr;
    arr = countSmaller(a, len, &retsz);
    for (i = 0; i < retsz; ++i)
        printf("%d \n", arr[i]);
    free(arr);
    return 0;
}
