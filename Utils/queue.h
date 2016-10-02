/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

/********************************************/
/* Function Prototypes                      */
/********************************************/
void *QueueAlloc(unsigned int size, unsigned int esize);
void QueueFree(void *handle);
int QueueAdd(void *handle, void *ptr);
int QueueDel(void *handle, void *ptr);
int QueueEmpty(void *handle);
int QueueSzGet(void *handle);
#endif // __STACK_H__
