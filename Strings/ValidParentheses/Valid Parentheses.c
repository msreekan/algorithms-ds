/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************/
/* Expression STACK             */
/********************************/
struct estack
{
    char *ch;
    int top;
    int sz;
};

/***********************************************************************/
/* spush: Stack push                                                   */
/*                                                                     */
/***********************************************************************/
void spush(struct estack *s, char ch)
{
    /* Memory constraints! */
    if(s->top == s->sz)
        exit(-1);
    s->ch[s->top] = ch;
    s->top++;
}

/***********************************************************************/
/* spop: Stack pop                                                     */
/*                                                                     */
/***********************************************************************/
char spop(struct estack *s)
{
    /* Refusal to POP */
    if(s->top == 0)
        return '\0';
    s->top--;
    return s->ch[s->top];
}

/***********************************************************************/
/* get_top: Get the stack top                                          */
/*                                                                     */
/***********************************************************************/
int get_top(struct estack *s)
{
    return s->top;
}

/***********************************************************************/
/* get_sz: Get stack size                                              */
/*                                                                     */
/***********************************************************************/
int get_sz(struct estack *s)
{
    return s->sz;
}

/***********************************************************************/
/* check_exp: Evaluate the expression                                  */
/*                                                                     */
/***********************************************************************/
int check_exp(char *ch, struct estack *s)
{
    char c;

    /* No elements left in the expression ? */
    if (*ch == '\0')
    {
        /* If we have open parentheses, stack would pop. */
        c = spop(s);

        /* Return error if there were braces left in the stack */
        if (c != '\0')
            return 0;
        else
            return 1;
    }

    /* Open braces */
    else if ((*ch == '(') || (*ch == '[') || (*ch == '{'))
    {
        /* Push to the stack */
        spush(s, *ch);

        /* If more than half of the stack is already filled,
           then this parsing is not going to end well, return error */
        if (get_top(s) > ((get_sz(s) + 1) / 2))
            return 0;

        /* Continue parsing */
        return check_exp(ch + 1, s);
    }

    /* Else it's closing braces, pop and check */
    else if ((*ch == ')') || (*ch == ']') || (*ch == '}'))
    {
        char c;

        /* Stack not returning matching braces is error */
        c = spop(s);
        if ((*ch == ')') && (c != '('))
            return 0;
        else if ((*ch == ']') && (c != '['))
            return 0;
        else if ((*ch == '}') && (c != '{'))
            return 0;
        else
            return check_exp(ch + 1, s);
    }

    /* Should not happen */
    return 0;
}

/***********************************************************************/
/* Given a string containing just the characters '(', ')', '{', '}',   */
/* '[' and ']', determine if the input string is valid.                */
/*                                                                     */
/* The brackets must close in the correct order, "()" and "()[]{}"     */
/* are all valid but "(]" and "([)]" are not.                          */
/*                                                                     */
/***********************************************************************/
int isValid(char* s)
{
    struct estack es = {NULL, 0, 0};

    /* Allocate the stack and call the expression checker */
    es.sz = strlen(s) + 1;
    es.ch = malloc(es.sz);
    return check_exp(s, &es);
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char ch1[] = "()";
    char ch2[] = "()[]{}";
    char ch3[] = "(]";
    char ch4[] = "([)]";

    printf("Validity of %s = %d:\n", ch1, isValid(ch1));
    printf("Validity of %s = %d:\n", ch2, isValid(ch2));
    printf("Validity of %s = %d:\n", ch3, isValid(ch3));
    printf("Validity of %s = %d:\n", ch4, isValid(ch4));
    return 0;
}

