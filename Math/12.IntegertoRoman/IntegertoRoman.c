/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* Given an integer, convert it to a roman numeral.                    */
/* Input is guaranteed to be within the range from 1 to 3999.          */
/***********************************************************************/
char* intToRoman(int num)
{
    int roff = 0, i, div = 1000, j;
    char *roman = malloc(16);
    /* Made static to move this table into .data segment, avoids stack
    reinitialization */
    static char *rn[][16] =
    {{"","I","II","III","IV","V","VI","VII","VIII","IX","X"},
     {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
     {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
     {"","M","MM","MMM"}};

    /* Validate allocation */
    if (!roman) return NULL;

    /* Convert */
    for (i = 3; i >= 0; --i, div /= 10)
        for (j = 0; j < *(rn[i][(num / div) % 10] + j); ++j)
            roman[roff++] = *(rn[i][(num / div) % 10] + j);

    /* Return the number */
    roman[roff] = 0;
    return roman;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *r;
    int i;
    for (i = 1; i < 3999; ++i)
    {
        r = intToRoman(i);
        printf("\"%s\",\n", r);
        free(r);
    }
    return 0;
}
