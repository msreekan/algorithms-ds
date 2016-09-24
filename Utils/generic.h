/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#ifndef __GENERIC_H__
#define __GENERIC_H__

/********************************************/
/* Macros                                   */
/********************************************/
#define INT_SWAP(a, b) {\
                        int temp = *(a);\
                        *(a) = *(b);\
                        *(b) = temp;\
                        }

/********************************************/
/* Function Prototypes                      */
/********************************************/
void PrintArray(int *arr, int len);
#endif // __GENERIC_H__
