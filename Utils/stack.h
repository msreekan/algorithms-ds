/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __STACK_H__
#define __STACK_H__

/********************************************/
/* Function Prototypes                      */
/********************************************/
void *StackAlloc(unsigned int, unsigned int );
void StackFree(void *);
int StackPush(void *, void *);
int StackPop(void *, void *);
int StackEmpty(void *handle);
#endif // __STACK_H__
