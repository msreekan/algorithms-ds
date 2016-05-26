/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Given n non-negative integers representing an elevation map where   */
/* the width of each bar is 1, compute how much water it is able to    */
/* trap after raining.                                                 */
/*                                                                     */
/* For example,                                                        */
/* Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.                          */
/***********************************************************************/
int trap(int* height, int heightSize)
{
    int i, j, k;
    int units = 0, highest = -1, offst = -1;
    int len = heightSize;
    int *arr = height;

    /* Run through the wall */
    for (i = 0; i < len; ++i)
    {
        /* If we have a wall, then seek the next wall in the direct line
        of sight */
        if (arr[i] > 0)
        {
            int tunits = 0, tbase = arr[i];
            highest = -1;

            /* Loop searching for highest adjacent wall */
            for (j = i + 1; j < len; ++j)
            {
                /* If the wall height is greater than 0 and it's highest
                then select that */
                if ((arr[j] > 0) && (arr[j] > highest))
                {
                    highest = arr[j];
                    offst = j;
                }

                /* We need not search beyond the direct line of sight, which is essentially
                a wall as high or higher than the present wall. */
                if (arr[j] >= arr[i])
                    break;
                else
                    tunits += tbase - arr[j];
            }

            /* If we found the wall then calculate the units */
            if (highest != -1)
            {
                int base = arr[i] > arr[offst] ? arr[offst] : arr[i];


                /* We already have the units calculated in the above loop */
                if (base == arr[i])
                    units += tunits;

                /* Else if the units were calculated relative to the wrong base,
                then we need to do this again */
                else
                {
                    for (k = i + 1; k < offst; k++)
                        units += (base - arr[k]);
                }

                /* Go to the next index */
                i = offst - 1;
            }
        }
    }

    /* Return the rain water units */
    return units;
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    int arr[] = {0, 2, 1, 0, 1, 2, 3, 2, 0, 1, 0, 3, 0, 1, 2, 0, 1, 2};
    int len = sizeof(arr) / sizeof(int);

    printf("Units = %d \n", trap(arr, len));
    return 0;
}

