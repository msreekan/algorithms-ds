/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***********************************************************************/
/* Implement the following operations of a stack using queues.         */
/* push(x) -- Push element x onto stack.                               */
/* pop() -- Removes the element on top of the stack.                   */
/* top() -- Get the top element.                                       */
/* empty() -- Return whether the stack is empty.                       */
/* Notes:                                                              */
/*                                                                     */
/* You must use only standard operations of a queue -- which means only*/
/* push to back, peek/pop from front, size, and is empty operations are*/
/* valid.                                                              */
/*                                                                     */
/* Depending on your language, queue may not be supported natively. You*/
/* may simulate a queue by using a list or deque (double-ended queue), */
/* as long as you use only standard operations of a queue.             */
/* You may assume that all operations are valid (for example, no pop or*/
/* top operations will be called on an empty stack).                   */
/***********************************************************************/
typedef struct {
    int *q;    // queue array
    int len;   // length
    int start; // start
    int end;   // end
} MyStack;

/***********************************************************************/
/* myStackCreate: Create the stack!                                    */
/*                                                                     */
/***********************************************************************/
MyStack* myStackCreate(int maxSize)
{
    MyStack *stack;

    /* Allocate the memory. */
    stack = malloc(sizeof(MyStack) + (sizeof(int) * (maxSize + 1)));
    if (!stack)
        return NULL;
    stack->q = (int *)&stack[1];
    stack->len = maxSize + 1;
    stack->start = 0;
    stack->end = 0;
    return stack;
}

/***********************************************************************/
/* myStackPush: Stack push!                                            */
/*                                                                     */
/***********************************************************************/
void myStackPush(MyStack* q, int x)
{
    int i, qlen;

    /* Ensure there is space. */
    if ((q->end + 1) % q->len == q->start)
        return;

    /* Calcualte the present queue length. */
    qlen = (q->start > q->end) ? q->len - q->start + q->end :
                                 q->end - q->start;

    /* Add the new element, then reverse the order. */
    q->q[q->end] = x;
    q->end = (q->end + 1) % q->len;

    /* Reverse the order of the queue. */
    for (i = 0; i < qlen; ++i)
    {
        q->q[q->end] = q->q[q->start];
        q->end = (q->end + 1) % q->len;
        q->start = (q->start + 1) % q->len;
    }
}

/***********************************************************************/
/* myStackPop: Stack pop!                                              */
/*                                                                     */
/***********************************************************************/
int myStackPop(MyStack* q)
{
    int val = q->q[q->start];
    q->start = (q->start + 1) % q->len;
    return val;
}

/***********************************************************************/
/* myStackTop: Stack top!                                              */
/*                                                                     */
/***********************************************************************/
int myStackTop(MyStack* q)
{
    return q->q[q->start];
}

/***********************************************************************/
/* myStackEmpty: Check whether stack is empty!                         */
/*                                                                     */
/***********************************************************************/
bool myStackEmpty(MyStack* q)
{
    return q->start == q->end ? true : false;
}

/***********************************************************************/
/* myStackFree: Live free!                                             */
/*                                                                     */
/***********************************************************************/
void myStackFree(MyStack* q)
{
    free(q);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int len = 32, i, popval = 0, j;
    MyStack *stack;

    /* Initialize the stack. */
    if (!(stack = myStackCreate(len)))
        return -1;

    /* Add elements to the stack. */
    for (i = 0; i < len; ++i)
    {
        myStackPush(stack, i);
        if ((popval = myStackTop(stack)) != i)
            printf("TOP Error: %d v/s %d \n", i, popval);
    }
    for (j = i - 1; j >= len / 2; --j)
    {
        if ((popval = myStackTop(stack)) != j)
            printf("TOP Error: %d v/s %d \n", j, popval);
        if ((popval = myStackPop(stack)) != j)
            printf("POP Error: %d v/s %d \n", j, popval);
    }

    /* Add elements to the stack. */
    for (i = len / 2; i < len; ++i)
    {
        myStackPush(stack, i);
        if ((popval = myStackTop(stack)) != i)
            printf("TOP Error: %d v/s %d \n", i, popval);
    }

    for (j = i - 1; j >= 0; --j)
    {
        if ((popval = myStackTop(stack)) != j)
            printf("TOP Error: %d v/s %d \n", j, popval);
        if ((popval = myStackPop(stack)) != j)
            printf("POP Error: %d v/s %d \n", j, popval);
    }

    myStackFree(stack);
    return 0;
}
