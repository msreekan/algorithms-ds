/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/***********************************/
/* Macros.                         */
/***********************************/
#define MAX_ADJ 16

/***********************************************************************/
/* gdfs: Run recursive DFS on a graph!                                 */
/*                                                                     */
/***********************************************************************/
bool gdfs(int num, int *mat, unsigned char *tmap, unsigned char *vmap,
          int v)
{
    int i;

    /* If there is a loop, then return. */
    if (tmap[v])
        return false;
    /* If the node was already visited, then return. */
    if (vmap[v])
        return true;

    /* Mark the node as being part of the traversed sub-graph.*/
    tmap[v] = true;

    /* Loop traversing all the nodes. */
    for (i = 1; i < mat[v * MAX_ADJ]; ++i)
        if (!gdfs(num, mat, tmap, vmap, mat[(v * MAX_ADJ) + i]))
            return false;

    /* Reset the transient map, set vertex as visited. */
    tmap[v] = false;
    vmap[v] = true;

    /* Return. */
    return true;
}

/***********************************************************************/
/* genAdMatrix: Generate adjacency matrix!                             */
/*                                                                     */
/***********************************************************************/
int *genAdMatrix(int num, int** prq, int prsize)
{
    /* Allocate matrix, allow extra row to record edges for vertex. */
    int *mat = malloc(sizeof(int) * num * MAX_ADJ);
    int i;

    /* Initialize the matrix edge count. Set to 1 for convenient
    indexing */
    for (i = 0; i < num; ++i)
        mat[i * MAX_ADJ] = 1;

    /* Run through the array, picking the edges. */
    for (i = 0; i < prsize; i++)
    {
        /* Index using the vertex count. */
        int index = (prq[i])[0] * MAX_ADJ, ecnt = mat[index];
        if (ecnt == MAX_ADJ) // Ensure sanity
            exit(-1);
        mat[index + ecnt] = (prq[i])[1];
        mat[index] = ecnt + 1; // increment the edge count
    }

    /* Return the adjacency matrix. */
    return mat;
}

/***********************************************************************/
/* There are a total of n courses you have to take, labeled from 0 to  */
/* n - 1.                                                              */
/*                                                                     */
/* Some courses may have prerequisites, for example to take course 0   */
/* you have to first take course 1, which is expressed as a pair: [0,1]*/
/* Given the total number of courses and a list of prerequisite pairs, */
/* is it possible for you to finish all courses?                       */
/*                                                                     */
/* For example:                                                        */
/* 2, [[1,0]]                                                          */
/* There are a total of 2 courses to take. To take course 1 you should */
/* have finished course 0. So it is possible.                          */
/*                                                                     */
/* 2, [[1,0],[0,1]]                                                    */
/* There are a total of 2 courses to take. To take course 1 you should */
/* have finished course 0, and to take course 0 you should also have   */
/* finished course 1. So it is impossible.                             */
/* Note:                                                               */
/* The input prerequisites is a graph represented by a list of edges,  */
/* not adjacency matrices.                                             */
/***********************************************************************/
bool canFinish(int num, int** prq, int prsize, int pcsize)
{
    int *mat;
    bool ret;
    unsigned char *tmap, *vmap;
    int v = 0;

    /* Validate. */
    if (num < 0 || !prq || prsize < 0 || pcsize < 0)
        return false;

    /* Generate an adjacency marix. */
    if (!(mat = genAdMatrix(num, prq, prsize)))
        return false;

    /* Allocate two maps.
       1. One to mark the ongoing path.
       2. Second one to mark the visited nodes.  */
    if (!(tmap = calloc(2 * num, sizeof(unsigned char))))
        return false;
    vmap = tmap + num;

    /* Run a DFS to verify there are no looping dependencies. */
    for (v = 0; v < num; ++v)
        if (!(ret = gdfs(num, mat, tmap, vmap, v)))
            break;

    /* Free memory. */
    free(mat);
    free(tmap);
    return ret;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    #if 0
    int a1[] = {1, 0}, a2[] = {0, 2}, a3[] = {2, 3}, a4[] = {3, 0};
    int *a[] = {a1, a2, a3, a4};
    int num = 4, r = 4, c = 2;
    #else
    int a1[] = {0, 1}, a2[] = {0, 2}, a3[] = {1, 2};
    int *a[] = {a1, a2, a3};
    int num = 3, r = 3, c = 2;
    #endif
    /* Call the routine. */
    if (canFinish(num, a, r, c))
        printf("Can Finish. \n");
    else
        printf("Cannot Finish.");
    return 0;
}
