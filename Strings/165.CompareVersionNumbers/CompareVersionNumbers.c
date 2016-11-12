/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************/
/* Compare two version numbers version1 and version2.                  */
/* If version1 > version2 return 1, if version1 < version2 return -1,  */
/* otherwise return 0.                                                 */
/*                                                                     */
/* You may assume that the version strings are non-empty and contain   */
/* only digits and the . character.                                    */
/* The . character does not represent a decimal point and is used to   */
/* separate number sequences.                                          */
/* For instance, 2.5 is not "two and a half" or "half way to version   */
/* three", it is the fifth second-level revision of the second         */
/* first-level revision.                                               */
/*                                                                     */
/* Here is an example of version numbers ordering:                     */
/*                                                                     */
/* 0.1 < 1.1 < 1.2 < 13.37                                             */
/***********************************************************************/
int compareVersion(char* version1, char* version2)
{
    char *v1 = version1, *v2 = version2, *tv1, *tv2;
    int dv1 = 0, dv2 = 0;

    /* Validate the input */
    if (!v1 || !v2 || (*v1 == 0 && *v2 == 0))
        return 0;

    /* Skip the leading zeros. */
    while (*v1 == '0') v1++;
    while (*v2 == '0') v2++;
    tv1 = v1;
    tv2 = v2;

    /* Find the length of the numeral sequeuence */
    while (*v1 != '.' && *v1 != 0) {
        v1++;
        dv1++;
    }

    /* Find the length of the numeral sequence */
    while (*v2 != '.' && *v2 != 0) {
        v2++;
        dv2++;
    }

    /* If one of them is larger, then that is higher */
    if (dv1 < dv2) return -1;
    else if (dv1 > dv2) return 1;

    /* If they are same, then compare the contents */
    v1 = tv1;
    v2 = tv2;
    while (*v1 == *v2 && *v1 != '.' && *v1 != 0) {
        v1++;
        v2++;
    }

    /* The greater numeral value reflects the greater version */
    if (*v1 && *v2 && *v1 > *v2) return 1;
    else if (*v1 && *v2 && *v1 < *v2) return -1;

    /* Skip any trailing '.' */
    if (*v1 == '.') v1++;
    if (*v2 == '.') v2++;

    /* Recursively parse the next version numeral sequence. */
    return compareVersion(v1, v2);
}

/***********************************************************************/
/* main: Entry point                                                   */
/*                                                                     */
/***********************************************************************/
int main()
{
    char v1[] = "1.1", v2[] = "1.1";
    //char v1[] = "01.10", v2[] = "1.010";
    //char v1[] = "0.1", v2[] = "0.0.1";
    //char v1[] = "1.0", v2[] = "1";
    printf("Compare Version %d", compareVersion(v1, v2));
    return 0;
}
