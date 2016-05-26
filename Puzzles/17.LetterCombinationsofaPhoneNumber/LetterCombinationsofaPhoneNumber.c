/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 16 // Size of the stack

/************************/
/* Stack Data Structure */
/************************/
struct stack
{
    char s[STACK_SIZE];
    int top;
};

/***********************************************************************/
/* cpush: Stack push                                                   */
/*                                                                     */
/***********************************************************************/
int cpush(struct stack *s, char ch)
{
    /* Cannot go beyond the stack size */
    if (s->top == STACK_SIZE)
        return -1;

    /* Push to the stack */
    s->s[s->top] = ch;
    s->top++;
    return 0;
}

/***********************************************************************/
/* cpop: Stack pop                                                     */
/*                                                                     */
/***********************************************************************/
int cpop(struct stack *s)
{
    /* Empty stacks won't pop */
    if (s->top == 0)
        return -1;
    s->top--;
    return 0;
}

/***********************************************************************/
/* cget_top: Get top                                                   */
/*                                                                     */
/***********************************************************************/
int cget_top(struct stack *s)
{
    return s->top;
}

/***********************************************************************/
/* cget: Return the stack base                                         */
/*                                                                     */
/***********************************************************************/
char *cget(struct stack *s)
{
    /* Cannot exceed the allocated size */
    if (s->top == STACK_SIZE)
        return NULL;

    s->s[s->top] = '\0';
    return s->s;
}

/***********************************************************************/
/* get_num: ASCII Character to number conversion                       */
/*                                                                     */
/***********************************************************************/
int get_num(char ch)
{
    if ((ch > 57) || (ch < 50))
        return -1;
    else
        return ch - 48;
}

/***********************************************************************/
/* generate_combos: Recursive function to generate various combinations*/
/*                                                                     */
/***********************************************************************/
int generate_combos(char **dcombos, char **combos, int *num_arr,
                    int num_offst, int num_arr_sz, int *combo_offst,
                    struct stack *s)
{
    int i = 0;
    char *str = NULL;

    /* We have finished generating one combination */
    if (num_offst == num_arr_sz)
    {
        char *str = cget(s);
        int len;

        /* Ensure sanity */
        if (str == NULL)
            return -1;

        /* Get the size of the combination */
        len = cget_top(s);

        /* Allocate memory */
        combos[*combo_offst] = malloc(sizeof(char) * (len + 1));
        if (!combos[*combo_offst])
            return -1;

        /* Store the combination */
        memcpy(combos[*combo_offst], str, len);

        /* NULL termination and offset increment winds up this
           instance */
        combos[*combo_offst][len] = '\0';
        *combo_offst += 1;
        return 0;
    }

    /* Get the string associated with this number */
    str = dcombos[num_arr[num_offst] - 2];

    /* Main loop which generates the combinations */
    while (str[i] != '\0')
    {
        /* Push the character on to the stack */
        if (cpush(s, str[i]))
            return -1;

        /* Generate the combinations for the remaining digits of the phone number */
        if (generate_combos(dcombos, combos, num_arr, num_offst + 1, num_arr_sz,
                            combo_offst, s))
            return -1;

        /* Pop the character and move on to the next one */
        if (cpop(s))
            return -1;
        ++i;
    }

    /* We are done */
    return 0;
}

/************************************************************************/
/* Given a digit string, return all possible letter combinations that   */
/* the number could represent on a telephone.                           */
/*                                                                      */
/* URL :                                                                */
/* https://leetcode.com/problems/letter-combinations-of-a-phone-number/ */
/*                                                                      */
/************************************************************************/
char** letterCombinations(char* digits, int* returnSize)
{

    /*
    ** dcombos -- digit letter combinations represents the number to the
    ** character mapping. For example : 2 maps to "abc", 3 to "def" on
    ** a phone
    */
    //                 2     3      4      5       6      7       8      9
    char *dcombos[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int cnum[9] =      { 3,     3,     3,     3,     3,     4,      3,     4};
    int i = 0, count = 1, combo_offst = 0, num_arr_sz = 0;
    char **combos = NULL;
    int num_arr[STACK_SIZE] = {0};
    struct stack s = {{0}, 0};

    /* Ensure peace */
    if ((!digits) || (digits[0] == '\0'))
        return NULL;

    /* Loop to figure out the total number of letter combinations associated
       with the number */
    while (digits[i] != '\0')
    {
        int num = get_num(digits[i]); // convert character to integer

        /* Multiply to generate the combination count */
        if ((num != -1) && (i < STACK_SIZE))
            count *= cnum[num - 2];
        else
            return NULL;

        /* Record the integer array */
        num_arr[i] = num;
        ++i;
    }

    /* Numbers of digits in the number */
    num_arr_sz = i;
    if (count < 3)
        return NULL;

    /* Total number of letter combinations in the array */
    combos = malloc(sizeof(char *) * count);
    if (!combos)
        return NULL;

    /* Combinations are generated by sequentially pushing characters
       from the string to the stack and then finally copying it to the
       output array */
    if (generate_combos(dcombos, combos, num_arr, 0, num_arr_sz, &combo_offst, &s))
        free(combos);

    /* Set return size and return array */
    *returnSize = combo_offst;
    return combos;
}

/***********************************************************************/
/* prn_combos: Print and free the combos                               */
/*                                                                     */
/***********************************************************************/
void prn_combos(char **combos, int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        printf("%s \n", combos[i]);
        free(combos[i]);
    }
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char **combos;
    int combo_sz = 0;
    combos = letterCombinations("234", &combo_sz);
    if (combos)
    {
        prn_combos(combos, combo_sz);
        free(combos);
    }
    return 0;
}

