******************************************************************************
Problem Statement: Merge k Sorted Lists
******************************************************************************
Merge k sorted linked lists and return it as one sorted list.
Analyze and describe its complexity.

******************************************************************************
URL : https://leetcode.com/problems/merge-k-sorted-lists/
******************************************************************************

******************************************************************************
Notes: 
******************************************************************************
Time Complexity : O(nLog(m))
Space Complexity : O(1)

Create a heap out of the list. Allow the smallest element to rise up to the
root, this ensures a O(nLog(m)) complexity versus the brute force O(n^2)

******************************************************************************

******************************************************************************
Other Similar Problems: 
******************************************************************************
1. Merge Two Sorted Lists