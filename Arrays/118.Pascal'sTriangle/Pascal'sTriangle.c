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
int** generate(int numRows, int **columnSizes)
{
    int **arr;
    int i;

    /* Allocate memory for column sizes and for Pascals's rows */
    if (!(*columnSizes = calloc(numRows, sizeof(int))))
        return NULL;
    if (!(arr = malloc(sizeof(int *) * numRows)))
    {
        free(*columnSizes);
        return NULL;
    }

    /* Allocate the first array */
    if (!(arr[0] = malloc(sizeof(int))))
        return arr;

    /* Generate Pascals triangle */
    (*columnSizes)[0] = 1;
    (arr[0])[0] = 1;
    for (i = 1; i < numRows; ++i)
    {
         (*columnSizes)[i] = i + 1;
        if (!(arr[i] = malloc(sizeof(int) * (*columnSizes)[i])))
            return arr;
        GenPascalsRow(arr[i - 1], arr[i], i + 1);
    }

    /* Return the generated triangle */
    return arr;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 5, i;
    int **arr;
    int *csizes;

    arr = generate(num, &csizes);

    for (i = 0; i < num; ++i) {
        PrintArray(arr[i], csizes[i]);
        printf("\n");
    }
    return 0;
}
