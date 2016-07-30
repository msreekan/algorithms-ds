/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************/
/* Token Macros         */
/************************/
#define IS_NUM(x)         (((x) >= 48) && ((x) <= 57))
#define IS_SIGN(x)        (((x) == '-') || ((x) == '+'))
#define IS_VALID(x)       ((IS_NUM((x))) || (IS_SIGN((x))) ||\
                           ((x) == 'e' || (x) == '.') || (x) == 0)

/************************/
/* Boolean Data         */
/************************/
typedef enum
{
    FALSE,
    TRUE
} bool;

/***********************************************************************/
/* isNum: Recursively parse the number!                                */
/*                                                                     */
/***********************************************************************/
bool isNum(char* s, int *e, int *dot)
{
    /* Skip space, if the end is not NULL, then return FALSE */
    while (*s == ' ') { s++;
        if ((*s) && (*s != ' '))
            return FALSE;
    }

    /* 1. If it's not the first instance of 'e' or if the next character
          is not a number nor a sign, then FALSE.
       2. If it's a '.', then it cannot be preceded by 'e' or another '.'.
       3. If it's a sign, then preceding character has to be 'e' and the
          next one has to be a number.
       4. Else if it's an invalid character, then return FALSE. */
    if (((*s == 'e') && ((!IS_NUM(*(s + 1)) && !IS_SIGN(*(s + 1))) || *e)) || // 1
        ((*s == '.') && (*e || *dot)) ||                                      // 2
        (IS_SIGN(*s) && ((*(s - 1) != 'e') || !IS_NUM(*(s + 1)))) ||          // 3
        (!IS_VALID(*s)))                                                      // 4
        return FALSE;

    /* Track presence of 'e' and '.' characters, there cannot be
       more than one of these */
    *e = (*s == 'e') ? 1 : *e;
    *dot = (*s == '.') ? 1 : *dot;

    /* Unless it is a NULL, move to the next character */
    return (*s == 0) ? 1 : isNum(s + 1, e, dot);
}

/***********************************************************************/
/* Validate if a given string is numeric.                              */
/*                                                                     */
/* Some examples:                                                      */
/* "0" => true                                                         */
/* " 0.1 " => true                                                     */
/* "abc" => false                                                      */
/* "1 a" => false                                                      */
/* "2e10" => true                                                      */
/*                                                                     */
/***********************************************************************/
bool isNumber(char* s)
{
    int e = 0, dot = 0;

    /* Skip leading white spaces */
    while (*s == ' ') ++s;

    /* Skip the first leading sign */
    if (IS_SIGN(*s)) s++;

    /* Leading NULL or 'e' is invalid. So is a '.' which is not followed
       by a number */
    if ((*s == 0) || (*s == 'e') || (*s == '.' && !IS_NUM(*(s + 1))))
        return FALSE;

    /* Evaluate the remaining characters */
    return isNum(s, &e, &dot);
}
/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *s[] = {"0", " 0.1 ", "abc", "1 a", "2e10", ".", ".4", "e9", "..", "3.", "3. ", ". ", ".4.", "e5e", "-4.1e-10", "5e-10", "-1.", "3-2", "+.8", " -.", " +0e-", "6e6.5", " 005047e+6", "1 "};
    int res[] = {1,     1,      0,     0,     1,      0,   1,    0,    0,    1,   1,     0,   0,      0,     1,          1,        1,     0,     1,    0,     0,       0,        1,           1};
    int len = sizeof(s) / sizeof(char *), i;
    for (i = 0; i < len; ++i)
    {
        int ret = isNumber(s[i]);
        if (ret != res[i])
            printf("FAIL %s = %d :\n", s[i], isNumber(s[i]));
        else
            printf("SUCCESS %s = %d :\n", s[i], isNumber(s[i]));
    }
    return 0;
}
