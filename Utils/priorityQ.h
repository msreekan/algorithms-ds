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
void *PQAlloc(int len, int esize, int (*pcb)(void *));
int AddToPQ(void *handle, void *buf);
int GetPQArr(void *handle, void **arr);
void FreePQ(void *handle);
#endif // __STACK_H__
