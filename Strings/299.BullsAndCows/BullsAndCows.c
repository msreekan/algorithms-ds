/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************/
/* Macros                           */
/************************************/
#define ASCII_TO_INT(x) ((x) - '0')
#define INT_TO_ASCII(x) ((x) + '0')
#define MIN_VAL(a, b)   ((a) > (b) ? (b) : (a))
#define SWAP_CHAR(x, y) {\
                          char c = x;\
                          x = y;\
                          y = c;\
                        }

/***********************************************************************/
/* i_toa: Integer to ASCII!                                            */
/*                                                                     */
/***********************************************************************/
int i_toa(int val, char *str, char t)
{
    int i = 0, j, len;

    /* Generate the string. */
    do
        str[i++] = INT_TO_ASCII(val % 10);
    while (val /= 10);

    /* Reverse the string. */
    len = j = i - 1;
    for (i = 0; i < j; ++i, --j)
        SWAP_CHAR(str[i], str[j]);

    /* Terminate and return the length. */
    str[++len] = t;
    return len + 1;
}

/***********************************************************************/
/* https://leetcode.com/problems/bulls-and-cows/#/description          */
/***********************************************************************/
char* getHint(char* secret, char* guess)
{
    int smap[10] = {0}, gmap[10] = {0};
    int i, bulls = 0, cows = 0, len;
    char *cb;

    /* Validate the inputs. */
    if (!secret || !guess)
        return NULL;

    /* Allocate space for result, accomodates space for max int
    value. */
    if (!(cb = malloc(sizeof(char) * 24)))
        return NULL;

    /* Generate the map. */
    for (i = 0; secret[i]; ++i)
    {
        /* If the characters mismatch, then increment maps. */
        if (secret[i] != guess[i])
        {
            smap[ASCII_TO_INT(secret[i])]++;
            gmap[ASCII_TO_INT(guess[i])]++;
        }
        /* Else increment bulls. */
        else
            bulls++;
    }

    /* Calculate the cows. */
    for (i = 0; i < 10; ++i)
        cows += MIN_VAL(smap[i], gmap[i]);

    /* Generate the string and return. */
    len = i_toa(bulls, cb, 'A');
    len += i_toa(cows, &cb[len], 'B');
    cb[len] = 0;
    return cb;
}


/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
#if 1
    char s[] = "1807";
    char g[] = "7810";
#else
    char s[] = "777891";
    char g[] = "022291";
#endif
    char *cb;
    cb = getHint(s, g);
    printf("%s \n", cb);
    free(cb);
    return 0;
}
