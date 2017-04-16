/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************/
/* Macros.                         */
/***********************************/
#define MAX_STACK 1024
#define PRN_ERR() printf("%s %d : \n", __func__, __LINE__)

/***********************************/
/* Stack Data Structure.           */
/***********************************/
typedef struct
{
    int *stack;
    int top;
    int minindex;
    int sz;
} MinStack;

/***********************************************************************/
/* minStackCreate: Allocate the stack.                                 */
/***********************************************************************/
MinStack* minStackCreate(int maxSize)
{
    MinStack *mstack;

    /* Allocate the stack structure and the array. */
    mstack = malloc(sizeof(MinStack) + (maxSize * sizeof(int)));
    if (!mstack)
        return NULL;

    /* Initialize the stack. */
    mstack->sz = maxSize;
    mstack->stack = (int *)(mstack + 1);
    mstack->minindex = -1; // invalid
    mstack->top = 0;

    /* Return the pointer. */
    return mstack;
}

/***********************************************************************/
/* minStackPush: Stack push.                                           */
/***********************************************************************/
void minStackPush(MinStack* obj, int x)
{
    /* Validate the inputs. */
    if (!obj || obj->sz == obj->top)
        return;

    /* Push the element into the stack. */
    obj->stack[obj->top] = x;

    /* If this is the new smallest element, then assign the same. */
    if (obj->minindex != -1 && x < obj->stack[obj->minindex])
        obj->minindex = obj->top;

    /* Update the top. */
    obj->top++;
}

/***********************************************************************/
/* minStackPop: Stack pop.                                             */
/***********************************************************************/
void minStackPop(MinStack* obj)
{
    /* Validate the inputs. */
    if (!obj || obj->top == 0)
        return;

    /* Decrement the top. */
    obj->top--;

    /* If the element is the present minimum, then reset the same. */
    if (obj->top == obj->minindex)
        obj->minindex = -1;
}

/***********************************************************************/
/* minStackTop: Get the Stack top.                                     */
/***********************************************************************/
int minStackTop(MinStack* obj)
{
    /* Validate the inputs and return the top. */
    if (!obj || obj->top == 0)
        return - 1;
    return obj->stack[obj->top - 1];
}

/***********************************************************************/
/* minStackGetMin: Get the minimum from the stack.                     */
/***********************************************************************/
int minStackGetMin(MinStack* obj)
{
    /* Validate the inputs. */
    if (!obj || obj->top == 0)
        return -1;

    /* If the minimum value is valid, then return the same. */
    if (obj->minindex != -1)
        return obj->stack[obj->minindex];
    /* Else we need to seek the minimum. */
    else
    {
        int i;

        /* Loop seeking the minimum value. */
        for (i = 0; i < obj->top; ++i)
            if (obj->minindex == -1 ||
                obj->stack[i] < obj->stack[obj->minindex])
                obj->minindex = i;
    }

    /* Return the minimum. */
    return obj->stack[obj->minindex];
}

/***********************************************************************/
/* minStackFree: Free the stack.                                       */
/***********************************************************************/
void minStackFree(MinStack* obj) {
    if (!obj)
        free(obj); // live free
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    void *stack = minStackCreate(MAX_STACK);

    /* Push. */
    minStackPush(stack, -10);
    minStackPush(stack, 14);

    /* Get the minimum, verify. */
    if (minStackGetMin(stack) != -10)
        PRN_ERR();

    /* Get the minimum, verify. */
    if (minStackGetMin(stack) != -10)
        PRN_ERR();

    minStackPush(stack, -20);

    /* Get the minimum, verify. */
    if (minStackGetMin(stack) != -20)
        PRN_ERR();

    /* Get the minimum, verify. */
    if (minStackGetMin(stack) != -20)
        PRN_ERR();

    /* Get the top, verify. */
    if (minStackTop(stack) != -20)
        PRN_ERR();

    /* Get the minimum, verify. */
    if (minStackGetMin(stack) != -20)
        PRN_ERR();

    /* Pop and push. */
    minStackPop(stack);
    minStackPush(stack, -10);
    minStackPush(stack, -7);

    /* Get the minimum and top, verify. */
    if (minStackGetMin(stack) != -10)
        PRN_ERR();
    minStackPush(stack, 10);
    minStackPush(stack, -7);

    /* Get the minimum and top, verify. */
    if (minStackGetMin(stack) != -10 || minStackTop(stack) != -7)
        PRN_ERR();

    /* Pop the min*/
    minStackPop(stack);

    /* Get the minimum and top, verify. */
    if (minStackGetMin(stack) != -10 || minStackTop(stack) != 10)
        PRN_ERR();
    return 0;
}
