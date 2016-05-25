******************************************************************************
Problem Statement: Container With Most Water
******************************************************************************
Given n non-negative integers a1, a2, ..., an, where each represents a point 
at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis
forms a container, such that the container contains the most water.

Note: You may not slant the container.
******************************************************************************
URL : https://leetcode.com/problems/longest-palindromic-substring/
******************************************************************************

******************************************************************************
Notes: 
******************************************************************************
Time Complexity : O(n)
Space Complexity : O(1)

Algorithms starts scanning the array from both the ends while seeking to 
increase the overall container height. Note that the container volume 
increases only if the decreasing width is compensated by an increased height.
******************************************************************************

******************************************************************************
Other Similar Problems: 
******************************************************************************
