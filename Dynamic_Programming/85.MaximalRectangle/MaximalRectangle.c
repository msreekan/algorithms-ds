/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* prn_arr: Print array                                                */
/*                                                                     */
/***********************************************************************/
void prn_arr(char *arr, int len)
{
    int i;
    for (i = 0; i < len - 1; ++i)
        printf("%c, ", arr[i]);
    printf("%c\n", arr[i]);
}

/***********************************************************************/
/* encode_row: Encode a row into the array                             */
/*                                                                     */
/***********************************************************************/
void encode_row(char *arr, int len)
{
    int i, cnt = 0;

    /* Run through the row */
    for (i = 0; i < len; ++i)
    {
        cnt = (arr[i] == '1') ? cnt + 1 : 0;
        arr[i] = cnt;
    }
}

/***********************************************************************/
/* Given a 2D binary matrix filled with 0's and 1's, find the largest  */
/*                                                                     */
/* rectangle containing only 1's and return its area.                  */
/*                                                                     */
/* For example, given the following matrix:                            */
/* 1 0 1 0 0                                                           */
/* 1 0 1 1 1                                                           */
/* 1 1 1 1 1                                                           */
/* 1 0 0 1 0                                                           */
/*                                                                     */
/* Return 6.                                                           */
/***********************************************************************/
int maximalRectangle(char** matrix, int matrixRowSize, int matrixColSize)
{
    int mr = matrixRowSize, mc = matrixColSize, i, j;
    int k, area = 0;

    /* Validate the parameters */
    if (!matrix || !mr || !mc)
        return 0;

    /* Encode rows */
    for (i = 0; i < mr; ++i)
        encode_row(matrix[i], mc);

    /* Run through the encoded columns checking area */
    for (i = mc - 1; i >= 0; --i)
        for (j = 0; j < mr; ++j) // rows
        {
            int length = *(matrix[j] + i), width = 1;

            /* Calculate the area */
            area = (area < length * width) ? length * width : area;

            /* Get the largest rectangle starting at [i, j] */
            for (k = j + 1; k < mr && *(matrix[k] + i); ++k)
            {
                width++;
                length = *(matrix[k] + i) < length ? *(matrix[k] + i) :
                                            length;
                area = (area < length * width) ? length * width : area;
            }
        }

    /* Return area */
    return area;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char a1[] = "101101", a2[] = "111111", a3[] = "011011";
    char a4[] = "111010", a5[] = "011111", a6[] = "110111";
    char *a[] = {a1, a2, a3, a4, a5, a6};
    int r = sizeof(a) / sizeof(char *), c = sizeof(a1) / sizeof(char);
    int res = 8;

    if (maximalRectangle(a, r, c) != res)
        printf("FAILURE \n");
    else
        printf("SUCCESS \n");
    return 0;
}
