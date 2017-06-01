/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* What if the citations array is sorted in ascending order? Could you */
/* optimize your algorithm?                                            */
/*                                                                     */
/***********************************************************************/
int hIndex(int* citations, int citationsSize)
{
    int i;

    /* Loop seeking the index where numbers of papers equal the citation
    count. */
    for (i = 0; i < citationsSize; ++i)
        if (citations[i] >= (citationsSize - i))
            break;
    /* Return the value. */
    return citationsSize - i;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    return 0;
}
