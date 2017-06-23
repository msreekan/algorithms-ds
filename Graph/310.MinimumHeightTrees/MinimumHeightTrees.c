/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if O_N2
/***************************************/
/* Macros                              */
/***************************************/
#define ASSERT(x) if(!(x)) exit(-1)

/***************************************/
/* Data Structures                     */
/***************************************/
struct node
{
    int val;            /* Value. */
    struct node *next;  /* Next node. */
};
struct edge
{
    int *n;
    struct edge *next;
};

/***********************************************************************/
/* RemoveLeaf: Delete all the leaf nodes!                              */
/*                                                                     */
/***********************************************************************/
void RemoveLeaf(struct node *nodes, struct edge *e, int ncnt,
                int *degree, int *rarr, int*rsz)
{
    struct node *hn = nodes, *pn = NULL, *n = nodes;
    struct edge *he = e, *nh = NULL, *nhe = NULL, *te, *pte;

    /* If we have less than 3 nodes, then we are done. */
    if (ncnt < 3)
    {
        rarr[0] = hn->val;
        *rsz = ncnt;
        if (hn->next)
            rarr[1] = hn->next->val;
        return;
    }

    /* Seek leaf nodes. */
    while (n)
    {
        /* If the degree is one, then find the corresponding edge and
        delete. */
        if (degree[n->val] == 1)
        {
            /* Run through the list looking for that one edge. */
            te = he;
            pte = NULL;
            while (te && te->n[0] != n->val && te->n[1] != n->val) {
                pte = te;
                te = te->next;
            }

            /* Delete the selected node and edge. */
            if (pn) pn->next = n->next;
            else hn = n->next;

            if (pte) pte->next = te->next;
            else he = te->next;


            /* Add the edge to the leaf node edge list. This will be used
            to update the degree. */
            if (!nh)
                nhe = nh = te;
            else {
                nhe->next = te;
                nhe = te;
            }
            ncnt--;
        }
        /* Set the previous node only if there was no change in list. */
        else
            pn = n;
        /* Move to the next node. */
        n = n->next;
    }

    /* Update the degree of nodes connected by the deleted edges. */
    nhe->next = NULL;
    te = nh;
    while (te)
    {
        degree[te->n[0]]--;
        degree[te->n[1]]--;
        te = te->next;
    }

    /* Delete the next set of leaf nodes. */
    RemoveLeaf(hn, he, ncnt, degree, rarr, rsz);
}

/***********************************************************************/
/* For a undirected graph with tree characteristics, we can choose any */
/* node as the root. The result graph is then a rooted tree. Among all */
/* possible rooted trees, those with minimum height are called minimum */
/* height trees (MHTs). Given such a graph, write a function to find   */
/* all the MHTs and return a list of their root labels.                */
/* Format                                                              */
/* The graph contains n nodes which are labeled from 0 to n - 1. You   */
/* will be given the number n and a list of undirected edges (each edge*/
/* is a pair of labels).                                               */
/* You can assume that no duplicate edges will appear in edges. Since  */
/* all edges are undirected, [0, 1] is the same as [1, 0] and thus     */
/* will not appear together in edges.                                  */
/***********************************************************************/
int* findMinHeightTrees(int n, int** e, int rsz, int csz, int* retsz)
{
    int i;
    int *arr, *rarr;
    struct node *nh = NULL;
    struct edge *eh = NULL;

    /* Validate the parameters. */
    if (n < 1 || rsz < 0 || !retsz)
        return NULL;
    *retsz = 0;

    /* Allocate space to store the degree of each node. */
    if (!(rarr = calloc(n + 2, sizeof(int))))
        goto __exit;
    arr = &rarr[2];

    /* Allocate space to store the nodes and edges in linked list. */
    if (!(nh = malloc((sizeof(struct node) * n) +
                      (sizeof(struct edge) * rsz))))
        goto __exit;
    eh = (struct edge *)&nh[n];

    /* Generate the nodes. */
    for (i = 0; i < n - 1; ++i)
    {
        nh[i].next = &nh[i + 1];
        nh[i].val = i;
    }
    nh[i].next = NULL;
    nh[i].val = i;

    /* Generate the edges. */
    for (i = 0; i < rsz && e; ++i)
    {
        /* Increment the degree. */
        arr[(e[i])[0]]++;
        arr[(e[i])[1]]++;
        eh[i].n = e[i];
        if (i < n - 1)
            eh[i].next = &eh[i + 1];
        else eh[i].next = NULL;
    }

    /* Strip the list. */
    RemoveLeaf(nh, eh, n, arr, rarr, retsz);

    /* Free the list and return the array. */
__exit:
    if (nh) free(nh);
    return rarr;
}
#else
/*******************************/
/* Data Structures             */
/*******************************/
struct node
{
    int val;
    struct node *next;
};

/***********************************************************************/
/* gdfs: Run DFS and return the farthest node!                         */
/*                                                                     */
/***********************************************************************/
void gdfs(int n, struct node **list, int *max_node, int *stack, int ssz,
          int *nodes, int *retsz, unsigned char *map, int *max_path)
{
    struct node *np;

    /* Return if the node is in the stack. */
    if (map[n])
        return;

    /* Set the map to avoid looping back (undirected graph). */
    map[n] = 1;
    stack[ssz] = n;

    /* If needed, update the maximum path and the center nodes. */
    if (*max_path < ssz + 1)
    {
        *max_path = ssz + 1;
        *retsz = 0;
        nodes[(*retsz)++] = stack[ssz / 2];

        /* If the length is odd, then we have two possible nodes. */
        if (ssz & 1)
            nodes[(*retsz)++] = stack[ssz / 2 + 1];
        *max_node = n;
    }

    /* Loop visiting all the neighbors. */
    for (np = list[n]; np; np = np->next)
        gdfs(np->val, list, max_node, stack, ssz + 1, nodes, retsz, map,
             max_path);
}

/***********************************************************************/
/* For a undirected graph with tree characteristics, we can choose any */
/* node as the root. The result graph is then a rooted tree. Among all */
/* possible rooted trees, those with minimum height are called minimum */
/* height trees (MHTs). Given such a graph, write a function to find   */
/* all the MHTs and return a list of their root labels.                */
/* Format                                                              */
/* The graph contains n nodes which are labeled from 0 to n - 1. You   */
/* will be given the number n and a list of undirected edges (each edge*/
/* is a pair of labels).                                               */
/* You can assume that no duplicate edges will appear in edges. Since  */
/* all edges are undirected, [0, 1] is the same as [1, 0] and thus     */
/* will not appear together in edges.                                  */
/***********************************************************************/
int* findMinHeightTrees(int n, int** e, int rsz, int csz, int* retsz)
{
    struct node *np;
    struct node **list;
    unsigned char *map;
    int i, max_node, max_path = 0;
    int *stack;
    int retarr[2];


    /* Validate the parameters. */
    if (n < 1 || rsz < 0 || !retsz)
        return NULL;
    *retsz = 0;

    /* Allocate nodes for adjacency list. Two nodes for each edge. */
    if (!(stack = malloc(sizeof(int) * n)))
        return NULL;
    if (!(np = malloc((sizeof(struct node) * (rsz << 1)) +
                      (sizeof(struct node *) * n) +
                      (sizeof(unsigned char) * n))))
    {
        free(stack);
        return NULL;
    }
    list = (struct node **)&np[rsz << 1];
    map = (unsigned char*)&list[n];
    memset(list, 0, (sizeof(struct node *) + sizeof(unsigned char)) * n);

    /* Generate the adjacency list. */
    for (i = 0; i < rsz; ++i)
    {
        /* Assign the node values. */
        np[i * 2].val = (e[i])[0];
        np[i * 2 + 1].val = (e[i])[1];

        /* Assign the nodes as neighbors. */
        np[i * 2].next = list[np[i * 2 + 1].val];
        list[np[i * 2 + 1].val] = &np[i * 2];
        np[i * 2 + 1].next = list[np[i * 2].val];
        list[np[i * 2].val] = &np[i * 2 + 1];
    }

    /* Pick an arbitrary node and run DFS to find the farthest node. */
    gdfs(0, list, &max_node, stack, 0, retarr, retsz, map, &max_path);

    /* Run DFS from this farthest node and find the max path. */
    max_path = 0;
    memset(map, 0, n);
    gdfs(max_node, list, &max_node, stack, 0, retarr, retsz, map, &max_path);

    stack[0] = retarr[0];
    if (*retsz > 1)
        stack[1] = retarr[1];
    free(np);
    return stack;
}
#endif

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
#if 0
    int n = 4;
    int e1[] = {1, 0}, e2[] = {1, 2}, e3[] = {1, 3};
    int *e[] = {e1, e2, e3};
#elif 0
    int n = 6;
    int e1[] = {0, 3}, e2[] = {1, 3}, e3[] = {2, 3}, e4[] = {4, 3};
    int e5[] = {5, 4};
    int *e[] = {e1, e2, e3, e4, e5};
    int rsz = sizeof(e) / sizeof(int *), csz = sizeof(e1) / sizeof(int);
#elif 1
    int n = 1;
    int *e[] = {};
    int rsz = 0, csz = 0;
#endif
    int *arr;
    int ret, i;
    arr = findMinHeightTrees(n, e, rsz, csz, &ret);
    for (i = 0; i < ret; ++i)
        printf("%d:\n", arr[i]);
    free(arr);
    return 0;
}
