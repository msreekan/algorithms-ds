/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __TRIE_H__
#define __TRIE_H__

/********************************************/
/* Function Prototypes                      */
/********************************************/
int DeleteLenTrie(void *handle, void *n, char *str, int len);
void *SearchLenTrie(void *handle, void *n, char *str, int len,
                    int *status);
int AddToTrie(void *handle, char *str);
void *InitTrie(void);
void FreeTrie(void *handle);
int UndoDelLenTrie(void *handle, void *n, char *str, int len);
#endif // __TRIE_H__
