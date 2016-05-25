/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given n non-negative integers a1, a2, ..., an, where each represents*/
/* a point at coordinate (i, ai). n vertical lines are drawn such that */
/* the two endpoints of line i is at (i, ai) and (i, 0). Find two      */
/* lines, which together with x-axis forms a container, such that the  */
/* container contains the most water.                                  */
/* Note: You may not slant the container.                              */
/*                                                                     */
/***********************************************************************/
int maxArea(int* height, int heightSize)
{
    int max_volume = 0;
    int ht = 0, len = 0, s = 0, e = heightSize - 1;

    /* Ensure sanity */
    if (height == NULL)
        return 0;

    /* Loop while the start is less than end */
    while (s < e)
    {
        /* Calculate the x axis length */
        len = (e + 1) - (s + 1);

        /* Calculate the container height */
        ht = height[s] > height[e] ? height[e] : height[s];

        /* Update the container volume */
        if (max_volume < (ht * len))
            max_volume = ht * len;

        /* If start is higher than end, then seek to increase end */
        if (height[s] > height[e])
        {
            int te = height[e];

            /* Loop till a higher end is found */
            do
                e--;
            while((e > s) && (te > height[e]));
        }

        /* Else seek to increase start */
        else
        {
            int ts = height[s];
            /* Seek for a higher start */
            do
                s++;
            while((e > s) && (ts > height[s]));
        }
    }

    /* Return the maximum volume */
    return max_volume;
}

/***********************************************************************/
/* main : Entry point                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int ht[] = {3, 1, 3};
    int len = sizeof(ht) / sizeof(int);

    printf("Area = %d", maxArea(ht, len));
    return 0;
}

