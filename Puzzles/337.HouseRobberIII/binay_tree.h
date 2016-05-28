/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/

/********************************/
/* Linked list NODE             */
/********************************/
struct node
{
    int val;
    struct node *right;
    struct node *left;
};

/********************************/
/* Function Prototypes          */
/********************************/
void free_tree(struct node *root);
struct node *generate_tree(int *a, int start, int end);
