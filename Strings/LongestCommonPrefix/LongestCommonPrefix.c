/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/***********************************************************************/
/* Write a function to find the longest common prefix string amongst an*/
/* array of strings.                                                   */
/***********************************************************************/
char *longestCommonPrefix(char** strs, int strsSize)
{
    int len = 0, i;
    char *ch = NULL, *rch = NULL;

    /* If the very first entry is valid, pick that as the longest
       common prefix */
    if (strs[0])
    {
        ch = strs[0];
        len = strlen(ch);
    }

    /* Loop through the input array */
    for (i = 0; (i < strsSize) && len; ++i)
    {
        int j;

        /* If the entry is NULL then break */
        if (!strs[i])
            break;

        /* Loop seeking the longest common prefix */
        for (j = 0; j < len; ++j)
        {
            /* If it's the end of the string, break */
            if (strs[i][j] == '\0')
                break;

            /* If the characters mismatch, we can stop scanning */
            if (strs[i][j] != ch[j])
                break;
        }

        /* Check if the longest common prefix has become shorter */
        if (j < len)
        {
            ch = strs[i];
            len = j;
        }
    }

    /* Return empty string if the longest common prefix is zero */
    rch = malloc(sizeof(char) * (len + 1));
    if (!rch)
        return NULL;
    /* Copy string only if it's valid */
    if (ch)
        memcpy(rch, ch, len);
    /* NULL terminate */
    rch[len] = '\0';

    /* Done */
    return rch;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char *ch1[] = {"ch123", "ch234", "ch456", "ch455"};
    char *lp;

    lp = longestCommonPrefix(&ch1[0], sizeof(ch1)/ sizeof(ch1[0]));
    if (lp)
        printf("LP = %s \n", lp);
    free(lp);
    return 0;
}

