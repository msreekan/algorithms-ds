/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*********************************************/
/* Data Structures                           */
/*********************************************/
struct Point
{
    int x;
    int y;
};

/***********************************************************************/
/* Given n points on a 2D plane, find the maximum number of points that*/
/* lie on the same straight                                            */
/* line.                                                               */
/***********************************************************************/
int maxPoints(struct Point* points, int pointsSize)
{
    int i, j, k, max_count = 1, tcount, xp, yp;
    double m, c, epsilon =  0.00001;

    /* Validate */
    if (!points || pointsSize  < 1)
        return 0;

    /*
        Line equation, y = mx + c :
        SLOPE : m = (y2 - y1) / (x2 - x1)
        Y-intercept: c = y - mx
    */
    /* Brute force loop for picking two points to find the slope and y
       intercept of the connecting line. */
    for (i = 0; i < pointsSize; ++i)
        for (j = i + 1; j < pointsSize; ++j)
        {
            xp = 0, yp = 0, m = 0, c = 0; // reset states
            /* If the line is parallel to x, then y coordinates will
            be same */
            if (points[j].y == points[i].y)
                xp = 1;
            /* Else if X-Coordinates are the same, then line is
            parallel to y. */
            else if (points[j].x == points[i].x)
                yp = 1;
            /* Else it's a generic case, calculate slope and
            y-intercept */
            else {
                m = ((points[i].y - points[j].y) * 1.0) /
                     (points[i].x - points[j].x);
                c = points[i].y - m * points[i].x;
            }

            /* Find all the coordinates points[k] which falls in the line
            connecting points[i] & points[j] */
            tcount = 2;
            for (k = 0; k < pointsSize; ++k)
                if (k != i && k != j){
                    /* Handle the above three cases */
                    if ((xp && points[k].y == points[i].y) || // y = c
                        (yp && points[k].x == points[i].x) || // x = x1
                        (!xp && !yp && fabs((m * points[k].x + c) - // y = mx + c
                         (points[k].y * 1.0)) < epsilon))
                        tcount++;
                }
            /* If the count is greater then update */
            if (max_count < tcount)
                max_count = tcount;
        }
    /* Return max count */
    return max_count;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //struct Point arr[] = {{560,248},{0,16},{30,250},{950,187},{630,277},{950,187},{-212,-268},{-287,-222},{53,37},{-280,-100},{-1,-14},{-5,4},{-35,-387},{-95,11},{-70,-13},{-700,-274},{-95,11},{-2,-33},{3,62},{-4,-47},{106,98},{-7,-65},{-8,-71},{-8,-147},{5,5},{-5,-90},{-420,-158},{-420,-158},{-350,-129},{-475,-53},{-4,-47},{-380,-37},{0,-24},{35,299},{-8,-71},{-2,-6},{8,25},{6,13},{-106,-146},{53,37},{-7,-128},{-5,-1},{-318,-390},{-15,-191},{-665,-85},{318,342},{7,138},{-570,-69},{-9,-4},{0,-9},{1,-7},{-51,23},{4,1},{-7,5},{-280,-100},{700,306},{0,-23},{-7,-4},{-246,-184},{350,161},{-424,-512},{35,299},{0,-24},{-140,-42},{-760,-101},{-9,-9},{140,74},{-285,-21},{-350,-129},{-6,9},{-630,-245},{700,306},{1,-17},{0,16},{-70,-13},{1,24},{-328,-260},{-34,26},{7,-5},{-371,-451},{-570,-69},{0,27},{-7,-65},{-9,-166},{-475,-53},{-68,20},{210,103},{700,306},{7,-6},{-3,-52},{-106,-146},{560,248},{10,6},{6,119},{0,2},{-41,6},{7,19},{30,250}};
    //struct Point arr[] = {{0,0}, {1,1}, {1,-1}};
    //struct Point arr[] = {{0,0}, {-1,-1}, {2,2}};
    struct Point arr[] = {{0,-12},{5,2},{2,5},{0,-5},{1,5},{2,-2},{5,-4},{3,4},{-2,4},{-1,4},{0,-5},{0,-8},{-2,-1},{0,-11},{0,-9}};
    int len = sizeof(arr) / sizeof(struct Point);

    printf("Max Points = %d:\n", maxPoints(arr, len));
    return 0;
}
