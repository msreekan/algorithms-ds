/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/********************************************/
/* Stack data structure.                    */
/********************************************/
typedef struct
{
    int *stack;
    int top;
    int size;
} Stack;

/********************************************/
/* Q with stack.                            */
/********************************************/
typedef struct
{
    Stack s1;
    Stack s2;
} MyQueue;

/***********************************************************************/
/* StackPush: Push element x to the stack.                             */
/***********************************************************************/
void StackPush(Stack *s, int val)
{
    /* Ensure there is space. */
    if (s->size == s->top)
        return;
    s->stack[s->top] = val;
    s->top++;
}

/***********************************************************************/
/* StackPop: Pop element from the stack.                               */
/***********************************************************************/
int StackPop(Stack *s, int *val)
{
    /* Ensure stack is not empty. */
    if (!s->top)
        return -1;
    --s->top;
    *val = s->stack[s->top];
    return 0;
}

/***********************************************************************/
/* StackPeek: Peek element from the stack.                             */
/***********************************************************************/
int StackPeek(Stack *s, int *val)
{
    /* Ensure stack is not empty. */
    if (!s->top)
        return -1;
    *val = s->stack[s->top - 1];
    return 0;
}

/***********************************************************************/
/* myQueueCreate: Initialize your data structure here.                 */
/***********************************************************************/
MyQueue* myQueueCreate(int maxSize)
{
    MyQueue *q;

    /* Verify the parameter. */
    if (maxSize < 0)
        return NULL;

    /* Allocate memory. */
    q = malloc(sizeof(MyQueue) + (sizeof(int) * maxSize * 2));
    if (!q)
        return NULL;
    q->s1.stack = (int *)&q[1];
    q->s2.stack = q->s1.stack + maxSize;
    q->s1.top = q->s2.top = 0;
    q->s1.size = q->s2.size = maxSize;
    return q;
}

/***********************************************************************/
/* myQueuePush: Push element x to the back of queue.                   */
/***********************************************************************/
void myQueuePush(MyQueue* q, int x)
{
    int val;

    /* Move all the contents to the second stack. */
    while (!StackPop(&q->s1, &val))
        StackPush(&q->s2, val);

    /* Push the new value to the stack. */
    StackPush(&q->s1, x);

    /* Move back the elements. */
    while (!StackPop(&q->s2, &val))
        StackPush(&q->s1, val);
}

/***********************************************************************/
/* myQueuePop: Removes the element from in front of queue and returns  */
/*             that element.                                           */
/***********************************************************************/
int myQueuePop(MyQueue* q)
{
    int val;
    if (StackPop(&q->s1, &val))
        exit(-1);
    return val;
}

/***********************************************************************/
/* myQueuePeek: Get the front element.                                 */
/***********************************************************************/
int myQueuePeek(MyQueue* q)
{
    int val;
    if (StackPeek(&q->s1, &val))
        exit(-1);
    return val;
}

/***********************************************************************/
/* myQueueEmpty: Returns whether the queue is empty.                   */
/***********************************************************************/
bool myQueueEmpty(MyQueue *q)
{
    int val;
    return StackPeek(&q->s1, &val) ? true : false;
}

/***********************************************************************/
/* myQueueFree: Free the queue.                                        */
/***********************************************************************/
void myQueueFree(MyQueue* q)
{
    free(q);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    int i, sz = 128;
    void *q;

    /* Allocate q. */
    if (!(q = myQueueCreate(sz)))
        return -1;

    /* Add elements to the queue. */
    for (i = 0; i < sz; ++i)
    {
        myQueuePush(q, i);
        if (myQueuePeek(q) != 0)
            return -1;
        if (myQueueEmpty(q))
            return -1;
    }

    /* Remove elements from the queue. */
    for (i = 0; i < sz; ++i)
    {
        if (myQueuePeek(q) != i)
            return -1;
        if (myQueuePop(q) != i)
            return -1;
    }

    /* Ensure the queue is empty. */
    if (!myQueueEmpty(q))
            return -1;
    return 0;
}
