/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/hasht.h"
#include "../Utils/queue.h"

/*********************************/
/* Macros                        */
/*********************************/
#define MAX_NODES 8192

/*********************************/
/* Graph Node                    */
/*********************************/
#define NEIGHBORS_MAX_SIZE 100
struct UndirectedGraphNode
{
    int label;
    struct UndirectedGraphNode *neighbors[NEIGHBORS_MAX_SIZE];
    int neighborsCount;
};

/***********************************************************************/
/* HashFn: Generate a hash for the entry!                              */
/*                                                                     */
/***********************************************************************/
int HashFn(void *entry)
{
    return (int)*(struct UndirectedGraphNode **)entry; // address
}

/***********************************************************************/
/* HashCmp: Hash comparison for the entry                              */
/*                                                                     */
/***********************************************************************/
int HashCmp(void *ptr, void *entry)
{
    /* Return 0 if the contents are same */
    return *(struct UndirectedGraphNode **)entry ==
           *(struct UndirectedGraphNode **)ptr ? 0 : 1;
}

/***********************************************************************/
/* Clone Graph                                                         */
/***********************************************************************/
struct UndirectedGraphNode *cloneGraph(struct UndirectedGraphNode *graph)
{
    void *hasht, *queue;
    struct UndirectedGraphNode *cgraph = NULL, *tcgraph[2], **cgarr1;
    struct UndirectedGraphNode *tcgraph2[2], **cgarr2;
    int i;

    /* Validate the parameter */
    if (!graph)
        return NULL;

    /* Allocate hash table and queue */
    if ((hasht = HashTAlloc((MAX_NODES / 16) + 1, sizeof(struct
                 UndirectedGraphNode *) * 2, HashFn, HashCmp)) == NULL ||
        (queue = QueueAlloc(MAX_NODES,  sizeof(struct
                 UndirectedGraphNode *))) == NULL)
        goto __exit;

    /* Clone the starting node, add it to the queue & hash table. */
    tcgraph[0] = graph;
    if (!(tcgraph[1] = malloc(sizeof(struct UndirectedGraphNode))))
        goto __exit;
    if (QueueAdd(queue, &tcgraph[0]) || HashTAdd(hasht, &tcgraph))
        goto __exit;
    tcgraph[1]->label = tcgraph[0]->label;
    tcgraph[1]->neighborsCount = tcgraph[0]->neighborsCount;

    /* BFS traversal of the graph */
    while (!QueueEmpty(queue))
    {
        /* Get the graph node, it as to be present in the hash table */
        if (QueueDel(queue, &tcgraph[0]) ||
            !(cgarr1 = HashTSearch(hasht, &tcgraph[0])))
            goto __exit;

        /* Clone and add the neighbors to the queue if they are not in
           hash table */
        tcgraph[1] = cgarr1[1];
        for (i = 0; i < tcgraph[0]->neighborsCount; ++i) {
            if (!(cgarr2 = HashTSearch(hasht, &tcgraph[0]->neighbors[i])))
            {
                /* Create clone */
                tcgraph2[0] = tcgraph[0]->neighbors[i];
                if (!(tcgraph2[1] = malloc(sizeof(struct UndirectedGraphNode))) ||
                     (QueueAdd(queue, &tcgraph2[0]) || HashTAdd(hasht, &tcgraph2)))
                    goto __exit;
                tcgraph2[1]->label = tcgraph[0]->neighbors[i]->label;
                tcgraph2[1]->neighborsCount = tcgraph[0]->neighbors[i]->neighborsCount;
                tcgraph[1]->neighbors[i] = tcgraph2[1]; // clone memory
            }
            else
                tcgraph[1]->neighbors[i] = cgarr2[1]; // clone memory
        }
    }

    /* Assign the starting node */
    cgarr1 = HashTSearch(hasht, &graph);
    cgraph = cgarr1[1];
__exit:
    if (hasht) HashTFree(hasht); // live free
    if (queue) QueueFree(queue);
    return cgraph;
}

/***********************************************************************/
/* PrintGraph: Print the graph!                                        */
/*                                                                     */
/***********************************************************************/
void PrintGraph(struct UndirectedGraphNode *graph)
{
    void *queue, *hasht;
    struct UndirectedGraphNode *gnode;
    int i;

    /* Allocate queue and the hash table */
    if (!(queue = QueueAlloc(MAX_NODES, sizeof(struct
          UndirectedGraphNode *))) ||
        !(hasht = HashTAlloc((MAX_NODES / 16) + 1, sizeof(struct
          UndirectedGraphNode *), HashFn, HashCmp)))
        goto __exit;

    /* Add the starting node */
    if (QueueAdd(queue, &graph) || HashTAdd(hasht, &gnode))
        goto __exit;

    /* BFS */
    while (!QueueEmpty(queue))
    {
        /* Get the node */
        if (QueueDel(queue, &gnode))
            goto __exit;

        /* Print the value and the neighbors */
        printf("%d : ", gnode->label);
        for (i = 0; i < gnode->neighborsCount; ++i) {
            /* Add the neighbor if it's not already in the queue. */
            if (!HashTSearch(hasht, &gnode->neighbors[i]) &&
                (HashTAdd(hasht, &gnode->neighbors[i]) ||
                 QueueAdd(queue, &gnode->neighbors[i])))
                goto __exit;
            printf("%d, ", gnode->neighbors[i]->label);
        }
        printf("\n");
    }

__exit:
    if (queue) QueueFree(queue);
    if (hasht) HashTFree(hasht);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int n1[] = {0, 1, 2};
    int n2[] = {1, 2};
    int n3[] = {2, 2};
    int *n[] = {n1, n2, n3};
    int nghcount[] = {sizeof(n1) / sizeof(int), sizeof(n2) / sizeof(int),
                      sizeof(n3) / sizeof(int)};
    int ncount = sizeof(n) / sizeof(int *), i, j;
    struct UndirectedGraphNode *graph_arr;
    struct UndirectedGraphNode *cgraph;

    /* Allocate the graph node array */
    if (!(graph_arr = malloc(sizeof(struct UndirectedGraphNode) * ncount)))
        return -1;
    /* Generate the graph */
    for (i = 0; i < ncount; ++i)
    {
        graph_arr[i].label = i;
        graph_arr[i].neighborsCount = nghcount[i] - 1;
        for (j = 0; j < graph_arr[i].neighborsCount; ++j)
            graph_arr[i].neighbors[j] = &graph_arr[(n[i])[j + 1]];
    }

    /* Print the graph*/
    PrintGraph(&graph_arr[0]);

    /* Clone the graph */
    cgraph = cloneGraph(&graph_arr[0]);

    /* Print the cloned graph */
    PrintGraph(cgraph);
    return 0;
}
