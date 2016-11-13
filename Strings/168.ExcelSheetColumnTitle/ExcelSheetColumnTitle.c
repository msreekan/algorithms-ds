/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**************************************/
/* Macros                             */
/**************************************/
#define MAX_STR_LEN 512

/***********************************************************************/
/* ConvertTitle: Convert title                                         */
/*                                                                     */
/***********************************************************************/
void ConvertTitle(int n, char **str, char *map)
{
    /* If the value is greater than zero, then proceed. */
    if (n > 0)  {
        /* Calculate the title alphabet offset.*/
        ConvertTitle ((n - ((n % 26) == 0 ? 26 : n % 26)) / 26, str, map);
        **str = map[n % 26];
        (*str) += 1; // increment the pointer after each assignment
    }
}

/***********************************************************************/
/* Given a positive integer, return its corresponding column title as  */
/* appear in an Excel sheet.                                           */
/* For example:                                                        */
/*    1 -> A                                                           */
/*    2 -> B                                                           */
/*    3 -> C                                                           */
/*     ...                                                             */
/*    26 -> Z                                                          */
/*    27 -> AA                                                         */
/*    28 -> AB                                                         */
/***********************************************************************/
char* convertToTitle(int n) {
    char map[] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
    char *str = malloc(sizeof(char) * MAX_STR_LEN), *tstr = str;
    if (str)
        ConvertTitle(n, &tstr, map);
    *tstr = 0; // NULL terminate the answer
    return str;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n = 76;
    char *str = convertToTitle(n);
    printf("Number = %d, Title = %s :\n", n, str);
    free(str);
    return 0;
}
