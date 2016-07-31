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
/* get_str_offst: Get string offset                                    */
/*                                                                     */
/***********************************************************************/
int get_str_offst(char **w, int offst, int wsz, int width,
                  unsigned char  *larr, int *len)
{
    int i, j = 0, slen;

    /* Loop to figure out the maximum number of words which can be
       accommodated within the width */
    *len = 0;
    for (i = offst; i < wsz; ++i, (*len) += 1, ++j)
    {
        /* Get the length break the loop if it exceeds the width */
        slen = strlen(w[i]);
        if (*len + slen > width)
            break;

        /* Store the length and increment the counter */
        larr[j * 2] = slen;
        (*len) += larr[j * 2];
        larr[j * 2 + 1] = (*len < width) ? 1 : 0;
    }

    /* There should not be a space at the end */
    larr[(j - 1) * 2 + 1] = 0;
    (*len) -= 1;
    return i - 1;
}

/***********************************************************************/
/* get_spaces: Get the empty space packing for the width               */
/*                                                                     */
/***********************************************************************/
void get_spaces(unsigned char *larr, int cnt, int width, int len)
{
    int scnt, i, j, scntr;

    /* If there is only one word, then append the spaces to the end */
    if (!cnt)
        larr[1] = width - len;
    else {
        /* Divide the space into the number of available slots */
        scnt = (width - len) / cnt;
        scntr = (width - len) % cnt;
        for (i = 1, j = 0; j < cnt; j++, i+= 2)
        {
            larr[i] += scnt;
            if (scntr-- > 0) // Split remainder */
                larr[i]++;
        }
    }
}

/***********************************************************************/
/* gen_space_strings: Generate strings separated by spaces             */
/*                                                                     */
/***********************************************************************/
void gen_space_strings(char **words, char *str, unsigned char *larr,
                       int slen)
{
    int i, j = 0, k = 0, l;

    /* Loop while the string or the white space counts are > 0 */
    for (i = 0; larr[i] || larr[i + 1]; i += 2)
    {
        /* Copy the word */
        memcpy(&str[k], words[j++], larr[i]);
        k += larr[i]; // increment offset

        /* Accommodate white space */
        for (l = 0; l < larr[i + 1]; ++l)
            str[k++] = ' ';
    }

    /* Fill any remaining offsets with white space, remember thag
    the last line has to be right justified */
    while (k < slen)
        str[k++] = ' ';
}

/***********************************************************************/
/* free_strings: Free string list                                      */
/*                                                                     */
/***********************************************************************/
void free_strings(char **ch, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        free(ch[i]);
}

/***********************************************************************/
/* fullJustify: Text justification.                                    */
/* https://leetcode.com/problems/text-justification/                   */
/*                                                                     */
/***********************************************************************/
char** fullJustify(char** words, int wordsSize, int maxWidth,
                   int* returnSize)
{
    int csize = maxWidth + 3;
    unsigned char *map = calloc(csize, sizeof(unsigned char));
    int i, j, k = 0, m = 0, len;
    char **cj;

    /* Trust, but verify */
    if (!map)
        return NULL;
    *returnSize = 0;

    /* Allocate the output string */
    cj = malloc(sizeof(char *) * wordsSize);
    if (!cj)
        return NULL;

    /* Loop seeking the string and the offset */
    for (i = 0; i < wordsSize; i = j + 1, ++m, ++k)
    {
        /* Get the number of strings which can be accommodated within
           the maxWidth range. [i, j] */
        j = get_str_offst(words, i, wordsSize, maxWidth, map, &len);

        /* Allocate the string of length maxWidth */
        cj[m] = calloc(maxWidth + 1, sizeof(char));
        if (!cj[m])
        {
            free_strings(cj, m);
            return NULL;
        }

        /* Generate right justified strings until the very last line */
        if (j + 1 <= wordsSize - 1)
            get_spaces(map, j - i, maxWidth, len);
        gen_space_strings(&words[i], cj[m], map, maxWidth);
        memset(map, 0, csize * sizeof(unsigned char));
    }

    *returnSize = m;
    free(map);
    return cj;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    char s1[] = "This", s2[] = "is", s3[] = "an", s4[] = "example";
    char s5[] = "of", s6[] = "text", s7[] = "justification.";
    char *s[] = {s1, s2, s3, s4, s5, s6, s7};
    int width = 16;
    #elif 0
    char s1[] = "a", s2[] = "b", s3[] = "c", s4[] = "d";
    char s5[] = "e";
    char *s[] = {s1, s2, s3, s4, s5};
    int width = 1;
    #elif 0
    char s1[] = "Listen", s2[] = "to", s3[] = "many", s4[] = "speak";
    char s5[] = "to", s6[] = "a", s7[] = "few.";
    char *s[] = {s1, s2, s3, s4, s5, s6, s7};
    int width = 6;
    #elif 0
    char s1[] = "";
    char *s[] = {s1};
    int width = 2;
    #elif 1
    char s1[] = "What", s2[] = "must", s3[] = "be", s4[] = "shall";
    char s5[] = "be.";
    char *s[] = {s1, s2, s3, s4, s5};
    int width = 12;
    #endif
    int len = sizeof(s) / sizeof(char *), ret;
    char **sp;
    int i;

    sp = fullJustify(s, len, width, &ret);
    for (i = 0; i < ret; ++i)
    {
        printf ("%s \n", sp[i]);
        free(sp[i]);
    }
    return 0;
}
