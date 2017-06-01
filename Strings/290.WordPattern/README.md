******************************************************************************
Problem Statement: [Word Pattern](https://leetcode.com/problems/word-pattern/#/description)
******************************************************************************
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a

letter in pattern and a non-empty word in str.

Examples:

pattern = "abba", str = "dog cat cat dog" should return true.

pattern = "abba", str = "dog cat cat fish" should return false.

pattern = "aaaa", str = "dog cat cat dog" should return false.

pattern = "abba", str = "dog dog dog dog" should return false.

******************************************************************************
Notes:

Time Complexity : O(n x m) n = pattern length, m = word length

Space Complexity : O(1)

******************************************************************************
