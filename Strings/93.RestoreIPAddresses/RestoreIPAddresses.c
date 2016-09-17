/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************/
/* Macros                             */
/**************************************/
#define MAX_VAL "255"
#define MAX_LEN 3
#define MAX_IP_SZ 2048

/***********************************************************************/
/* max_val: Validate the max value of the string                       */
/*                                                                     */
/***********************************************************************/
int max_val(char *num, char *max, int len)
{
    int i;

    /* Starting with MSB check the values are less than equal to max */
    for (i = 0; i < len && num[i] == max[i]; ++i);

    /* Looks good */
    return (i == len || num[i] <= max[i]) ? 0 : 1;
}

/***********************************************************************/
/* gen_ips: Generate IP addresses!                                     */
/*                                                                     */
/***********************************************************************/
void gen_ips(char *s, int len, char *ts, int tlen, int num, char **ip,
             int *rsize)
{
    int i;

    /* If the character count exceed the slot, return */
    if ((num * 3 < len) || (num > len))
        return;

    /* If we have finished generating an IP, then save the same */
    if (num == 0)
    {
        ip[*rsize] = malloc(sizeof(char) * tlen);
        if (!ip[*rsize])
            return;
        ts[tlen - 1] = 0;
        memcpy(ip[*rsize], ts, tlen);
        (*rsize) += 1;
        return;
    }

    /* Generate various values for this location */
    for (i = 0; i < MAX_LEN && i < len; ++i)
    {
        ts[tlen + i] = s[i];

        /* We cannot exceed the max value for a unit */
        if (((i > 0) && (*s == '0')) ||
            ((i == MAX_LEN - 1) && max_val(&ts[tlen], MAX_VAL, MAX_LEN)))
            break;

        /* Append '.' and proceed to generate more sequences */
        ts[tlen + i + 1] = '.';
        gen_ips(s + i + 1, len - i - 1, ts, tlen + i + 2, num - 1, ip,
                rsize);
    }
}

/***********************************************************************/
/* Given a string containing only digits, restore it by returning all  */
/* possible valid IP address combinations.                             */
/*                                                                     */
/* For example:                                                        */
/*  Given "25525511135",                                               */
/*                                                                     */
/* return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)*/
/***********************************************************************/
char** restoreIpAddresses(char* s, int *rsize)
{
    int slen = strlen(s), num = 4;
    char **ip;
    char *ts;

    /* Allocate memory for IP array and initialize return size */
    ip = malloc((sizeof(char *) * MAX_IP_SZ) +
                (sizeof(char) * (slen + num + 1)));
    if (!ip)
        return NULL;
    ts = (char *)(ip + MAX_IP_SZ);
    *rsize = 0;

    /* Generate IPs */
    gen_ips(s, slen, ts, 0, num, ip, rsize);

    /* Return the list */
    return ip;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char s[] = "2552551553";
    char **ip;
    int rsize, i;

    ip = restoreIpAddresses(s, &rsize);

    /* Print the IPs */
    for (i = 0; i < rsize; ++i)
    {
        printf("%s\n", ip[i]);
        free(ip[i]);
    }
    free(ip);
    return 0;
}
