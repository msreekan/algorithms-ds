/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************/
/* Macros                                    */
/*********************************************/
#define CH_OFF(x) ((x) - 'C')

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
/* Given a roman numeral, convert it to an integer.                    */
/* Input is guaranteed to be within the range from 1 to 3999.          */
/***********************************************************************/
int romanToInt(char* s)
{
    /*            C    D    E, F, G, H, I, J, K, L      M, N,  O, P */
    int nv[22] = {100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0,  0, 0,
    /*            Q,   R    S,  T,  U,  V,  W,  X  */
                  0,   0,   0,  0,  0,  5,  0,  10};
    int num = 0, i;

    /* Loop and process all the characters */
    for (i = 0; s[i]; ++i)
        num += (s[i + 1] && nv[CH_OFF(s[i])] < nv[CH_OFF(s[i + 1])]) ?
                -nv[CH_OFF(s[i])] : nv[CH_OFF(s[i])];

    /* Return the number */
    return num;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int i;
    char *s;
    for (i = 1; i < 3999; ++i)
    {
        s = intToRoman(i);
        if (romanToInt(s) != i)
            printf("Error : %s %d", s, romanToInt(s));
        free(s);
    }
    return 0;
}
