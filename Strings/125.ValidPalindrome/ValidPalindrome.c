/***********************************************************************/
/* Anyone is free to copy, modify, publish, use, compile, sell,        */
/* dismantle, dismember or distribute this software, either in source  */
/* code form or as object code or assembly code, for any purpose,      */
/* commercial or non-commercial, and by any means.                     */
/***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Utils/generic.h"

/***********************************************************************/
/* isRPalindrome: Palindrome recursive check                           */
/*                                                                     */
/***********************************************************************/
bool isRPalindrome(char *s1, char *s2)
{
    return  (s1 >= s2) ? true : (toLower(*s1) == toLower(*s2)) ?
            isRPalindrome(++s1, --s2) : (!isAlphaNum(*s1)) ?
            isRPalindrome(++s1, s2): (!isAlphaNum(*s2)) ?
            isRPalindrome(s1, --s2): false;
}

/***********************************************************************/
/* Given a string, determine if it is a palindrome, considering only   */
/* alphanumeric characters and ignoring cases.                         */
/* For example,                                                        */
/* "A man, a plan, a canal: Panama" is a palindrome.                   */
/* "race a car" is not a palindrome.                                   */
/* Note:                                                               */
/* Have you consider that the string might be empty? This is a good    */
/* question to ask during an interview.                                */
/* For the purpose of this problem, we define empty string as valid    */
/* palindrome.                                                         */
/***********************************************************************/
bool isPalindrome(char* s)
{
    int len = strlen(s);
    return isRPalindrome(s, s + len - 1);
}

/***********************************************************************/
/* main: Entry point!                                                  */
/*                                                                     */
/***********************************************************************/
int main()
{
    //char s[] = "A man, a plan, a canal: Panama"; // palindrome
    //char s[] = "race a car"; // not a palindrome
    char s[] = "";
    printf("Palindrome check = %d :\n", isPalindrome(s));
    return 0;
}
