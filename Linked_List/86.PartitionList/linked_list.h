/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
/********************************/
/* Linked list NODE             */
/********************************/
struct ListNode
{
      int val;
      struct ListNode *next;
};

/********************************/
/* Function Prototypes          */
/********************************/
void free_list(struct ListNode *s);
void prn_list(struct ListNode *s);
struct ListNode *generate_list(int *a, int len);
