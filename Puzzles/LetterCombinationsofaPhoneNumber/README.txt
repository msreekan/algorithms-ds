******************************************************************************
Problem Statement: Letter Combinations of a Phone Number
******************************************************************************
Given a digit string, return all possible letter combinations that the number
could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.

https://leetcode.com/problems/letter-combinations-of-a-phone-number

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

******************************************************************************
URL : https://leetcode.com/problems/letter-combinations-of-a-phone-number
******************************************************************************

******************************************************************************
Notes: 
******************************************************************************
Time Complexity : O(4 ^ n)
Space Complexity : O(n)

Typical recursive mechanism to generate combinations. Each letter combination
is pushed to the stack and once generated it will be moved to the output array. 

******************************************************************************

******************************************************************************
Other Similar Problems: 
******************************************************************************
