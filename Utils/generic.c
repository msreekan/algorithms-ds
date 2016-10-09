/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************************************************/
/* isAlphaNum: Check for ASCII alphanumeric character                  */
/*                                                                     */
/***********************************************************************/
int isAlphaNum(char s)
{
    return ((s > 47 && s < 58) || (s > 64 && s < 91) ||
            (s > 96 && s < 123)) ? true : false;
}

/***********************************************************************/
/* toLower: Return lowercase if the character is upper case            */
/*                                                                     */
/***********************************************************************/
int toLower(char s)
{
    return (s > 64 && s < 91) ? s + 32 : s;
}

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
