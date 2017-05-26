/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*******************************************/
/* Macros                                  */
/*******************************************/
#define INT_SWAP(a, b) {\
                        int t = (b);\
                        (b) = (a);\
                        (a) = t;\
                        }

/***********************************************************************/
/* BubbleSort: Sort an array of 4!                                     */
/*                                                                     */
/***********************************************************************/
void BubbleSort(int *a)
{
    int swap = 1, i, j;

    /* Sort them and pick the intermediate coordinates. */
    for (i = 0; i < 4 && swap; ++i)
        for (swap = 0, j = 1; j < 4; ++j) {
            if (a[j] < a[j - 1]) {
                INT_SWAP(a[j], a[j - 1]);
                swap = 1;
            }
        }
}

/***********************************************************************/
/* Find the total area covered by two rectilinear rectangles in a 2D   */
/* plane.                                                              */
/***********************************************************************/
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
    int a1 = (A - C) * (B - D), a2 = (E - G) * (F - H), a3 = 0;

    /* If there overlap,  then calculate the area. */
    if (!(((A < E && C < E) || (B < F && D < F)) ||
         ((E < A && G < A) || (F < B && H < B))))
    {
        int a[] = {A, E, C, G};
        int b[] = {F, B, H, D};

        /* Sort coordinate array. */
        BubbleSort(a);
        BubbleSort(b);

        /* The intermediate values will give us the overlap area.*/
        a3 = (a[1] - a[2]) * (b[1] - b[2]);
    }

    /* Sum the areas, subtract the difference. */
    return a1 + a2 - a3;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //int A = -2, B = -2, C = 2, D = 2, E = -2, F = -2, G = 2, H = 2;
    int A = 0, B = 0, C = 0, D = 0, E = -1, F = -1, G = 1, H = 1;
    printf("Area = %d :\n", computeArea(A, B, C, D, E, F, G, H));
    return 0;
}
