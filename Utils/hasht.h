/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __HASHT_H__
#define __HASHT_H__

/********************************************/
/* Function Prototypes                      */
/********************************************/
void *HashTAlloc(unsigned int size, unsigned int esize,
                 int (*hash_fn)(void *), int (*cmp_fn)(void *, void *));
void HashTFree(void *handle);
int HashTAdd(void *handle, void *ptr);
int HashTDelete(void *handle, void *ptr);
void *HashTSearch(void *handle, void *ptr);
#endif // __HASHT_H__
