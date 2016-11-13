/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/* Macros                                        */
/*************************************************/
#define RECURSIVE 0

#if RECURSIVE
/***********************************************************************/
/* TitleToN: Title to number                                           */
/*                                                                     */
/***********************************************************************/
int TitleToN(char *s, int n)
{
    return *s ? TitleToN(s + 1, (n * 26) + (*s + 1) - 'A') : n;
}

/***********************************************************************/
/* Given a column title as appear in an Excel sheet, return its        */
/* corresponding column number.                                        */
/* For example:                                                        */
/*   A -> 1                                                            */
/*   B -> 2                                                            */
/*   C -> 3                                                            */
/*    ...                                                              */
/*   Z -> 26                                                           */
/*   AA -> 27                                                          */
/*   AB -> 28                                                          */
/***********************************************************************/
int titleToNumber(char* s)
{
    return TitleToN(s, 0);
}

#else
/***********************************************************************/
/* Given a column title as appear in an Excel sheet, return its        */
/* corresponding column number.                                        */
/* For example:                                                        */
/*   A -> 1                                                            */
/*   B -> 2                                                            */
/*   C -> 3                                                            */
/*    ...                                                              */
/*   Z -> 26                                                           */
/*   AA -> 27                                                          */
/*   AB -> 28                                                          */
/***********************************************************************/
int titleToNumber(char* s)
{
    int i, n = 0;
    /* Loop parsing the title */
    for (i = 0; s[i]; ++i)
        n = (n * 26) + (s[i] + 1) - 'A';
    return n; // return the value
}
#endif // RECURSIVE

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "AAS";
    printf("Title %s : Number %d \n", s, titleToNumber(s));
    return 0;
}
