/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/generic.h"

/*****************************************/
/* Macros                                */
/*****************************************/
#define MAX_NODE_DEGREE 64

/***********************************************************************/
/* genAdjMat: Generate an adjacency matrix!                            */
/*                                                                     */
/***********************************************************************/
int  *genAdjMat(int num, int** prereq, int preqRowSz, int preqColSz)
{
    int i, j;
    int * mat;

    /* Allocate the matrix, panic if memory allocation fails. */
    if (!(mat = calloc(sizeof(int), num * MAX_NODE_DEGREE)))
        return NULL;

    /*  Loop through the pre-requisites. */
    for (i = 0; i < preqRowSz; ++i)
    {
        /* Get the index for the node. */
        int index = (prereq[i])[0] * MAX_NODE_DEGREE;
        /* Get degree for this node. */
        int *degree = &mat[index + MAX_NODE_DEGREE - 1];

        /* Set all the adjacent nodes. */
        for (j = 1; j < preqColSz; ++j, (*degree) += 1) {
            /* An assert. */
            if(*degree == MAX_NODE_DEGREE)
                exit(-1);
            mat[index + *degree] = (prereq[i])[j];
        }
    }

    /* Return the adjacency matrix. */
    return mat;
}

/***********************************************************************/
/* gDFS: Run a DFS on the graph.                                       */
/*                                                                     */
/***********************************************************************/
int gDFS(int *amat, int v, unsigned char *tmap, unsigned char *pmap,
         int *list, int *lsize)
{
    int *nodes = &amat[v * MAX_NODE_DEGREE];
    int degree = nodes[MAX_NODE_DEGREE - 1];
    int i;

    /* If there is a loop, then return. */
    if (tmap[v]) return 1;

    /* If the node was already visited, then return. */
    if (pmap[v]) return 0;

    /* Mark the node as being traversed. Run DFS on each of the
    connections. */
    tmap[v] = 1;
    for (i = 0; i < degree; ++i)
        if (gDFS(amat, nodes[i], tmap, pmap, list, lsize))
            return 1;

    /* Node traversal done, set the permanent marker. */
    tmap[v] = 0;
    pmap[v] = 1;

    /* Add the node to the list before we backtrack. */
    list[*lsize] = v;
    (*lsize) += 1;  // increment the node count
    return 0;
}

/***********************************************************************/
/* There are a total of n courses you have to take, labeled from 0 to  */
/* n - 1. Some courses may have prerequisites, for example to take     */
/* course 0 you have to first take course 1, which is expressed as a   */
/* pair: [0,1]. Given the total number of courses and a list of        */
/* prerequisite pairs, return the ordering of courses you should take  */
/* to finish all courses.                                              */
/* There may be multiple correct orders, you just need to return one   */
/* of them. If it is impossible to finish all courses, return an empty */
/* array.                                                              */
/* For example:                                                        */
/* 2, [[1,0]]                                                          */
/* There are a total of 2 courses to take. To take course 1 you should */
/* have finished course 0. So the correct course order is [0,1]        */
/* 4, [[1,0],[2,0],[3,1],[3,2]]                                        */
/* There are a total of 4 courses to take. To take course 3 you should */
/* have finished both courses 1 and 2. Both courses 1 and 2 should be  */
/* taken after you finished course 0. So one correct course order is   */
/* [0,1,2,3]. Another correct ordering is[0,2,1,3].                    */
/* Note:                                                               */
/* The input prerequisites is a graph represented by a list of edges,  */
/* not adjacency matrices. Read more about how a graph is represented. */
/* You may assume that there are no duplicate edges in the input       */
/* prerequisites.                                                      */
/***********************************************************************/
int* findOrder(int num, int** prereq, int preqRowSz, int preqColSz,
               int* returnSize)
{
    int *amat = NULL, *list = NULL;
    int lsize = 0, i;
    unsigned char *tmap = NULL, *pmap = NULL;

    /* Ensure there is at least one node.*/
    if (num < 1)
        return NULL;

    /* Validate the parameters. */
    *returnSize = 0; // reset return size
    /* Allocate the memory for output list. */
    if (!(list = malloc(sizeof(int) * num)))
        goto __cexit;

    /* Generate an adjacency matrix for this graph. */
    amat = genAdjMat(num, prereq, preqRowSz, preqColSz);
    if (!amat)
        goto __cexit;

    /* Allocate maps to track the visited nodes. */
    if (!(tmap = calloc(sizeof(unsigned char), num  * 2)))
        goto __cexit;
    pmap = tmap + num;

    /* Allocate the memory for output list. */
    if (!(list = malloc(sizeof(int) * num)))
        goto __cexit;

    /* Run DFS until all the nodes are traversed or until there is a
    failure. */
    for (i = 0; i < num; ++i)
        if (gDFS(amat, i, tmap, pmap, list, &lsize))
            goto __cexit;

    /* Set the return size. */
    *returnSize = lsize;
__cexit:
    if (tmap)
        free(tmap);
    if (amat)
        free(amat);
    return list;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int num = 2, row = 0, col = 2, lsize;
    int r1[] = {1, 0}, r2[] = {2, 0}, r3[] = {3, 1}, r4[] = {3, 2};
    int *r[] = {r1, r2, r3, r4}, *list;

    /* Get the list. */
    list = findOrder(num, r, row, col, &lsize);

    /* Print the order. */
    PrintArray(list, lsize);
    printf("\n");

    return 0;
}
