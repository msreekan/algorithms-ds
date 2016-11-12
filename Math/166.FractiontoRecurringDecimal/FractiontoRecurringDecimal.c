/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Utils/queue.h"
#include "../Utils/hasht.h"
#include "../Utils/generic.h"

/******************************************/
/* Macros                                 */
/******************************************/
#define QUEUE_SZ 1024
#define INT_TO_ASCII(x)  ((x) + 48)

/***********************************************************************/
/* HashGen: Generate an i32 hash from an entry!                        */
/*                                                                     */
/***********************************************************************/
int HashGen(void *ptr1)
{
    unsigned long long *l1 = ptr1;
    return (*l1) & 0x7FFFFFFF;
}

/***********************************************************************/
/* HashCmp: Compare two entries!                                       */
/*                                                                     */
/***********************************************************************/
int HashCmp(void *ptr1, void *ptr2)
{
    unsigned long long *l1 = ptr1, *l2 = ptr2;
    return *l1 == *l2 ? 0 : 1;
}

/***********************************************************************/
/* Given two integers representing the numerator and denominator of a  */
/* fraction, return the fraction in string format.                     */
/*                                                                     */
/* If the fractional part is repeating, enclose the repeating part in  */
/* parentheses.                                                        */
/*                                                                     */
/* For example,                                                        */
/* Given numerator = 1, denominator = 2, return "0.5".                 */
/* Given numerator = 2, denominator = 1, return "2".                   */
/* Given numerator = 2, denominator = 3, return "0.(6)".               */
/***********************************************************************/
char* fractionToDecimal(long numerator, long denominator)
{
    unsigned long long n = llabs(0ULL | numerator);
    unsigned long long d = llabs(0ULL | denominator), r = 0, q = 0;
    int off = 0, sign = 0, st, en, doff, f = 0, count = 0;
    void *hasht = NULL, *fqueue = NULL;
    char *dec = NULL;
    struct ValCount {
        unsigned long long val;
        int count;
    };
    struct ValCount *b = NULL;
    struct ValCount v;

    /* Validate */
    if (!denominator || ((hasht = HashTAlloc(QUEUE_SZ,
          sizeof(struct ValCount), HashGen, HashCmp)) == NULL) ||
        ((fqueue = QueueAlloc(QUEUE_SZ, sizeof(int))) == NULL))
        return NULL;

    /* Figure out the sign */
    if (numerator < 0) sign = 1;
    if (denominator < 0 && n != 0)
        sign = (sign == 0 ) ? 1 : 0;

    /* Get the quotient */
    q = n / d;

    /* Check if there is a remainder */
    while ((r = (n % d)) && b == NULL){

        /* Multiply by 10 */
        n = r * 10ULL;

        /* Search for the value. If the value not present,
        then add it to the hash table. */
        if ((b = HashTSearch(hasht, &n)) == NULL) {
            v.val = n;
            v.count = count++; // counter to track '('
            if (HashTAdd(hasht, &v))
                goto __exit;

            /* Add fraction digit to the queue */
            f = (int)(n / d);
            if (QueueAdd(fqueue, &f))
                goto __exit;
        }
    }

    /* Allocate the return character array */
    dec = malloc(sizeof(char) * (QueueSzGet(fqueue) + 32));
    if (!dec) goto __exit;

    /* If needed, add the sign */
    if (sign) dec[off++] = '-';

    /* Generate the quotient string */
    while (q > 9){
        dec[off++] = INT_TO_ASCII(q % 10);
        q /= 10;
    }
    dec[off++] = INT_TO_ASCII(q % 10);

    /* We need to reverse the quotient string. */
    st = sign;
    en = off - 1;
    while (st < en)
        SwapChars(&dec[en--], &dec[st++]);

    /* If the fraction part is present, then add the same */
    if (QueueSzGet(fqueue)) {

        dec[off++] = '.'; // add decimal point
        doff = off; // save the starting offset of the fraction

        /* Now generate the fractional part */
        while (!QueueDel(fqueue, &f)) {
            if (b && off - doff == b->count) // place braces at the correct offset
                dec[off++] = '(';
            dec[off++] = INT_TO_ASCII(f);
        }

        /* Mark closing braces */
        if (b != NULL)
            dec[off++] = ')';
    }
    dec[off] = 0; // NULL termination
__exit:
    if (hasht) HashTFree(hasht);
    if (fqueue) QueueFree(fqueue);
    return dec;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    long n[] = {1, -1, 2, -2147483648, 1, 1, 0, -50};
    long d[] = {5, -2147483648, 3, -1, 5, 6, -5, 8};
    char *s[] = {"0.2", "0.0000000004656612873077392578125",
                 "0.(6)", "2147483648", "0.2", "0.1(6)", "0", "-6.25"};
    int len = sizeof(n) / sizeof(int), i;
    char *f;
    for (i = 0; i < len; ++i) {
        f = fractionToDecimal(n[i], d[i]);
        if (strcmp(f, s[i]))
            printf("Error : %s v/s %s :\n", f, s[i]);
        free(f);
    }
    return 0;
}
