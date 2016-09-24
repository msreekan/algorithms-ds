/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* PrintArray: Print an array                                          */
/*                                                                     */
/***********************************************************************/
void PrintArray(int *arr, int len)
{
    int i;

    /* Validate */
    if(!arr || !len)
        return;

    /* Print the contents */
    for (i = 0; i < len; ++i)
        printf("%d ", arr[i]);
}
