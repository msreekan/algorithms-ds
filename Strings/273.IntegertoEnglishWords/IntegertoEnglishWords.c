/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************/
/* Macros.                                         */
/***************************************************/
#define STR_LEN 512

/***********************************************************************/
/* Convert a non-negative integer to its english words representation. */
/* Given input is guaranteed to be less than 231 - 1.                  */
/* For example,                                                        */
/* 123 -> "One Hundred Twenty Three"                                   */
/* 12345 -> "Twelve Thousand Three Hundred Forty Five"                 */
/* 1234567 -> "One Million Two Hundred Thirty Four Thousand Five       */
/* Hundred Sixty Seven"                                                */
/***********************************************************************/
char* numberToWords(int num)
{
    char o2t[][16] = {"", "", "", "", "", "", "", "", "", "", "Ten ",
                      "Eleven ", "Twelve ", "Thirteen ", "Fourteen ",
                      "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ",
                      "Nineteen "};
    char ones[][16] = {"", "One ", "Two ", "Three ", "Four ", "Five ",
                       "Six ", "Seven ", "Eight ", "Nine "};
    char tens[][16] = {"", "", "Twenty ", "Thirty ", "Forty ", "Fifty ",
                       "Sixty ", "Seventy ", "Eighty ", "Ninety "};
    char h[][16] = {"Billion ", "Million ", "Thousand ", "", "", ""};
    int m[] = { 1000000000, 1000000, 1000, 1};
    int val = num, i, msb, soff = 0;
    char *str;

    /* Allocate the string array. */
    if (!(str = malloc(sizeof(char) * STR_LEN)))
        return NULL;

    /* Handle the special case. */
    if (!num)
    {
        strcpy(str, "Zero");
        return str;
    }

    /* Loop and translate all the values. */
    while (val)
    {
        /* Get the MSB values. */
        for (i = 0; i < sizeof(m) / sizeof(int); ++i) {
            if (val / m[i])
            {
                msb = val / m[i];
                val = val % m[i];
                break;
            }
        }

        /* If we have values to parse, then do the same. */
        if (msb)
        {
            /* Get the value in the hundreds. */
            if (msb / 100)
            {
                /* Copy the contents. */
                if (strcpy(&str[soff], ones[msb / 100]) != &str[soff])
                    return str;
                soff += strlen(ones[msb / 100]);
                if (strcpy(&str[soff], "Hundred ") != &str[soff])
                    return str;
                soff += strlen("Hundred ");
                msb %= 100;
            }

            /* If there are tens, then add the same. */
            if (msb / 10 >= 2)
            {
                /* Copy the contents. */
                if (strcpy(&str[soff], tens[msb / 10]) != &str[soff])
                    return str;
                soff += strlen(tens[msb / 10]);

                /* Add any trailing ones here. */
                if (msb % 10)
                {
                    /* Copy the contents. */
                    if (strcpy(&str[soff], ones[msb % 10]) != &str[soff])
                        return str;
                    soff += strlen(ones[msb % 10]);
                }
            }

            /* Else if we have a value between 10 and 19, then add that here. */
            else if (msb / 10)
            {
                /* Copy the contents. */
                if (strcpy(&str[soff], o2t[msb % 20]) != &str[soff])
                    return str;
                soff += strlen(o2t[msb % 20]);
            }

            /* If there are ones, then add the same. */
            else if (msb % 10)
            {
                /* Copy the contents. */
                if (strcpy(&str[soff], ones[msb % 10]) != &str[soff])
                    return str;
                soff += strlen(ones[msb % 10]);
            }

            /* Now add the thousands, millions and billions. */
            if (strcpy(&str[soff], h[i]) != &str[soff])
                return str;
            soff += strlen(h[i]);
        }
    }

    /* Add terminating character and return. */
    str[soff - 1] = 0;
    return str;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 123;
    char *str;
    str = numberToWords(num);
    printf("%d = %s:\n", num, str);
    free(str);
    return 0;
}
