#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************/
/* scmp : Compare sub-strings                                          */
/*                                                                     */
/***********************************************************************/
int scmp(char *a, char *b, int n)
{
    int i;
    for (i = 0; i < n; ++i)
        if (a[i] != b[i])
            return 1;
    return 0;
}

/***********************************************************************/
/* Given an absolute path for a file (Unix-style), simplify it.        */
/*                                                                     */
/* For example,                                                        */
/* path = "/home/", => "/home"                                         */
/* path = "/a/./b/../../c/", => "/c"                                   */
/***********************************************************************/
char* simplifyPath(char* path)
{
    int soff = 0, poff = 0;

    /* Scan the path */
    while (path[poff] != 0)
    {
        /* Handle parent directory indirections */
        if (!scmp(&path[poff], "../", 3) ||
            !scmp(&path[poff], "..", 3))
        {
            /* Rewind to the parent directory only if we are not in root */
            while (soff > 1 && soff-- && path[soff] != '/');
            while (soff > 1 && soff-- && path[soff] != '/');
            poff += 2;
        }

        /* Handle the "..." */
        else if (!scmp(&path[poff], "...", 3))
        {
            poff += 3;
            soff += 3;
        }

        /* Ignore "." and consecutive slashes "//" */
        else if ((!scmp(&path[poff], "./", 2) ||
                  !scmp(&path[poff], ".", 2)) ||
                ((path[poff] == '/') && soff > 0 &&
                 (path[soff - 1] == '/')))
            poff++;

        /* Else simply move to the next character */
        else
            path[soff++] = path[poff++];
    }

    /* Handle the ending "/" */
    soff = (soff > 1 && path[soff - 1] == '/') ? soff - 1 : soff;
    path[soff] = 0; // Null terminate */
    return path;
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    char p1[] = "/home/", p2[] = "/a//.//b//../../c/", p3[] = "/";
    char p4[] = "/home//foo/", p5[] = "/...", p6[] = "/..hidden";
    char p7[] = "/.", p8[] = "/..", p9[] = "/home/../../..";
    char p10[] = "/..";
    char *p[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10};
    int len = sizeof(p) / sizeof(char *), i;
    char *s;
    for (i = 0; i < len; ++i)
    {
        printf("%s = ", p[i]);
        s = simplifyPath(p[i]);
        printf("%s\n", s);
        free(s);
    }
    return 0;
}
