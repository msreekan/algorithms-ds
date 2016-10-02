/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

/***********************************************************************/
/* GenPascalsRow: Generate a row for Pascal's triangle!                */
/*                                                                     */
/***********************************************************************/
void GenPascalsRow(int *refarr, int *arr, int rownum)
{
    int i;
    arr[0] = arr[rownum - 1] = 1; // set last and first element to 1
    /* Use reference array to generate values */
    for (i = 1; i < rownum - 1; ++i)
        arr[i] = refarr[i - 1] + refarr[i];
}

/***********************************************************************/
/* Given numRows, generate the first numRows of Pascal's triangle.     */
/***********************************************************************/
int* getRow(int rowIndex, int* returnSize)
{
    int *arr, *arr1, *arr2;
    int i, num = rowIndex + 1;

    /* Set the index and allocate space */
    *returnSize = num;
    arr1 = malloc(sizeof(int) * (num));
    if (!arr1)
        return NULL;
    arr2 = malloc(sizeof(int) * (num));
    if (!arr2)
        return NULL;

    /* Initialize and then generate the rows */
    arr1[0] = 1;
    for (i = 1; i < num; ++i)
    {
        GenPascalsRow(arr1, arr2, i + 1);

        /* Ping Ping */
        arr = arr1;
        arr1 = arr2;
        arr2 = arr;
    }
    free(arr2);
    return arr1;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 4, csizes;
    int *arr;
    arr = getRow(num, &csizes);
    PrintArray(arr, csizes);
    printf("\n");
    return 0;
}
